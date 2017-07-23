#ifndef __AnticipateInterpolator_h__
#define __AnticipateInterpolator_h__

#include "Interpolator.h"
#include "utils/include/mathlib.h"

/**
 * An interpolator where the change starts backward then flings forward.
 */
class AnticipateInterpolator : public Interpolator {
private:
	float mTension;

public:
	AnticipateInterpolator() {
        mTension = 2.0f;
    }

    /**
     * @param tension Amount of anticipation. When tension equals 0.0f, there is
     *                no anticipation and the interpolator becomes a simple
     *                acceleration interpolator.
     */
    AnticipateInterpolator(float tension) {
        mTension = tension;
    }

//    AnticipateInterpolator(Context context, AttributeSet attrs) {
//        TypedArray a = context.obtainStyledAttributes(attrs,
//                com.android.internal.R.styleable.AnticipateInterpolator);
//
//        mTension =
//                a.getFloat(com.android.internal.R.styleable.AnticipateInterpolator_tension, 2.0f);
//
//        a.recycle();
//    }

    float getInterpolation(float t) {
        // a(t) = t * t * ((tension + 1) * t - tension)
        return t * t * ((mTension + 1) * t - mTension);
    }
};
#endif
