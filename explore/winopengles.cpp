#include "winopengles.h"

#include <QtGui>
#include <qmessagebox.h>
WinOpenGLES::WinOpenGLES(QWidget *parent) :
    QWidget(parent),mFrequency(30)
{
    m_hWnd = (HWND)winId();

    setAttribute(Qt::WA_PaintOnScreen, true);

    if (!initOpenGLES())
    {
        QMessageBox::warning(this, tr("Error"),tr("WGLInit()"),QMessageBox::Ok);
    }

    // 2.Set Up Our Perspective GL Screen
    GLResize(size());

    if (!GLInit())
    {
        QMessageBox::warning(this, tr("Error"),tr("GLInit()"),QMessageBox::Ok);
    }

//    eglDisplay	= 0;
//    eglConfig	= 0;
//    eglSurface	= 0;
//    eglContext	= 0;
//    eglWindow	= 0;
}

QPaintEngine *WinOpenGLES::paintEngine() const	//渲染位置(特别重要,说明)
{
    return NULL;
}

WinOpenGLES::~WinOpenGLES(void)
{
    GLRelease();
}

void logoutput( const char * lpszFormat, ... )
{
//#ifdef _DEBUG
//    va_list argList;
//    va_start( argList, lpszFormat );

//    char chInput[512] = {0};
//    vsprintf_s( chInput, lpszFormat, argList );

//    va_end(argList);

//    OutputDebugString(chInput);
//    OutputDebugString("\n");
//#endif
}

/*!****************************************************************************
 @Function		TestEGLError
 @Input			pszLocation		location in the program where the error took
                                place. ie: function name
 @Return		bool			true if no EGL error was detected
 @Description	Tests for an EGL error and prints it
******************************************************************************/
bool TestEGLError(char* pszLocation)
{
    /*
        eglGetError returns the last error that has happened using egl,
        not the status of the last called function. The user has to
        check after every single egl call or at least once every frame.
    */
    EGLint iErr = eglGetError();
    if (iErr != EGL_SUCCESS)
    {
        logoutput("%s failed (%d).\n", pszLocation, iErr);
        return false;
    }

    return true;
}

bool WinOpenGLES::initOpenGLES()
{
    /*
        Step 1 - Get the default display.
        EGL uses the concept of a "display" which in most environments
        corresponds to a single physical screen. Since we usually want
        to draw to the main screen or only have a single screen to begin
        with, we let EGL pick the default display.
        Querying other displays is platform specific.
    */
    HDC hDC = ::GetDC(m_hWnd);
    eglDisplay = eglGetDisplay(hDC);
    if (eglDisplay == EGL_NO_DISPLAY)
        if ((eglDisplay = eglGetDisplay((EGLNativeDisplayType) EGL_DEFAULT_DISPLAY)) == EGL_NO_DISPLAY)
            return FALSE;

    /*
        Step 2 - Initialize EGL.
        EGL has to be initialized with the display obtained in the
        previous step. We cannot use other EGL functions except
        eglGetDisplay and eglGetError before eglInitialize has been
        called.
        If we're not interested in the EGL version number we can just
        pass NULL for the second and third parameters.
    */
    EGLint iMajorVersion, iMinorVersion;
    if (!eglInitialize(eglDisplay, &iMajorVersion, &iMinorVersion))
    {
        logoutput("eglInitialize() failed.");
        return FALSE;
    }

    /*
        Step 3 - Make OpenGL ES the current API.
        EGL provides ways to set up OpenGL ES and OpenVG contexts
        (and possibly other graphics APIs in the future), so we need
        to specify the "current API".
    */
    eglBindAPI(EGL_OPENGL_ES_API);
    if (!TestEGLError("eglBindAPI"))
    {
        return FALSE;
    }

    /*
        Step 4 - Specify the required configuration attributes.
        An EGL "configuration" describes the pixel format and type of
        surfaces that can be used for drawing.
        For now we just want to use the default Windows surface,
        i.e. it will be visible on screen. The list
        has to contain key/value pairs, terminated with EGL_NONE.
     */
    const EGLint pi32ConfigAttribs[] =
    {
        EGL_LEVEL,				0,
        EGL_SURFACE_TYPE,		EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE,	EGL_OPENGL_ES2_BIT,
        EGL_NATIVE_RENDERABLE,	EGL_FALSE,
        EGL_DEPTH_SIZE,			EGL_DONT_CARE,
        EGL_NONE
    };

    /*
        Step 5 - Find a config that matches all requirements.
        eglChooseConfig provides a list of all available configurations
        that meet or exceed the requirements given as the second
        argument. In most cases we just want the first config that meets
        all criteria, so we can limit the number of configs returned to 1.
    */
    EGLint iConfigs;
    if (!eglChooseConfig(eglDisplay, pi32ConfigAttribs, &eglConfig, 1, &iConfigs) || (iConfigs != 1))
    {
        logoutput("eglChooseConfig() failed.");
        return FALSE;
    }

    /*
        Step 6 - Create a surface to draw to.
        Use the config picked in the previous step and the native window
        handle when available to create a window surface. A window surface
        is one that will be visible on screen inside the native display (or
        fullscreen if there is no windowing system).
        Pixmaps and pbuffers are surfaces which only exist in off-screen
        memory.
    */
    // Create a surface for the main window
    eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, (EGLNativeWindowType) m_hWnd, NULL);
    //eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, eglWindow, NULL);

    if(eglSurface == EGL_NO_SURFACE)
    {
        eglGetError(); // Clear error
        eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, NULL, NULL);
    }

    if (!TestEGLError("eglCreateWindowSurface"))
    {
        return FALSE;
    }

    /*
        Step 7 - Create a context.
        EGL has to create a context for OpenGL ES. Our OpenGL ES resources
        like textures will only be valid inside this context
        (or shared contexts)
    */
    EGLint ai32ContextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
    eglContext = eglCreateContext(eglDisplay, eglConfig, NULL, ai32ContextAttribs);
    if (!TestEGLError("eglCreateContext"))
    {
        return FALSE;
    }

    /*
        Step 8 - Bind the context to the current thread and use our
        window surface for drawing and reading.
        Contexts are bound to a thread. This means you don't have to
        worry about other threads and processes interfering with your
        OpenGL ES application.
        We need to specify a surface that will be the target of all
        subsequent drawing operations, and one that will be the source
        of read operations. They can be the same surface.
    */
    eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);
    if (!TestEGLError("eglMakeCurrent"))
    {
        return FALSE;
    }
    return true;
}

