#ifndef __DirectionRandomiserAffectorFactory_H__
#define __DirectionRandomiserAffectorFactory_H__

#include "ParticlePrerequisites.h"
#include "particle/ParticleAffectorFactory.h"
#include "DirectionRandomiserAffector.h"
#ifdef _DEBUG_PARTICLE_SYSTEM_
#include "base/LogManager.h"
#endif
/** Factory class for DirectionRandomiserAffector. */
class DirectionRandomiserAffectorFactory : public ParticleAffectorFactory
{
	/** See ParticleAffectorFactory */
	String getName() const { return "DirectionRandomiser"; }

	/** See ParticleAffectorFactory */
	ParticleAffector* createAffector(ParticleSystem* psys)
	{
		ParticleAffector* p = new DirectionRandomiserAffector(psys);
		mAffectors.push_back(p);
#ifdef _DEBUG_PARTICLE_SYSTEM_
		LogManager::log(PS_LOG_TAG, "DirectionRandomiserAffectorFactory::createAffector: DirectionRandomiserAffector created");
#endif
		return p;
	}

	void destroyAffector(ParticleAffector* e)
	{
		if (0 != e) {
			delete e;
#ifdef _DEBUG_PARTICLE_SYSTEM_
			LogManager::log(PS_LOG_TAG, "DirectionRandomiserAffectorFactory::destroyAffector: DirectionRandomiserAffector deleted");
#endif
		}
	}
};

#endif
