#ifndef __LinearInterpolator_h__
#define __LinearInterpolator_h__

#include "Interpolator.h"
#include "utils/include/mathlib.h"

/**
 * An interpolator where the rate of change is constant
 *
 */
class LinearInterpolator: public Interpolator {

public:
	LinearInterpolator() {
	}

//    LinearInterpolator(Context context, AttributeSet attrs) {
//    }

	float getInterpolation(float input) {
		return input;
	}
};
#endif
