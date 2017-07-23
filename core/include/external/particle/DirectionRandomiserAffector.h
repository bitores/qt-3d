#ifndef __DirectionRandomiserAffector_H__
#define __DirectionRandomiserAffector_H__

#include "ParticlePrerequisites.h"
#include "particle/ParticleAffector.h"
#include "utils/include/Vector3.h"
/** This class defines a ParticleAffector which applies randomness to the movement of the particles.
@remarks
	This affector (see ParticleAffector) applies randomness to the movement of the particles by
	changing the direction vectors.
@par
	The most important parameter to control the effect is randomness. It controls the range in which changes
	are applied to each axis of the direction vector.
	The parameter scope can be used to limit the effect to a certain percentage of the particles.
*/
class DirectionRandomiserAffector : public ParticleAffector
{
public:
	/** Command object for randomness (see ParamCommand).*/
	class CmdRandomness : public ParamCommand
	{
	public:
		String doGet(const void* target) const;
		void doSet(void* target, const String& val);
	};

	/** Command object for scope (see ParamCommand).*/
	class CmdScope : public ParamCommand
	{
	public:
		String doGet(const void* target) const;
		void doSet(void* target, const String& val);
	};

	/** Command object for keep_velocity (see ParamCommand).*/
	class CmdKeepVelocity : public ParamCommand
	{
	public:
		String doGet(const void* target) const;
		void doSet(void* target, const String& val);
	};

	/// Default constructor
	DirectionRandomiserAffector(ParticleSystem* psys);

	/** See ParticleAffector. */
	void _affectParticles(ParticleSystem* pSystem, Real timeElapsed);


	/** Sets the randomness to apply to the particles in a system. */
	void setRandomness(Real force);
	/** Sets the scope (percentage of particles which are randomised). */
	void setScope(Real force);
	/** Set flag which detemines whether particle speed is changed. */
	void setKeepVelocity(bool keepVelocity);

	/** Gets the randomness to apply to the particles in a system. */
	Real getRandomness(void) const;
	/** Gets the scope (percentage of particles which are randomised). */
	Real getScope(void) const;
	/** Gets flag which detemines whether particle speed is changed. */
	bool getKeepVelocity(void) const;

	/// Command objects
	static CmdRandomness msRandomnessCmd;
	static CmdScope msScopeCmd;
	static CmdKeepVelocity msKeepVelocityCmd;

protected:
	Real mRandomness;
	Real mScope;
	bool mKeepVelocity;
};

#endif
