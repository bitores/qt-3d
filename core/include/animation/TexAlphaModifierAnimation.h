#ifndef _TexAlphaModifierAnimation_h_
#define _TexAlphaModifierAnimation_h_

#include "utils/include/prerequisites.h"
#include "utils/include/Common.h"
#include "Animation.h"


/**
 * An animation that controls the position of an object. See the
 * {@link android.view.animation full package} description for details and
 * sample code.
 *
 */
class TexAlphaModifierAnimation : public Animation
{
protected:
	Real mFromAlpha;
	Real mToAlpha;

	Pass* mPass;
public:
	/** Constructor.
		@param
		       pass Pass to apply the modification to.
	*/
	TexAlphaModifierAnimation(Root* root, Pass* pass);

	void applyTransformation(float interpolatedTime);

	void setFromAlpha(Real alpha);
	void setToAlpha(Real alpha);

	void setTarget(Pass* pass);
};










#endif /* _TexAlphaModifierAnimation_h_ */
