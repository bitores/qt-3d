	OpenGL只处理与3D图形的绘制，基本上不提供创建用户界面的功能，所以为OpenGL应用程序创建用户界面必须使用其它的图形工其包（如Motif、MFC等）。而Qt的OpenGL模块很好的解决了这个问题，它提供了一个继承自Qwidget的OpenGL部件类QGLWidget，使得该部件类能够像Qt其它部件那样使用，还可以在绘制窗口部件时直接使用OpenGL的API接口。在Qt中为OpenGL提供支持的类主要有以下几个：
	QGLWidget：用于渲染OpenGL场景的易于使用的Qt部件。
	QGLColormap：用于在QGLWidget中安装用户自定义的颜色图。
	QGLContext：封装了用于OpenGL渲染的场景。
	QGLFormat：指定OpenGL演染场景的显示模式。
	QGLFrameBufferObject和QGLPixelBuffer分别提供了对GL帧缓冲对象和GL像素缓冲的支持。
	QGLPaintEngine：QPaintEngine的派生类，为QPainter提供了OpenGL绘图引擎。
	实际上，在进行二维图形的绘制中，完全可以不使用OpenGL的原生接口而使用更为方便的QPainter。QPainter只是个API，实际的渲染是由QPaintEngine来执行的。Qt自带有QGLPaintEngine，为QPainter提供了OpenGL后台。在QGLWidget基础上创建的QPainter，自动将QGLPaintEngine作为绘画引擎。这样，任何使用此QPainter类型绘制的2D图形都会自动解析至OpenGL，间接以GL的原生接口来实现二维图形的绘制。使用QPainter而不是OpenGL命令的优势是可轻易将渲染在平台默认引擎和OpenGL之间切换。这样不仅可以充分利用二者各自的优势，同时还可以直接使用Qt二维绘图系统所提供的众多高级功能。
	Qt 提供了QtOpenGL模块来支持三维图形功能的OpenGL模块。在使用QtOpengl模块时，必须在对应的工程文件（*.pro）中加入:
	QT += opengl
	来声明使用QtOpengl模块，以便 qmake 在利用*.pro生成编译器所需的makefile时添加所需的opengl库。
	在Qt下使用创建Opengl绘图组件主要通过继承QGLWidget并重现相关绘制函数来实现，QGLWidget派生自QWidget,故绝大多数情况下QGLWidget可以像QWidget一样使用，只是使用OpenGL的函数替代QPainter实现绘制。通常通过子类化QGLWidget来实现OpenGL的使用，QGLWidget提供了三个虚函数用以重载来实现OpenGL的绘制：
	 
	initializeGL() 注册函数，在此设置GL的渲染绘制属性、定义显示列表、载入固定纹理等初始化工作。在initializeGL()在调用paintGL()之前只被调用一次，之后不再调用。
	paintGL() 绘制函数，在此使用OpenGL中的接口进行场景绘制，QGLWidget的paintEvent( QPaintEvent* )将会自动调用 paintGL()进行部件的显示绘制。也可在需要重绘时通过updateGL()时调用paintGL()。
	resizeGL() 该函数用于处理当部件大小发生改变时，对OpenGL绘图管线各矩阵需要进行的操作。该函数paintGL()第一次调用之前，initializeGL()调用之后被第一次被调用， 之后每当QGLWidget的不见大小发生改变时，都将调用该函数来对视图、投影矩阵等进行相应的设置。
	可在任何需要刷新场景绘制的地方通过调用updateGL()来通知OpenGL进行重绘，但updateGL()自身不用实现。与QWidget相同，鼠标和键盘事件是通过mousePressEvent()和keyPressEvent()等事件处理函数进行处理的。要创建动画，只需启动QTimer，然后调用updateGL()。但应注意，如果需要在QGLWidget派生类之外的其他函数中进行paintGL()相同功能的绘制，需要先使用makeCurrent()接口将后面绘制的上下文对象(Context)标记为当前上下文对象(Current Context)。
	如果本地OpenGL支持叠置绘制（Overlay Paint）（windows的WGL和X11的GLX都支持）QGLWidget还可以通过与前述类似的initializeOverlayGL()、resizeOverlayGL()、 paintOverlayGL()和updateOverlayGL()进行叠置层的绘制。makeoverlayCurrent()函数可以用于将叠置标记为当前上下文对象．
	除了对OpenGL原生接口的支持，QGLWidget还为OpenGL在多个操作系统平台上的应用进行了浅层封装。Qt提供加载图像并将其与纹理绑定的使用功能。可使用 GLuint bindTexture(Qimage&, GLenum target, GLint format, QGLContext::BindOptions)等接口将图像与所申请的OpenGL纹理索引进行绑定，并使用 deleteTexture ( GLuint id )来删除已申请的纹理索引。Qt在内部对己与纹理绑定的像素图／图像进行跟踪，这样就可在使用相同的图像文件或像素图时重新使用纹理。由于QImage是独立于硬件的，因此可以在另一个线程中对纹理图片进行绘制，在绘制完成之后再载入OpenGL中作为纹理，而不需要OpenGL渲染线程中处理，因此可以很大幅度提高OpenGL绘图部件的响应速度。
	Qt还提供了在OpenGL三维绘图场景中任意三维位置处按照给定的QFont字体格式绘制任意字符（包汉字等非ASCII码字符），大大简化了在三维场景中绘制字符的操作