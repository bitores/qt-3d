#ifndef __CosineAffector_H__
#define __CosineAffector_H__

#include "ParticlePrerequisites.h"
#include "particle/ParticleAffector.h"
#include "animation/InterpolatorSet.h"
//#include "utils/include/Vector3.h"


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
    class RandomCurveAffector : public ParticleAffector
    {
    public:

        class CmdScaledX : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

        class CmdScaledY : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

        class CmdScaledZ : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

        class  CmdScaleFixed : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

        class  CmdScaleFactor : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

        class  CmdActiveMode : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /// Default constructor
        RandomCurveAffector(ParticleSystem* psys);
    	~RandomCurveAffector();

        /** See ParticleAffector. */
        void _affectParticles(ParticleSystem* pSystem, Real timeElapsed);

        void setScaledX(float scaledX);
        float getScaledX() const;

        void setScaledY(float scaledY);
        float getScaledY() const;

        void setScaledZ(float scaledZ);
        float getScaledZ() const;

		Real getScaleFactor() const;
		void setScaleFactor(Real scaleFactor);

		bool isScaleFixed() const;
		void enableScaleFixed(bool isScaleFixed);

		void setActiveMode(String mode);
		String getActiveMode() const;

        /// Command objects
        static CmdScaledX msScaledXCmd;
        static CmdScaledY msScaledYCmd;
        static CmdScaledZ msScaledZCmd;
        static CmdScaleFixed msScaleFixedCmd;
        static CmdScaleFactor msScaleFactorCmd;
        static CmdActiveMode msActiveMode;

    private:
        void _initialInterpolatorSet();

    protected:
          float mScaledX;
          float mScaledY;
          float mScaledZ;

          bool mIsScaleFixed;
          Real mScaleFactor; // fit to device

          String mActiveMode;
          InterpolatorSet mInterpolatorSet;
    };
#endif

