#ifndef __RotationAffectorFactory_H__
#define __RotationAffectorFactory_H__

#include "ParticlePrerequisites.h"
#include "particle/ParticleAffectorFactory.h"
#include "RotationAffector.h"
#ifdef _DEBUG_PARTICLE_SYSTEM_
#include "base/LogManager.h"
#endif

/** Factory class for RotationAffector. */
class RotationAffectorFactory : public ParticleAffectorFactory
{
	/** See ParticleAffectorFactory */
	String getName() const { return "Rotator"; }

	/** See ParticleAffectorFactory */
	ParticleAffector* createAffector(ParticleSystem* psys)
	{
		ParticleAffector* p = new RotationAffector(psys);
		mAffectors.push_back(p);
#ifdef _DEBUG_PARTICLE_SYSTEM_
		LogManager::log(PS_LOG_TAG, "RotationAffectorFactory::createAffector: RotationAffector created");
#endif
		return p;
	}

    void destroyAffector(ParticleAffector* e)
    {
    	if (0 != e) {
    		delete e;
#ifdef _DEBUG_PARTICLE_SYSTEM_
    		LogManager::log(PS_LOG_TAG, "RotationAffectorFactory::destroyAffector: RotationAffector deleted");
#endif
    	}
    }
};
#endif

