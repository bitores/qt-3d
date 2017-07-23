#ifndef __RotationAffector_H__
#define __RotationAffector_H__

#include "utils/include/mathlib.h"
#include "ParticlePrerequisites.h"
#include "particle/ParticleAffector.h"

/** This plugin subclass of ParticleAffector allows you to alter the rotation of particles.
@remarks
	This class supplies the ParticleAffector implementation required to make the particle expand
	or contract in mid-flight.
*/
class RotationAffector : public ParticleAffector
{
public:
	/// Command object for particle emitter  - see ParamCommand
	class CmdRotationSpeedRangeStart : public ParamCommand
	{
	public:
		String doGet(const void* target) const;
		void doSet(void* target, const String& val);
	};

	/// Command object for particle emitter  - see ParamCommand
	class CmdRotationSpeedRangeEnd : public ParamCommand
	{
	public:
		String doGet(const void* target) const;
		void doSet(void* target, const String& val);
	};

	/// Command object for particle emitter  - see ParamCommand
	class CmdRotationRangeStart : public ParamCommand
	{
	public:
		String doGet(const void* target) const;
		void doSet(void* target, const String& val);
	};

	/// Command object for particle emitter  - see ParamCommand
	class CmdRotationRangeEnd : public ParamCommand
	{
	public:
		String doGet(const void* target) const;
		void doSet(void* target, const String& val);
	};

	class CmdSyncWithDirection : public ParamCommand
	{
	public:
		String doGet(const void* target) const;
		void doSet(void* target, const String& val);
	};

	/** Default constructor. */
	RotationAffector(ParticleSystem* psys);

	/** See ParticleAffector. */
	void _initParticle(Particle* pParticle);

	/** See ParticleAffector. */
	void _affectParticles(ParticleSystem* pSystem, Real timeElapsed);



	/** Sets the minimum rotation speed of particles to be emitted. */
	void setRotationSpeedRangeStart(const Radian& angle);
	/** Sets the maximum rotation speed of particles to be emitted. */
	void setRotationSpeedRangeEnd(const Radian& angle);
	/** Gets the minimum rotation speed of particles to be emitted. */
	const Radian& getRotationSpeedRangeStart(void) const;
	/** Gets the maximum rotation speed of particles to be emitted. */
	const Radian& getRotationSpeedRangeEnd(void) const;


	/** Sets the minimum rotation angle of particles to be emitted. */
	void setRotationRangeStart(const Radian& angle);
	/** Sets the maximum rotation angle of particles to be emitted. */
	void setRotationRangeEnd(const Radian& angle);
	/** Gets the minimum rotation of particles to be emitted. */
	const Radian& getRotationRangeStart(void) const;
	/** Gets the maximum rotation of particles to be emitted. */
	const Radian& getRotationRangeEnd(void) const;

    void enableSyncWithDirection(bool sync);
    const bool isSyncWithDirection() const;

	static CmdRotationSpeedRangeStart	msRotationSpeedRangeStartCmd;
	static CmdRotationSpeedRangeEnd		msRotationSpeedRangeEndCmd;
	static CmdRotationRangeStart		msRotationRangeStartCmd;
	static CmdRotationRangeEnd			msRotationRangeEndCmd;
	static CmdSyncWithDirection			msSyncWithDirectionCmd;

protected:
	/// Initial rotation speed of particles (range start)
	Radian mRotationSpeedRangeStart;
	/// Initial rotation speed of particles (range end)
	Radian mRotationSpeedRangeEnd;
	/// Initial rotation angle of particles (range start)
	Radian mRotationRangeStart;
	/// Initial rotation angle of particles (range end)
	Radian mRotationRangeEnd;

    bool mSyncWithDirection;

    Radian genAngleWithDirection(Vector3& direction);
    };
#endif

