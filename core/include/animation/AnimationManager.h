#ifndef __AnimationManager_h__
#define __AnimationManager_h__

#include "utils/include/prerequisites.h"

class AnimationManager
{
private:
	typedef std::list<Animation*> AnimationList;
	AnimationList mAnimationList;

public:
	~AnimationManager();

	Animation*  registerAnimation(Animation* animation);
	Animation*  unregisterAnimation(Animation* animation);
	void update(Real deltaTime);

	void onStop(bool beStop);

	Animation* findAnimation(const String & objName);

	void releaseAllAnimation();

	void onResize(float screenWidth, float screenHeight);
};
#endif
