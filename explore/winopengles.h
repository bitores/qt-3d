#ifndef WINOPENGLES_H
#define WINOPENGLES_H

#include <qt_windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
//#include <gl\glu.h>			// Header File For The GLu32 Library
//#include <gl\glaux.h>		// Header File For The Glaux Library



#include <QWidget>
#include <EGL/egl.h>
#include <GLES2/gl2.h>


//#pragma comment(lib,"libEGL.lib")
//#pragma comment(lib,"glut32.lib")
//#pragma comment(lib,"glut.lib")
//#pragma comment(lib,"glu.lib")
//#pragma comment(lib,"glu32.lib")
class WinOpenGLES : public QWidget
{
    Q_OBJECT
public:
    explicit WinOpenGLES(QWidget *parent = 0);
    QPaintEngine *paintEngine() const;	//渲染位置(特别重要,说明)


    bool initOpenGLES();
    bool swap();
    void releaseOpenGLES();

    BOOL GLInit();
    void GLFrame();
    void GLRender();
    void GLResize(QSize size);
    BOOL GLRelease();

    virtual void EnGLFrame();
    virtual void EnGLRender();

    void setFrequency(int count);

protected:
    virtual ~WinOpenGLES(void);				//析构函数
    void timerEvent(QTimerEvent* );
    void paintEvent(QPaintEvent* );
    void resizeEvent(QResizeEvent *);
    void closeEvent(QCloseEvent *);


private:
    HDC m_hDC;
    HWND m_hWnd;
    // EGL variables
    EGLDisplay			eglDisplay;
    EGLConfig			eglConfig;
    EGLSurface			eglSurface;
    EGLContext			eglContext;
    EGLNativeWindowType	eglWindow;

    int         mFrequency;
};
void logoutput( const char * lpszFormat, ...);
#endif // WINOPENGLES_H
