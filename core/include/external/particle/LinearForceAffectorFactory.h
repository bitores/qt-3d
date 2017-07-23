#ifndef __LinearForceAffectorFactory_H__
#define __LinearForceAffectorFactory_H__

#include "ParticlePrerequisites.h"
#include "particle/ParticleAffectorFactory.h"
#include "LinearForceAffector.h"
#ifdef _DEBUG_PARTICLE_SYSTEM_
#include "base/LogManager.h"
#endif

/** Factory class for LinearForceAffector. */
class LinearForceAffectorFactory : public ParticleAffectorFactory
{
	/** See ParticleAffectorFactory */
	String getName() const { return "LinearForce"; }

	/** See ParticleAffectorFactory */
	ParticleAffector* createAffector(ParticleSystem* psys)
	{
		ParticleAffector* p = new LinearForceAffector(psys);
		mAffectors.push_back(p);
#ifdef _DEBUG_PARTICLE_SYSTEM_
		LogManager::log(PS_LOG_TAG, "LinearForceAffectorFactory::createAffector: LinearForceAffector created");
#endif
		return p;
	}

    void destroyAffector(ParticleAffector* e)
    {
    	if (0 != e) {
    		delete e;
#ifdef _DEBUG_PARTICLE_SYSTEM_
    		LogManager::log(PS_LOG_TAG, "LinearForceAffectorFactory::destroyAffector: LinearForceAffector deleted");
#endif
    	}
    }
};
#endif

