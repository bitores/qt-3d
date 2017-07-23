#ifndef __AreaEmitter_H__
#define __AreaEmitter_H__

#include "ParticlePrerequisites.h"
#include "particle/ParticleEmitter.h"

/** Particle emitter which emits particles randomly from points inside
	an area (box, sphere, ellipsoid whatever subclasses choose to be).
@remarks
	This is an empty superclass and needs to be subclassed. Basic particle
	emitter emits particles from/in an (unspecified) area. The
	initial direction of these particles can either be a single direction
	(i.e. a line), a random scattering inside a cone, or a random
	scattering in all directions, depending the 'angle' parameter, which
	is the angle across which to scatter the particles either side of the
	base direction of the emitter.
*/
class AreaEmitter : public ParticleEmitter
{
public:
	/** Command object for area emitter size (see ParamCommand).*/
	class CmdWidth : public ParamCommand
	{
	public:
		String doGet(const void* target) const;
		void doSet(void* target, const String& val);
	};
	/** Command object for area emitter size (see ParamCommand).*/
	class CmdHeight : public ParamCommand
	{
	public:
		String doGet(const void* target) const;
		void doSet(void* target, const String& val);
	};
	/** Command object for area emitter size (see ParamCommand).*/
	class CmdDepth : public ParamCommand
	{
	public:
		String doGet(const void* target) const;
		void doSet(void* target, const String& val);
	};

	/// Command object for particle emitter  - see ParamCommand
    class  CmdRangeFixed : public ParamCommand
    {
    public:
        String doGet(const void* target) const;
        void doSet(void* target, const String& val);
    };

	/// Command object for particle emitter  - see ParamCommand
    class  CmdRangeFactor : public ParamCommand
    {
    public:
        String doGet(const void* target) const;
        void doSet(void* target, const String& val);
    };

	/// Command object for particle emitter  - see ParamCommand
    class  CmdXRangeFactor : public ParamCommand
    {
    public:
        String doGet(const void* target) const;
        void doSet(void* target, const String& val);
    };

	/// Command object for particle emitter  - see ParamCommand
    class  CmdYRangeFactor : public ParamCommand
    {
    public:
        String doGet(const void* target) const;
        void doSet(void* target, const String& val);
    };

	/// Command object for particle emitter  - see ParamCommand
    class  CmdZRangeFactor : public ParamCommand
    {
    public:
        String doGet(const void* target) const;
        void doSet(void* target, const String& val);
    };

	AreaEmitter(ParticleSystem* psys);

	/** See ParticleEmitter. */
	unsigned short _getEmissionCount(Real timeElapsed);

	/** Overloaded to update the trans. matrix */
	void setDirection( const Vector3& direction );

	/** Sets the size of the area from which particles are emitted.
	@param
		size Vector describing the size of the area. The area extends
		around the center point by half the x, y and z components of
		this vector. The box is aligned such that it's local Z axis points
		along it's direction (see setDirection)
	*/
	void setSize(const Vector3& size);

	/** Sets the size of the area from which particles are emitted.
	@param x,y,z
		Individual axis lengths describing the size of the area. The area
		extends around the center point by half the x, y and z components
		of this vector. The box is aligned such that it's local Z axis
		points along it's direction (see setDirection)
	*/
	void setSize(Real x, Real y, Real z);
	/** Sets the size of the clear space inside the area from where NO particles are emitted.
	@param x,y,z
		Individual axis lengths describing the size of the clear space.
		The clear space is aligned like the outer area.
		(see setDirection and setSize)
	*/
//        void setClearSpace(Real x, Real y, Real z);

	/** Sets the width (local x size) of the emitter. */
	void setWidth(Real width);
	/** Gets the width (local x size) of the emitter. */
	Real getWidth(void) const;
	/** Sets the height (local y size) of the emitter. */
	void setHeight(Real Height);
	/** Gets the height (local y size) of the emitter. */
	Real getHeight(void) const;
	/** Sets the depth (local y size) of the emitter. */
	void setDepth(Real Depth);
	/** Gets the depth (local y size) of the emitter. */
	Real getDepth(void) const;

	bool isRangeFixed() const { return mIsRangeFixed; };
	void enableRangeFixed(bool isRangeFixed) { mIsRangeFixed = isRangeFixed; };

	void setRangeFactor(Real rangeFactor) {
//		mRangeFactor = rangeFactor;
		mXRangeFactor = mYRangeFactor = mZRangeFactor = rangeFactor;
	};
	Real getRangeFactor() const { return mXRangeFactor; };

	void setXRangeFactor(Real xRangeFactor) { mXRangeFactor = xRangeFactor; };
	Real getXRangeFactor() const { return mXRangeFactor; };

	void setYRangeFactor(Real yRangeFactor) { mYRangeFactor = yRangeFactor; };
	Real getYRangeFactor() const { return mYRangeFactor; };

	void setZRangeFactor(Real zRangeFactor) { mZRangeFactor = zRangeFactor; };
	Real getZRangeFactor() const { return mZRangeFactor; };

	void resize(Real deviceWidth, Real deviceHeight);
	virtual void copyParametersTo(StringInterface* dest) const;

protected:
	/// Size of the area
	Vector3 mSize;

	/// Local axes, not normalised, their magnitude reflects area size
	Vector3 mXRange, mYRange, mZRange;

	bool mIsRangeFixed;
	Real /*mRangeFactor, */mXRangeFactor, mYRangeFactor, mZRangeFactor;

	/// Internal method for generating the area axes
	void genAreaAxes(void);
	/** Internal for initializing some defaults and parameters
	@returns True if custom parameters need initialising
	*/
	bool initDefaults(const String& mType);

	/// Command objects
	static CmdWidth msWidthCmd;
	static CmdHeight msHeightCmd;
	static CmdDepth msDepthCmd;
	static CmdRangeFixed msRangeFixedCmd;
	static CmdRangeFactor msRangeFactorCmd;
	static CmdXRangeFactor msXRangeFactorCmd;
	static CmdYRangeFactor msYRangeFactorCmd;
	static CmdZRangeFactor msZRangeFactorCmd;
};
#endif

