#ifndef __OvershootInterpolator_h__
#define __OvershootInterpolator_h__

#include "Interpolator.h"
#include "utils/include/mathlib.h"

/**
 * An interpolator where the change flings forward and overshoots the last value
 * then comes back.
 */
class OvershootInterpolator : public Interpolator {
private:
	float mTension;

public:
	OvershootInterpolator() {
        mTension = 2.0f;
    }

    /**
     * @param tension Amount of overshoot. When tension equals 0.0f, there is
     *                no overshoot and the interpolator becomes a simple
     *                deceleration interpolator.
     */
    OvershootInterpolator(float tension) {
        mTension = tension;
    }

//    public OvershootInterpolator(Context context, AttributeSet attrs) {
//        TypedArray a = context.obtainStyledAttributes(attrs,
//                com.android.internal.R.styleable.OvershootInterpolator);
//
//        mTension =
//                a.getFloat(com.android.internal.R.styleable.OvershootInterpolator_tension, 2.0f);
//
//        a.recycle();
//    }

    float getInterpolation(float t) {
        // _o(t) = t * t * ((tension + 1) * t + tension)
        // o(t) = _o(t - 1) + 1
        t -= 1.0f;
        return t * t * ((mTension + 1) * t + mTension) + 1.0f;
    }
};
#endif
