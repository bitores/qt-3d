#ifndef __ScaleAffectorFactory_H__
#define __ScaleAffectorFactory_H__

#include "ParticlePrerequisites.h"
#include "particle/ParticleAffectorFactory.h"
#include "ScaleAffector.h"
#ifdef _DEBUG_PARTICLE_SYSTEM_
#include "base/LogManager.h"
#endif
/** Factory class for ScaleAffector. */
class ScaleAffectorFactory : public ParticleAffectorFactory
{
	/** See ParticleAffectorFactory */
	String getName() const { return "Scaler"; }

	/** See ParticleAffectorFactory */
	ParticleAffector* createAffector(ParticleSystem* psys)
	{
		ParticleAffector* p = new ScaleAffector(psys);
		mAffectors.push_back(p);
#ifdef _DEBUG_PARTICLE_SYSTEM_
		LogManager::log(PS_LOG_TAG, "ScaleAffectorFactory::createAffector: ScaleAffector created");
#endif
		return p;
	}

    void destroyAffector(ParticleAffector* e)
    {
    	if (0 != e) {
    		delete e;
#ifdef _DEBUG_PARTICLE_SYSTEM_
    		LogManager::log(PS_LOG_TAG, "ScaleAffectorFactory::destroyAffector: ScaleAffector deleted");
#endif
    	}
    }
};

#endif

