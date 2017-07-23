#ifndef __ColourFaderAffectorFactory2_H__
#define __ColourFaderAffectorFactory2_H__

#include "ParticlePrerequisites.h"
#include "particle/ParticleAffectorFactory.h"
#include "ColourFaderAffector2.h"

#ifdef _DEBUG_PARTICLE_SYSTEM_
#include "base/LogManager.h"
#endif


    /** Factory class for ColourFaderAffector2. */
    class ColourFaderAffectorFactory2 : public ParticleAffectorFactory
    {
    public:
    	ColourFaderAffectorFactory2();
    	~ColourFaderAffectorFactory2();

        /** See ParticleAffectorFactory */
        String getName() const { return "ColourFader2"; }

        /** See ParticleAffectorFactory */
        ParticleAffector* createAffector(ParticleSystem* psys)
        {
            ParticleAffector* p = new ColourFaderAffector2(psys);
            mAffectors.push_back(p);
#ifdef _DEBUG_PARTICLE_SYSTEM_
            LogManager::log(PS_LOG_TAG, "ColourFaderAffectorFactory2::createAffector: ColourFaderAffector2 created");
#endif
            return p;
        }

        void destroyAffector(ParticleAffector* e)
        {
        	if (0 != e) {
        		delete e;
#ifdef _DEBUG_PARTICLE_SYSTEM_
        		LogManager::log(PS_LOG_TAG, "ColourFaderAffectorFactory2::destroyAffector: ColourFaderAffector2 deleted");
#endif
        	}
        }
    };

#endif

