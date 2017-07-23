#ifndef __UI3dStore_h__
#define __UI3dStore_h__

#include "e3d_wallpaper_base/E3dWallpaperBase.h"

class UI3dStore : public E3dWallpaperBase
{
public:
    
public:
	UI3dStore();
	~UI3dStore();

	void prevCreateScene();
	void postCreateScene();


//	void onTouchEvent(int action, float x, float y);
//	void onOffsetsChanged(float xOffset, float yOffset, float xStep, float yStep, int xPixels, int yPixels);
//	void onStop(bool beStop);
//	void onSize(Real w, Real h);
};

#endif

