#ifndef __TexCoordSetAnimation_h__
#define __TexCoordSetAnimation_h__

#include "utils/include/prerequisites.h"
#include "utils/include/Common.h"
#include "Animation.h"
#include "ui/eRect.h"

class TexCoordSetAnimation : public Animation
{
protected:
	eRectPtr mTarget;
    typedef vector< FloatRect> TextureCoordSets;
    TextureCoordSets mTextureCoords;
public:
	TexCoordSetAnimation(Root* root, eRectPtr target, bool canStop = true);

	void applyTransformation(float interpolatedTime);

	void setTarget(eRectPtr target);

	void setTextureCoordSets(TextureCoordSets textureCoords);

	void setStoppedFrame(int frame);
};

#endif
