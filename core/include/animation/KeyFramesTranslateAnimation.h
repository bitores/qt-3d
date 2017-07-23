#ifndef __KeyFramesTranslateAnimation_h__
#define __KeyFramesTranslateAnimation_h__

#include "utils/include/prerequisites.h"
#include "utils/include/Common.h"
#include "utils/include/Transform.h"
#include "Animation.h"
#ifdef _DEBUG_ANI_
#include "base/LogManager.h"
#endif
#include "utils/include/String.h"
/**
 * An animation that controls the position of an object. See the
 * {@link android.view.animation full package} description for details and
 * sample code.
 *
 */
class KeyFramesTranslateAnimation : public Animation
{
private:
	Transform* mTarget;

	float mScreenWidth;
	float mScreenHeight;
    bool mIsCoordinateRelativeToScreen;
	bool mIsDirty;
    float *frameDatas;
    int numFrames;
    char * kfsName;
    TransformSpace mTransformSpace;

    void _init() {
        //mRelative = false;
        mIsCoordinateRelativeToScreen = false;
        mIsDirty = true;
        mScreenWidth = 0.0;
        mScreenHeight = 0.0;
        frameDatas=0;
        numFrames=0;
        kfsName=0;
        //mRoot=0;

    }
public:

    KeyFramesTranslateAnimation(Root* root, Transform* target, bool canStop = true) : Animation(root, canStop) {
    	_init();
    	mTarget = target;
    }

    void setFrameDatas(float* frames)
    {
    	this->frameDatas=frames;

    }
    void setIsCoordinateRelativeToScreen(bool isCoordinateRelativeToScreen)
    {
    	mIsCoordinateRelativeToScreen = isCoordinateRelativeToScreen;
    	mIsDirty = true;
    }


   	void onResize(float screenWidth, float screenHeight) {
   		mScreenWidth = screenWidth;
   		mScreenHeight = screenHeight;
   		mIsDirty = true;
   	}
	void setTransformSpace(String tfsName)
   	{
   		//mTransformSpace = ts;
   		StringUtil::toLowerCase(tfsName);
   			if ("ts_local" == tfsName) {
   				mTransformSpace = TS_LOCAL;
   			} else if("ts_world" == tfsName) {
   				mTransformSpace = TS_WORLD;
   			} else if("ts_not_add" == tfsName) {
   				mTransformSpace = TS_NOT_ADD;
   			} else {
   				mTransformSpace = TS_PARENT;
   		}
   	}
   	bool setFrames(int frameNum,String framesetName);
    void applyTransformation(float interpolatedTime/*, Transform* t*/);

    void initialize(int width, int height, int parentWidth, int parentHeight);
};

#endif
