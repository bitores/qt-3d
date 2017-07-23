#ifndef __AnimationUtils_h__
#define __AnimationUtils_h__

#include <stdint.h>
#include <sys/types.h>
#include "utils/include/Timer.h"
/**
 * Defines common utilities for working with animations.
 *
 */
class AnimationUtils
{
public:
	AnimationUtils();
	static Timer mTimer;
    /**
     * Returns the current animation time in milliseconds. This time should be used when invoking
     * {@link Animation#setStartTime(long)}. Refer to {@link android.os.SystemClock} for more
     * information about the different available clocks. The clock used by this method is
     * <em>not</em> the "wall" clock (it is not {@link System#currentTimeMillis}).
     *
     * @return the current animation time in milliseconds
     *
     * @see android.os.SystemClock
     */
    static long currentAnimationTimeMillis() {
    	return mTimer.getMilliseconds();
//        return SystemClock.uptimeMillis();
    }
};

#endif