bool WinOpenGLES::swap()
{
    eglSwapBuffers(eglDisplay, eglSurface);
    if (!TestEGLError("eglSwapBuffers"))
    {
        return FALSE;
    }
    return true;
}

void WinOpenGLES::releaseOpenGLES()
{
    eglMakeCurrent(EGL_NO_DISPLAY, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroyContext(eglDisplay, eglContext);
    eglDestroySurface(eglDisplay, eglSurface);

    eglTerminate(eglDisplay);
}

BOOL WinOpenGLES::GLInit()
{
    glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
    glClearDepth(1.0f);									// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

    startTimer(mFrequency);
    return TRUE;
}

void WinOpenGLES::GLFrame()
{
    EnGLFrame();
}

void WinOpenGLES::GLRender()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
    glLoadIdentity();									// Reset The Current Modelview Matrix

    EnGLRender();
}

///设置刷新频率
void WinOpenGLES::setFrequency(int count)
{
    mFrequency = count;
}

void WinOpenGLES::GLResize(QSize size)
{
    int height = size.height();
    int width = size.width();

    if (height==0)										// Prevent A Divide By Zero By
    {
        height=1;										// Making Height Equal One
    }

//    glViewport(0,0,(GLsizei)width,(GLsizei)height);						// Reset The Current Viewport

//    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
//    glLoadIdentity();									// Reset The Projection Matrix

//    // Calculate The Aspect Ratio Of The Window
//    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

//    glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
//    glLoadIdentity();
}

BOOL WinOpenGLES::GLRelease()
{
    eglDisplay	= 0;
    eglConfig	= 0;
    eglSurface	= 0;
    eglContext	= 0;
    eglWindow	= 0;

    return TRUE;
}

void WinOpenGLES::EnGLFrame()
{

}

void WinOpenGLES::EnGLRender()
{

}

void WinOpenGLES::timerEvent(QTimerEvent* )
{
    update();
}

void WinOpenGLES::paintEvent(QPaintEvent* )
{
    if (updatesEnabled())
    {
        GLFrame();
        GLRender();
        swap();
    }
}

void WinOpenGLES::resizeEvent(QResizeEvent *e)
{
    GLResize(e->size());
    QWidget::resizeEvent(e);
}

void WinOpenGLES::closeEvent(QCloseEvent *e)
{
    GLRelease();
    QWidget::closeEvent(e);
}

