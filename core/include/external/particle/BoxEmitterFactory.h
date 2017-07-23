#ifndef __BoxEmitterFactory_H__
#define __BoxEmitterFactory_H__

#include "ParticlePrerequisites.h"
#include "particle/ParticleEmitterFactory.h"
#include "BoxEmitter.h"

#ifdef _DEBUG_PARTICLE_SYSTEM_
#include "base/LogManager.h"
#endif

    /** Factory class for particle emitter of type "Box".
    @remarks
        Creates instances of BoxEmitter to be used in particle systems. 
    */
    class BoxEmitterFactory : public ParticleEmitterFactory
    {
    protected:

    public:
        /** See ParticleEmitterFactory */
        String getName() const
        { 
            return "Box"; 
        }

        /** See ParticleEmitterFactory */
        ParticleEmitter* createEmitter(ParticleSystem* psys) 
        {
            ParticleEmitter* emit = new BoxEmitter(psys);
            mEmitters.push_back(emit);
#ifdef _DEBUG_PARTICLE_SYSTEM_
			LogManager::log(PS_LOG_TAG, "BoxEmitterFactory::createEmitter: BoxEmitter created");
#endif
            return emit;
        }

        void destroyEmitter(ParticleEmitter* e)
        {
        	if (e != 0) {
        		delete e;
#ifdef _DEBUG_PARTICLE_SYSTEM_
        		LogManager::log(PS_LOG_TAG, "BoxEmitterFactory::destroyEmitter: BoxEmitter deleted");
#endif
        	}
        }


    };
#endif

