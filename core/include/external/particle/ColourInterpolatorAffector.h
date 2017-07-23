#ifndef __ColourInterpolatorAffector_H__
#define __ColourInterpolatorAffector_H__

#include "ParticlePrerequisites.h"
#include "particle/ParticleAffector.h"
#include "utils/include/ColourValue.h"

class ColourInterpolatorAffector : public ParticleAffector
{
public:
	// this is something of a hack..
	// needs to be replaced with something more..
	// ..elegant
	enum { MAX_STAGES = 6 };


	/** Command object for red adjust (see ParamCommand).*/
	class CmdColourAdjust : public ParamCommand
	{
	public:
		size_t		mIndex;

	public:
		String doGet(const void* target) const;
		void doSet(void* target, const String& val);
	};

	/** Command object for red adjust (see ParamCommand).*/
	class CmdTimeAdjust : public ParamCommand
	{
	public:
		size_t		mIndex;

	public:
		String doGet(const void* target) const;
		void doSet(void* target, const String& val);
	};

	/** Default constructor. */
	ColourInterpolatorAffector(ParticleSystem* psys);

	/** See ParticleAffector. */
	void _affectParticles(ParticleSystem* pSystem, Real timeElapsed);

	void setColourAdjust(size_t index, ColourValue colour);
	ColourValue getColourAdjust(size_t index) const;

	void setTimeAdjust(size_t index, Real time);
	Real getTimeAdjust(size_t index) const;


	static CmdColourAdjust	msColourCmd[MAX_STAGES];
	static CmdTimeAdjust	msTimeCmd[MAX_STAGES];

protected:
	ColourValue				mColourAdj[MAX_STAGES];
	Real					mTimeAdj[MAX_STAGES];

};

#endif

