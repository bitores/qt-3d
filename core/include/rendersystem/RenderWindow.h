#ifndef __RenderWindow__h
#define __RenderWindow__h

#include "RenderTarget.h"

class RenderWindow : public RenderTarget
{
public:
	RenderWindow(Root* root, unsigned int width, unsigned int height);

	void copyContentsToMemory(const PixelBox &dst, FrameBuffer buffer = FB_AUTO);

	bool requiresTextureFlipping() const;
};
#endif
