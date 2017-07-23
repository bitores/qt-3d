#ifndef __CompositorTargetPass_h__
#define __CompositorTargetPass_h__

#include "utils/include/prerequisites.h"
#include "base/Object.h"
#include "utils/include/IteratorWrapper.h"


class CompositorTargetPass : public Object
{
private:

public:
	CompositorTargetPass(Compositor* parent);
	~CompositorTargetPass();

	 /** Input mode of a TargetPass
	*/
	enum InputMode
	{
		IM_NONE,        /// No input
		IM_PREVIOUS     /// Output of previous Composition in chain
	};

	typedef vector<CompositorPass *> Passes;
	typedef VectorIterator<Passes> PassIterator;

	/** Set input mode of this TargetPass
	*/
	void setInputMode(InputMode mode);
	/** Get input mode */
	InputMode getInputMode() const;
	/** Set output local texture name */
	void setOutputName(const String &out);
	/** Get output local texture name */
	const String &getOutputName() const;
	/** Set "only initial" flag. This makes that this target pass is only executed initially
		after the effect has been enabled.
	*/
	void setOnlyInitial(bool value);
	/** Get "only initial" flag.
	*/
	bool getOnlyInitial();

	/** Set the scene visibility mask used by this pass
	*/
	void setVisibilityMask(uint32 mask);
	/** Get the scene visibility mask used by this pass
	*/
	uint32 getVisibilityMask();
	/** Set whether shadows are enabled in this target pass.
	@remarks
		Only applicable to targets that render the scene as
		one of their passes.
	*/
	void setShadowsEnabled(bool enabled);
	/** Get whether shadows are enabled in this target pass.
	@remarks
		Only applicable to targets that render the scene as
		one of their passes.
	*/
	bool getShadowsEnabled(void) const;
	/** Set the scene LOD bias used by this pass. The default is 1.0,
		everything below that means lower quality, higher means higher quality.
	*/
	void setLodBias(float bias);
	/** Get the scene LOD bias used by this pass
	*/
	float getLodBias();
	/** Create a new pass, and return a pointer to it.
	*/
	CompositorPass *createPass();
	/** Remove a pass. It will also be destroyed.
	*/
	void removePass(size_t idx);
	/** Get a pass.
	*/
	CompositorPass *getPass(size_t idx);
	/** Get the number of passes.
	*/
	size_t getNumPasses();
	/** Remove all passes
	*/
	void removeAllPasses();
	/** Get an iterator over the Passes in this TargetPass. */
	PassIterator getPassIterator(void) {return PassIterator(mPasses.begin(), mPasses.end());}
	/** Get parent compositor
	 */
	Compositor* getParent() {return mParent;}

private:
	/// Parent compositor
	Compositor* mParent;
	/// Input mode
	InputMode mInputMode;
	/// (local) output texture
	String mOutputName;
	/// Passes
	Passes mPasses;

	/// This target pass is only executed initially after the effect
	/// has been enabled.
	bool mOnlyInitial;
	/// Visibility mask for this render
	uint32 mVisibilityMask;
	/// LOD bias of this render
	float mLodBias;
	/// Material scheme name
	//String mMaterialScheme;
	/// Shadows option
	bool mShadowsEnabled;
};
#endif
