#ifndef __ColourFaderAffectorFactory_H__
#define __ColourFaderAffectorFactory_H__

#include "ParticlePrerequisites.h"
#include "particle/ParticleAffectorFactory.h"
#include "ColourFaderAffector.h"

#ifdef _DEBUG_PARTICLE_SYSTEM_
#include "base/LogManager.h"
#endif
    /** Factory class for ColourFaderAffector. */
    class ColourFaderAffectorFactory : public ParticleAffectorFactory
    {
    public:
    	ColourFaderAffectorFactory();
    	~ColourFaderAffectorFactory();

        /** See ParticleAffectorFactory */
        String getName() const { return "ColourFader"; }

        /** See ParticleAffectorFactory */
        ParticleAffector* createAffector(ParticleSystem* psys)
        {
            ParticleAffector* p = new ColourFaderAffector(psys);
            mAffectors.push_back(p);
#ifdef _DEBUG_PARTICLE_SYSTEM_
            LogManager::log(PS_LOG_TAG, "ColourFaderAffectorFactory::createAffector: ColourFaderAffector created");
#endif
            return p;
        }

        void destroyAffector(ParticleAffector* e)
        {
        	if (0 != e) {
        		delete e;
#ifdef _DEBUG_PARTICLE_SYSTEM_
        		LogManager::log(PS_LOG_TAG, "ColourFaderAffectorFactory::destroyAffector: ColourFaderAffector deleted");
#endif
        	}
        }
    };

#endif

