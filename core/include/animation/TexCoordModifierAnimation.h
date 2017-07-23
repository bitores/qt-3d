#ifndef __TexCoordModifierAnimation_h__
#define __TexCoordModifierAnimation_h__

#include "utils/include/prerequisites.h"
#include "utils/include/Common.h"
#include "Animation.h"


/**
 * An animation that controls the position of an object. See the
 * {@link android.view.animation full package} description for details and
 * sample code.
 *
 */
class TexCoordModifierAnimation : public Animation
{
public:
    typedef enum _tex_op {
        TRANS_U = 0,
        TRANS_V,
        SCALE_U,
        SCALE_V,
        ROTATE,
    }TEX_OP; // for texture animation control

protected:
	bool mTransU, mTransV;
	bool mScaleU, mScaleV;
	bool mRotate;

	Real mFromScaleU;
	Real mToScaleU;

	Real mFromScaleV;
	Real mToScaleV;

	Real mFromTranslateU;
	Real mToTranslateU;

	Real mFromTranslateV;
	Real mToTranslateV;

	Real mFromRotate;
	Real mToRotate;

	TextureUnitState* mTextureLayer;
public:
	/** Constructor.
		@param
			t TextureUnitState to apply the modification to.
		@param
			translateU If true, the u coordinates will be translated by the modification.
		@param
			translateV If true, the v coordinates will be translated by the modification.
		@param
			scaleU If true, the u coordinates will be scaled by the modification.
		@param
			scaleV If true, the v coordinates will be scaled by the modification.
		@param
			rotate If true, the texture will be rotated by the modification.
	*/
	TexCoordModifierAnimation(Root* root, TextureUnitState* t, bool translateU = false, bool translateV = false,
		bool scaleU = false, bool scaleV = false, bool rotate = false );

	void applyTransformation(float interpolatedTime);

	Real getValue(void) const;
	void setValue(TEX_OP op, Real value);

	void setFromScaleU(Real scaleu);
	void setToScaleU(Real scaleu);

	void setFromScaleV(Real scalev);
	void setToScaleV(Real scalev);

	void setFromTranslateU(Real translateu);
	void setToTranslateU(Real translateu);

	void setFromTranslateV(Real translatev);
	void setToTranslateV(Real translatev);

	void setFromRotate(Real rotate);
	void setToRotate(Real rotate);

};

#endif
