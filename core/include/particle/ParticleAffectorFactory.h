#ifndef __ParticleAffectorFactory_H__
#define __ParticleAffectorFactory_H__


#include "utils/include/prerequisites.h"
#include "ParticleAffector.h"

/** Abstract class defining the interface to be implemented by creators of ParticleAffector subclasses.
@remarks
	Plugins or 3rd party applications can add new types of particle affectors to Ogre by creating
	subclasses of the ParticleAffector class. Because multiple instances of these affectors may be
	required, a factory class to manage the instances is also required.
@par
	ParticleAffectorFactory subclasses must allow the creation and destruction of ParticleAffector
	subclasses. They must also be registered with the ParticleSystemManager. All factories have
	a name which identifies them, examples might be 'force_vector', 'attractor', or 'fader', and these can be
	also be used from particle system scripts.
*/
class ParticleAffectorFactory
{
protected:
	vector<ParticleAffector*> mAffectors;
public:
	ParticleAffectorFactory() {}
	virtual ~ParticleAffectorFactory(){};
	/** Returns the name of the factory, the name which identifies the particle affector type this factory creates. */
	virtual String getName() const = 0;

	/** Creates a new affector instance.
	@remarks
		The subclass MUST add a pointer to the created instance to mAffectors.
	*/
	virtual ParticleAffector* createAffector(ParticleSystem* psys) = 0;

	/** Destroys the affector pointed to by the parameter (for early clean up if required). */
	virtual void destroyAffector(ParticleAffector* e){};
};

#endif

