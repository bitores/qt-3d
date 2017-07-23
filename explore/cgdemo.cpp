#include "cgdemo.h"

#include "gl/glut.h"
#include <iostream>
#include <QLabel>

#include "../core/include/e3d_wallpaper_base/E3dWallpaperBase.h"


#pragma comment(lib,"glut32.lib")

#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

void CGDemo::EnGLInit()
{
    me3d = new E3dWallpaperBase();
    me3d->initJellyfish();
}

void CGDemo::EnGLFrame()
{
    std::cout<<"EnGLRender"<<std::endl;
}

void CGDemo::EnGLRender()
{

}

CGDemo::CGDemo( WinOpenGLES* parent ) : WinOpenGLES(parent)
{
    me3d = 0;
    EnGLInit();
}
CGDemo::~CGDemo()
{

}
