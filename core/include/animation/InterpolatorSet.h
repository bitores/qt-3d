#ifndef __InterpolatorSet_h__
#define __InterpolatorSet_h__

#include "Interpolator.h"
#include "animation/AccelerateDecelerateInterpolator.h"
#include "animation/AccelerateInterpolator.h"
#include "animation/AnticipateInterpolator.h"
#include "animation/AnticipateOvershootInterpolator.h"
#include "animation/BounceInterpolator.h"
#include "animation/CycleInterpolator.h"
#include "animation/DecelerateInterpolator.h"
#include "animation/LinearInterpolator.h"
#include "animation/OvershootInterpolator.h"

#include "utils/include/mathlib.h"
#ifdef _DEBUG_
#include "base/LogManager.h"
#endif
/**
 * An interpolator where the rate of change is constant
 *
 */
class InterpolatorSet
{
protected:
    typedef std::vector<Interpolator*> TInterpolatorArray;
    TInterpolatorArray mInterpolatorArray;

public:
	InterpolatorSet()
	{
	}

	~InterpolatorSet()
	{
		destroyInterpolators();
	}

	Interpolator* getRandomInterpolator()
	{
		if (0 == mInterpolatorArray.size()) {
			return 0;
		}
		unsigned int index = Math::RangeRandom(0, mInterpolatorArray.size() - 1);
#ifdef _DEBUG_
		LogManager::log(LOG_TAG, "InterpolatorSet::getRandomInterpolator: mInterpolatorArray.size=%u, randomIndex=%u", mInterpolatorArray.size(), index);
#endif
		if (index >= mInterpolatorArray.size()) {
			return 0;
		}
		return mInterpolatorArray[index];
	}

	Interpolator* getInterpolator(unsigned int index)
	{
		if (index >= mInterpolatorArray.size()) {
			return 0;
		}
		return mInterpolatorArray[index];
	}

	void addInterpolator(Interpolator* pIp)
	{
		if (pIp) {
			mInterpolatorArray.push_back(pIp);
		}
	}

	void destroyInterpolators()
	{
#ifdef _DEBUG_
		LogManager::log(LOG_TAG, "InterpolatorSet::destroyInterpolators: begin...");
		int i = 0;
#endif
		TInterpolatorArray::iterator iter = mInterpolatorArray.begin();
		for (; iter != mInterpolatorArray.end(); ++iter) {
			if (*iter) {
				delete *iter;
#ifdef _DEBUG_
				++i;
#endif
			}
		}
		mInterpolatorArray.clear();
#ifdef _DEBUG_
		LogManager::log(LOG_TAG, "InterpolatorSet::destroyInterpolators: finish to destroy %d Interpolators", i);
#endif
	}

	unsigned int size()
	{
		return mInterpolatorArray.size();
	}

	static Interpolator* getInterpolatorInstance(String iplName, float factor = 1.0)
	{
		Interpolator *interpolator = 0;
		StringUtil::toLowerCase(iplName);
		if ("accelerate" == iplName) {
			interpolator = new AccelerateInterpolator(factor);
		} else if ("decelerate" == iplName) {
			interpolator = new DecelerateInterpolator(factor);
		} else if ("accelerate_decelerate" == iplName) {
			interpolator = new AccelerateDecelerateInterpolator();
		} else if ("anticipate" == iplName) {
			interpolator = new AnticipateInterpolator();
		} else if ("anticipate_overshoot" == iplName) {
			interpolator = new AnticipateOvershootInterpolator();
		} else if ("bounce" == iplName) {
			interpolator = new BounceInterpolator();
		} else if ("cycle" == iplName) {
			interpolator = new CycleInterpolator(1);
		} else if ("overshoot" == iplName) {
			interpolator = new OvershootInterpolator();
		} else {
			interpolator = new LinearInterpolator();
		}
		return interpolator;
	}
};
#endif
