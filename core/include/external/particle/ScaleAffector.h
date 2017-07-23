#ifndef __ScaleAffector_H__
#define __ScaleAffector_H__

#include "ParticlePrerequisites.h"
#include "particle/ParticleAffector.h"


/** This plugin subclass of ParticleAffector allows you to alter the scale of particles.
@remarks
	This class supplies the ParticleAffector implementation required to make the particle expand
	or contract in mid-flight.
*/
class ScaleAffector : public ParticleAffector
{
public:

	/** Command object for scale adjust (see ParamCommand).*/
    class CmdScaleAdjust : public ParamCommand
    {
    public:
        String doGet(const void* target) const;
        void doSet(void* target, const String& val);
    };
	class CmdWidthScaleAdjust : public ParamCommand
	{
	public:
		String doGet(const void* target) const;
		void doSet(void* target, const String& val);
	};
	class CmdHeightScaleAdjust : public ParamCommand
	{
	public:
		String doGet(const void* target) const;
		void doSet(void* target, const String& val);
	};

	/** Default constructor. */
	ScaleAffector(ParticleSystem* psys);

	/** See ParticleAffector. */
	void _affectParticles(ParticleSystem* pSystem, Real timeElapsed);

	/** Sets the scale adjustment to be made per second to particles.
	@param Rate
		Sets the adjustment to be made to the x and y scale components per second. These
		values will be added to the scale of all particles every second, scaled over each frame
		for a smooth adjustment.
	*/
	void setAdjust( Real rate );
    Real getAdjust(void) const;

	void setWidthAdjust( Real widthRate );
	Real getWidthAdjust(void) const;

	void setHeightAdjust( Real heightRate );
	Real getHeightAdjust(void) const;

    static CmdScaleAdjust msScaleCmd;
	static CmdWidthScaleAdjust msWidthScaleCmd;
	static CmdHeightScaleAdjust msHeightScaleCmd;

protected:
    Real mScaleAdj;
	Real mWidthScaleAdj;
	Real mHeightScaleAdj;
};
#endif

