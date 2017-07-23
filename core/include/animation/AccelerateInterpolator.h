#ifndef __AccelerateInterpolator_h__
#define __AccelerateInterpolator_h__

#include "Interpolator.h"
#include "utils/include/mathlib.h"
/**
 * An interpolator where the rate of change starts out slowly and
 * and then accelerates.
 *
 */
class AccelerateInterpolator : public Interpolator {
private:
	float mFactor;
    double mDoubleFactor;

public:
    AccelerateInterpolator() {
        mFactor = 1.0f;
        mDoubleFactor = 2.0;
    }

    /**
     * Constructor
     *
     * @param factor Degree to which the animation should be eased. Seting
     *        factor to 1.0f produces a y=x^2 parabola. Increasing factor above
     *        1.0f  exaggerates the ease-in effect (i.e., it starts even
     *        slower and ends evens faster)
     */
    AccelerateInterpolator(float factor) {
        mFactor = factor;
        mDoubleFactor = 2 * mFactor;
    }

//    AccelerateInterpolator(Context context, AttributeSet attrs) {
//        TypedArray a =
//            context.obtainStyledAttributes(attrs, com.android.internal.R.styleable.AccelerateInterpolator);
//
//        mFactor = a.getFloat(com.android.internal.R.styleable.AccelerateInterpolator_factor, 1.0f);
//        mDoubleFactor = 2 * mFactor;
//
//        a.recycle();
//    }

    float getInterpolation(float input) {
        if (mFactor == 1.0f) {
            return input * input;
        } else {
            return (float)Math::Pow(input, (float)mDoubleFactor);
        }
    }
};
#endif
