#ifndef __TextureAffectorFactory_H__
#define __TextureAffectorFactory_H__

#include "ParticlePrerequisites.h"
#include "particle/ParticleAffectorFactory.h"
#include "TextureAffector.h"
#ifdef _DEBUG_PARTICLE_SYSTEM_
#include "base/LogManager.h"
#endif

/** Factory class for TextureAffector. */
class TextureAffectorFactory : public ParticleAffectorFactory
{
	/** See ParticleAffectorFactory */
	String getName() const { return "Texture"; }

	/** See ParticleAffectorFactory */
	ParticleAffector* createAffector(ParticleSystem* psys)
	{
		ParticleAffector* p = new TextureAffector(psys);
		mAffectors.push_back(p);
#ifdef _DEBUG_PARTICLE_SYSTEM_
		LogManager::log(PS_LOG_TAG, "TextureAffectorFactory::createAffector: TextureAffector created");
#endif
		return p;
	}

    void destroyAffector(ParticleAffector* e)
    {
    	if (0 != e) {
    		delete e;
#ifdef _DEBUG_PARTICLE_SYSTEM_
    		LogManager::log(PS_LOG_TAG, "TextureAffectorFactory::destroyAffector: TextureAffector deleted");
#endif
    	}
    }
};
#endif

