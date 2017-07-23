#ifndef __TextureAffector_H__
#define __TextureAffector_H__

#include "ParticlePrerequisites.h"
#include "particle/ParticleAffector.h"
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
    class TextureAffector : public ParticleAffector
    {
    public:
        class CmdMinTexcoordIndex : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

        class CmdMaxTexcoordIndex : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

        class CmdDeltaTime : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

        class CmdAffectMode : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

        class CmdFromTime : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

        class CmdToTime : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

        enum TextureAffectMode
        {
            ALL_TIME,
            PART_TIME
        };

        /// Default constructor
    	TextureAffector(ParticleSystem* psys);

        /** See ParticleAffector. */
        void _affectParticles(ParticleSystem* pSystem, Real timeElapsed);

        void setMinTexcoordIndex(unsigned int minTexcoordIndex);
        unsigned int getMinTexcoordIndex() const;

        void setMaxTexcoordIndex(unsigned int maxTexcoordIndex);
        unsigned int getMaxTexcoordIndex() const;

        void setDeltaTime(float deltaTime);
        float getDeltaTime() const;

        void setTextureAffectMode(TextureAffectMode mode);
        TextureAffectMode getTextureAffectMode() const;

        void setFromTime(float fromTime);
        float getFromTime() const;

        void setToTime(float toTime);
        float getToTime() const;

        /// Command objects
        static CmdMinTexcoordIndex msMinTexcoordIndex;
        static CmdMaxTexcoordIndex msMaxTexcoordIndex;
        static CmdDeltaTime msDeltaTime;
        static CmdAffectMode msAffectMode;
        static CmdFromTime msFromTime;
        static CmdToTime msToTime;

    protected:
        unsigned int mMinTexcoordIndex;
        unsigned int mMaxTexcoordIndex;

        float mDeltaTime;
        float mPastDeltaTime;

        float mFromTime;
        float mToTime;

        TextureAffectMode mTextureAffectMode;
    };
#endif

