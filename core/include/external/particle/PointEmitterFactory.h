#ifndef __PointEmitterFactory_H__
#define __PointEmitterFactory_H__

#include "ParticlePrerequisites.h"
#include "particle/ParticleEmitterFactory.h"
#include "PointEmitter.h"

#ifdef _DEBUG_PARTICLE_SYSTEM_
#include "base/LogManager.h"
#endif

    /** Factory class for particle emitter of type "Point".
    @remarks
        Creates instances of PointEmitter to be used in particle systems. 
    */
    class PointEmitterFactory : public ParticleEmitterFactory
    {
    protected:

    public:
    	PointEmitterFactory();
    	~PointEmitterFactory();

        /** See ParticleEmitterFactory */
        String getName() const
        { 
            return "Point"; 
        }

        /** See ParticleEmitterFactory */
        ParticleEmitter* createEmitter(ParticleSystem* psys) 
        {
            ParticleEmitter* emit = new PointEmitter(psys);
#ifdef _DEBUG_PARTICLE_SYSTEM_
           LogManager::log(PS_LOG_TAG, "PointEmitterFactory::createEmitter: PointEmitter created");
#endif
            mEmitters.push_back(emit);
            return emit;
        }

        void destroyEmitter(ParticleEmitter* e)
        {
        	if (e != 0) {
        		delete e;
#ifdef _DEBUG_PARTICLE_SYSTEM_
        		LogManager::log(PS_LOG_TAG, "PointEmitterFactory::destroyEmitter: PointEmitter deleted");
#endif
        	}
        }

    };

#endif

