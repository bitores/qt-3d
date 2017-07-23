#ifndef __LinearForceAffector_H__
#define __LinearForceAffector_H__

#include "ParticlePrerequisites.h"
#include "particle/ParticleAffector.h"
#include "utils/include/Vector3.h"


    /** This class defines a ParticleAffector which applies a linear force to particles in a system.
    @remarks
        This affector (see ParticleAffector) applies a linear force, such as gravity, to a particle system.
        This force can be applied in 2 ways: by taking the average of the particle's current momentum and the 
        force vector, or by adding the force vector to the current particle's momentum. 
    @par
        The former approach is self-stabilising i.e. once a particle's momentum
        is equal to the force vector, no further change is made to it's momentum. It also results in
        a non-linear acceleration of particles.
        The latter approach is simpler and applies a constant acceleration to particles. However,
        it is not self-stabilising and can lead to perpetually increasing particle velocities. 
        You choose the approach by calling the setForceApplication method.
    */
    class LinearForceAffector : public ParticleAffector
    {
    public:
        /** Command object for force vector (see ParamCommand).*/
        class CmdForceVector : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

        /** Command object for force application (see ParamCommand).*/
        class CmdForceApp : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

        class CmdProductAjustFactor : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

        /// Choice of how to apply the force vector to particles
        enum ForceApplication
        {
            /// Take the average of the force vector and the particle momentum
            FA_AVERAGE,
            /// Add the force vector to the particle momentum
            FA_ADD,
            FA_PRODUCT
        };
        /// Default constructor
        LinearForceAffector(ParticleSystem* psys);

        /** See ParticleAffector. */
        void _affectParticles(ParticleSystem* pSystem, Real timeElapsed);


        /** Sets the force vector to apply to the particles in a system. */
        void setForceVector(const Vector3& force);

        /** Gets the force vector to apply to the particles in a system. */
        Vector3 getForceVector(void) const;

        /** Sets how the force vector is applied to a particle. 
        @remarks
          The default is FA_ADD.
        @param fa A member of the ForceApplication enum.
        */
        void setForceApplication(ForceApplication fa);

        /** Retrieves how the force vector is applied to a particle. 
        @param fa A member of the ForceApplication enum.
        */
        ForceApplication getForceApplication(void) const;

        void setProductAjustFactor(Real productAjustFactor);

        Real getProductAjustFactor() const;

        /// Command objects
        static CmdForceVector msForceVectorCmd;
        static CmdForceApp msForceAppCmd;
        static CmdProductAjustFactor msProductAjustFactorCmd;

    protected:
        /// Force vector
        Vector3 mForceVector;
        Real mProductAjustFactor;

        /// How to apply force
        ForceApplication mForceApplication;

    };
#endif

