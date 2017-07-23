#ifndef __DecelerateInterpolator_h__
#define __DecelerateInterpolator_h__

#include "Interpolator.h"
#include "utils/include/mathlib.h"

/**
 * An interpolator where the rate of change starts out quickly and
 * and then decelerates.
 *
 */
class DecelerateInterpolator : public Interpolator {
public:
	DecelerateInterpolator() {
		mFactor = 1.0f;
    }

	/**
     * Constructor
     *
     * @param factor Degree to which the animation should be eased. Setting factor to 1.0f produces
     *        an upside-down y=x^2 parabola. Increasing factor above 1.0f makes exaggerates the
     *        ease-out effect (i.e., it starts even faster and ends evens slower)
     */
    DecelerateInterpolator(float factor) {
        mFactor = factor;
    }

//    DecelerateInterpolator(Context context, AttributeSet attrs) {
//        TypedArray a =
//            context.obtainStyledAttributes(attrs, com.android.internal.R.styleable.DecelerateInterpolator);
//
//        mFactor = a.getFloat(com.android.internal.R.styleable.DecelerateInterpolator_factor, 1.0f);
//
//        a.recycle();
//    }

    float getInterpolation(float input) {
        float result;
        if (mFactor == 1.0f) {
            result = (float)(1.0f - (1.0f - input) * (1.0f - input));
        } else {
            result = (float)(1.0f - Math::Pow((1.0f - input), 2 * mFactor));
        }
        return result;
    }

private:
    float mFactor;
};
#endif
