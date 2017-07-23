####Qt中配置glut库   ( Windows )  

	Qt本身不包括glut工具库,如果要使用glut库，该怎么做呢？
	下面来简述一下Qt下怎么安装glut库：
	 
	1.首先需要去opengl的官网下载glut库：
	http://www.opengl.org/resources/libraries/glut/glutdlls37beta.zip
	 
	2.解压后，将glut32.lib和glut.lib两个文件拷贝到qt目录下的./lib文件夹中；
	 
	3.将glut.dll和glut32.dll两个动态链接库拷贝到C:\windows\system32中；
	 
	4.将glut.h文件拷贝到qt目录下的\include\QtOpenGL中，并建立glut文件【内容写上 #include "glut.h"】,保存为没有后缀名的文件；
	 
	5.切换到自己的程序中，在 **.pro 文件中添加：
	   LIBS += -lgut32
	   LIBS += -LC:\glut
	 
	6. 在main.cpp中加入“#include<glut>”或者“#include<glut.h>”,这样就可以使用glut中的函数了。
	 
	7. 下面来看一个简单的例子：
	复制代码
	 1     #include <windows.h>
	 2     #include <glut.h>
	 3void init(void)
	 4    {
	 5       glClearColor(1.0, 1.0, 1.0, 0.0);
	 6      glMatrixMode(GL_PROJECTION);
	 7       gluOrtho2D(0.0, 200.0, 0.0, 160.0);
	 8    }
	 9void lineSegment(void)
	10    {
	11      glClear(GL_COLOR_BUFFER_BIT);
	12       glColor3f(1.0, 0.0, 0.0);
	13      glBegin(GL_LINES);
	14       glVertex2i (180, 15);
	15       glVertex2i (10, 145);
	16      glEnd();
	17      glFlush();
	18    }
	19int main(int argc, char **argv)
	20    {
	21       glutInit(&argc, argv);
	22       glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	23       glutInitWindowPosition(50, 100);
	24       glutInitWindowSize(400, 300);
	25       glutCreateWindow("Example OpenGL Program");
	26      init();
	27      glutDisplayFunc(lineSegment);
	28      glutMainLoop();
	29     }
