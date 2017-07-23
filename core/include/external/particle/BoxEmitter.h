#ifndef __BoxEmitter_H__
#define __BoxEmitter_H__

#include "ParticlePrerequisites.h"
#include "AreaEmitter.h"

    /** Particle emitter which emits particles randomly from points inside a box.
    @remarks
        This basic particle emitter emits particles from a box area. The
        initial direction of these particles can either be a single direction (i.e. a line),
        a random scattering inside a cone, or a random scattering in all directions, 
        depending the 'angle' parameter, which is the angle across which to scatter the 
        particles either side of the base direction of the emitter. 
    */
    class BoxEmitter : public AreaEmitter
    {
    public:

        BoxEmitter(ParticleSystem* psys);

        /** See ParticleEmitter. */
        void _initParticle(Particle* pParticle);

    protected:

    };

#endif

