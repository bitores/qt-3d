#ifndef CGDEMO_H
#define CGDEMO_H

#include "winopengles.h"
class E3dWallpaperBase;
class CGDemo : public WinOpenGLES
{
    Q_OBJECT
public:
    CGDemo(WinOpenGLES* parent = NULL);
    ~CGDemo();

protected:
    void EnGLInit();
    void EnGLFrame();
    void EnGLRender();

public:
    E3dWallpaperBase* me3d;
};

#endif // CGDEMO_H
