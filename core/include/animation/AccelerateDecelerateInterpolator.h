#ifndef __AccelerateDecelerateInterpolator_h__
#define __AccelerateDecelerateInterpolator_h__

#include "Interpolator.h"
#include "utils/include/mathlib.h"
/**
 * An interpolator where the rate of change starts and ends slowly but
 * accelerates through the middle.
 *
 */
class AccelerateDecelerateInterpolator : public Interpolator {
public:
	AccelerateDecelerateInterpolator() {
    }

    float getInterpolation(float input) {
        return (float)(Math::Cos((input + 1) * Math::PI) / 2.0f) + 0.5f;
    }
};
#endif
