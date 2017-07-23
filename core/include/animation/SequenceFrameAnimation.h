#ifndef __SequenceFrameAnimation_h__
#define __SequenceFrameAnimation_h__

#include "utils/include/prerequisites.h"
#include "utils/include/Common.h"
#include "Animation.h"


/**
 * An animation that controls the position of an object. See the
 * {@link android.view.animation full package} description for details and
 * sample code.
 *
 */
class SequenceFrameAnimation : public Animation
{
private:
	GameObject* mTarget;
	TextureUnitState* _textureUnitState;

public:
    SequenceFrameAnimation(Root* root, GameObject* target, bool canStop = true);

    void applyTransformation(float interpolatedTime/*, Transform* t*/);
};

#endif


