#ifndef __ColourFaderAffector_H__
#define __ColourFaderAffector_H__

#include "ParticlePrerequisites.h"
#include "particle/ParticleAffector.h"

    /** This plugin subclass of ParticleAffector allows you to alter the colour of particles.
    @remarks
        This class supplies the ParticleAffector implementation required to modify the colour of
        particle in mid-flight.
    */
    class ColourFaderAffector : public ParticleAffector
    {
    public:

        /** Command object for red adjust (see ParamCommand).*/
        class CmdRedAdjust : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

        /** Command object for green adjust (see ParamCommand).*/
        class CmdGreenAdjust : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

        /** Command object for blue adjust (see ParamCommand).*/
        class CmdBlueAdjust : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

        /** Command object for alpha adjust (see ParamCommand).*/
        class CmdAlphaAdjust : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };


        /** Default constructor. */
        ColourFaderAffector(ParticleSystem* psys);

        /** See ParticleAffector. */
        void _affectParticles(ParticleSystem* pSystem, Real timeElapsed);

        /** Sets the colour adjustment to be made per second to particles. 
        @param red, green, blue, alpha
            Sets the adjustment to be made to each of the colour components per second. These
            values will be added to the colour of all particles every second, scaled over each frame
            for a smooth adjustment.
        */
        void setAdjust(float red, float green, float blue, float alpha = 0.0);
        /** Sets the red adjustment to be made per second to particles. 
        @param red
            The adjustment to be made to the colour component per second. This
            value will be added to the colour of all particles every second, scaled over each frame
            for a smooth adjustment.
        */
        void setRedAdjust(float red);

        /** Gets the red adjustment to be made per second to particles. */
        float getRedAdjust(void) const;

        /** Sets the green adjustment to be made per second to particles. 
        @param green
            The adjustment to be made to the colour component per second. This
            value will be added to the colour of all particles every second, scaled over each frame
            for a smooth adjustment.
        */
        void setGreenAdjust(float green);
        /** Gets the green adjustment to be made per second to particles. */
        float getGreenAdjust(void) const;
        /** Sets the blue adjustment to be made per second to particles. 
        @param blue
            The adjustment to be made to the colour component per second. This
            value will be added to the colour of all particles every second, scaled over each frame
            for a smooth adjustment.
        */
        void setBlueAdjust(float blue);
        /** Gets the blue adjustment to be made per second to particles. */
        float getBlueAdjust(void) const;

        /** Sets the alpha adjustment to be made per second to particles. 
        @param alpha
            The adjustment to be made to the colour component per second. This
            value will be added to the colour of all particles every second, scaled over each frame
            for a smooth adjustment.
        */
        void setAlphaAdjust(float alpha);
        /** Gets the alpha adjustment to be made per second to particles. */
        float getAlphaAdjust(void) const;

        static CmdRedAdjust msRedCmd;
        static CmdGreenAdjust msGreenCmd;
        static CmdBlueAdjust msBlueCmd;
        static CmdAlphaAdjust msAlphaCmd;

    protected:
        float mRedAdj;
        float mGreenAdj;
        float mBlueAdj;
        float mAlphaAdj;

        /** Internal method for adjusting while clamping to [0,1] */
        inline void applyAdjustWithClamp(float* pComponent, float adjust)
        {
            *pComponent += adjust;
            // Limit to 0
            if (*pComponent < 0.0)
            {
                *pComponent = 0.0f;
            }
            // Limit to 1
            else if (*pComponent > 1.0)
            {
                *pComponent = 1.0f;
            }
        }

    };

#endif

