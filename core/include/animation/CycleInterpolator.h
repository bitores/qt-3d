#ifndef __CycleInterpolator_h__
#define __CycleInterpolator_h__

#include "Interpolator.h"
#include "utils/include/mathlib.h"

/**
 * Repeats the animation for a specified number of cycles. The
 * rate of change follows a sinusoidal pattern.
 *
 */
class CycleInterpolator : public Interpolator {
public:
	CycleInterpolator(float cycles) {
        mCycles = cycles;
    }

//    CycleInterpolator(Context context, AttributeSet attrs) {
//        TypedArray a =
//            context.obtainStyledAttributes(attrs, com.android.internal.R.styleable.CycleInterpolator);
//
//        mCycles = a.getFloat(com.android.internal.R.styleable.CycleInterpolator_cycles, 1.0f);
//
//        a.recycle();
//    }

    float getInterpolation(float input) {
        return (float)(Math::Sin(2 * mCycles * Math::PI * input));
    }

private:
    float mCycles;
};
#endif
