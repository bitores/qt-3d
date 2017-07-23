#ifndef __TextureFrameAffector_H__
#define __TextureFrameAffector_H__

#include "ParticlePrerequisites.h"
#include "particle/ParticleAffector.h"

class TextureFrameAffector : public ParticleAffector
{
public:
	// this is something of a hack..
	// needs to be replaced with something more..
	// ..elegant
	enum { MAX_STAGES = 6 };


	/** Command object for red adjust (see ParamCommand).*/
	class CmdFrameAdjust : public ParamCommand
	{
	public:
		uint32		mIndex;

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
	TextureFrameAffector(ParticleSystem* psys);

	/** See ParticleAffector. */
	void _affectParticles(ParticleSystem* pSystem, Real timeElapsed);

	void setFrameAdjust(uint32 index, uint32 frame);
	uint32 getFrameAdjust(size_t index) const;

	void setTimeAdjust(uint32 index, Real time);
	Real getTimeAdjust(uint32 index) const;


	static CmdFrameAdjust	msFrameCmd[MAX_STAGES];
	static CmdTimeAdjust		msTimeCmd[MAX_STAGES];

protected:
	uint32					mFrameAdj[MAX_STAGES];
	Real					mTimeAdj[MAX_STAGES];

};


#endif

