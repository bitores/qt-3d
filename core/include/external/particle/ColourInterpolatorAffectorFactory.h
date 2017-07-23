#ifndef __ColourInterpolatorAffectorFactory_H__
#define __ColourInterpolatorAffectorFactory_H__

#include "ParticlePrerequisites.h"
#include "particle/ParticleAffectorFactory.h"
#include "ColourInterpolatorAffector.h"
#ifdef _DEBUG_PARTICLE_SYSTEM_
#include "base/LogManager.h"
#endif

/** Factory class for ColourInterpolatorAffector. */
class ColourInterpolatorAffectorFactory : public ParticleAffectorFactory
{
	/** See ParticleAffectorFactory */
	String getName() const { return "ColourInterpolator"; }

	/** See ParticleAffectorFactory */
	ParticleAffector* createAffector(ParticleSystem* psys)
	{
		ParticleAffector* p = new ColourInterpolatorAffector(psys);
		mAffectors.push_back(p);
#ifdef _DEBUG_PARTICLE_SYSTEM_
		LogManager::log(PS_LOG_TAG, "ColourInterpolatorAffectorFactory::createAffector: ColourInterpolatorAffector created");
#endif
		return p;
	}

    void destroyAffector(ParticleAffector* e)
    {
    	if (0 != e) {
    		delete e;
#ifdef _DEBUG_PARTICLE_SYSTEM_
    		LogManager::log(PS_LOG_TAG, "ColourInterpolatorAffectorFactory::destroyAffector: ColourInterpolatorAffector deleted");
#endif
    	}
    }
};
#endif

