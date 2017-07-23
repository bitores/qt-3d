#ifndef __CompositorChain_h__
#define __CompositorChain_h__

#include "utils/include/prerequisites.h"
#include "compositor/CompositorInstance.h"
#include "rendersystem/RenderTargetListener.h"
#include "scenegraph/SceneManager.h"
#include "base/Viewport.h"


class CompositorChain : public RenderTargetListener, public Viewport::Listener
{
public:
	CompositorChain(Viewport* vp, CompositorManager* compManager);
	~CompositorChain();

	/// Identifier for "last" compositor in chain.
	static const size_t LAST = (size_t)-1;

	typedef vector<CompositorInstance*> Instances;
	typedef VectorIterator<Instances> InstanceIterator;

	/** Apply a compositor. Initially, the filter is enabled.
	@param filter
		Filter to apply.
	@param addPosition
		Position in filter chain to insert this filter at; defaults to the end (last applied filter).
	@param scheme
		Scheme to use (blank means default).
	*/
	CompositorInstance* addCompositor(CompositorPtr filter, size_t addPosition=LAST);

	/** Remove a compositor.
	@param position
		Position in filter chain of filter to remove; defaults to the end (last applied filter)
	*/
	void removeCompositor(size_t position=LAST);

	/** Get the number of compositors.
	*/
	size_t getNumCompositors();

	/** Remove all compositors.
	*/
	void removeAllCompositors();

	/** Get compositor instance by position.
	*/
	CompositorInstance *getCompositor(size_t index);

	/** Get compositor instance by name. Returns null if not found.
	*/
	CompositorInstance *getCompositor(const String& name);

	/** Get the original scene compositor instance for this chain (internal use).
	*/
	CompositorInstance* _getOriginalSceneCompositor(void) { return mOriginalScene; }

	/** Get an iterator over the compositor instances. The first compositor in this list is applied first, the last one is applied last.
	*/
	InstanceIterator getCompositors();

	/** Enable or disable a compositor, by position. Disabling a compositor stops it from rendering
		but does not free any resources. This can be more efficient than using removeCompositor and
		addCompositor in cases the filter is switched on and off a lot.
	@param position
		Position in filter chain of filter
	*/
	void setCompositorEnabled(size_t position, bool state);

	 /** @see RenderTargetListener::preRenderTargetUpdate */
	virtual void preRenderTargetUpdate(const RenderTargetEvent& evt);
	/** @see RenderTargetListener::postRenderTargetUpdate */
	virtual void postRenderTargetUpdate(const RenderTargetEvent& evt);
	/** @see RenderTargetListener::preViewportUpdate */
	virtual void preViewportUpdate(const RenderTargetViewportEvent& evt);
	/** @see RenderTargetListener::postViewportUpdate */
	virtual void postViewportUpdate(const RenderTargetViewportEvent& evt);

	/** @see Viewport::Listener::viewportCameraChanged */
	virtual void viewportCameraChanged(Viewport* viewport);
	/** @see Viewport::Listener::viewportDimensionsChanged */
	virtual void viewportDimensionsChanged(Viewport* viewport);
	/** @see Viewport::Listener::viewportDestroyed */
	virtual void viewportDestroyed(Viewport* viewport);

	/** Mark state as dirty, and to be recompiled next frame.
	*/
	void _markDirty();

	/** Get viewport that is the target of this chain
	*/
	Viewport *getViewport() {return mViewport;}

	/** Remove a compositor by pointer. This is internally used by CompositionTechnique to
		"weak" remove any instanced of a deleted technique.
	*/
	void _removeInstance(CompositorInstance *i);

	/** Internal method for registering a queued operation for deletion later **/
	void _queuedOperation(CompositorInstance::RenderSystemOperation* op);

	/** Compile this Composition chain into a series of RenderTarget operations.
	*/
	void _compile();

	/** Get the previous instance in this chain to the one specified.
	*/
	CompositorInstance* getPreviousInstance(CompositorInstance* curr, bool activeOnly = true);
	/** Get the next instance in this chain to the one specified.
	*/
	CompositorInstance* getNextInstance(CompositorInstance* curr, bool activeOnly = true);

	CompositorManager* getCompositorManager();

protected:
   /// Viewport affected by this CompositorChain
   Viewport *mViewport;

   CompositorManager* mCompositorManager;

   /** Plainly renders the scene; implicit first compositor in the chain.
   */
   CompositorInstance *mOriginalScene;

   /// Postfilter instances in this chain
   Instances mInstances;

	/// State needs recompile
	bool mDirty;

	/// Any compositors enabled?
	bool mAnyCompositorsEnabled;

	/// Compiled state (updated with _compile)
	/// typedef vector<TargetOperation>::type CompiledState;
	CompositorInstance::CompiledState mCompiledState;
	CompositorInstance::TargetOperation mOutputOperation;

	/// Render System operations queued by last compile, these are created by this
	/// instance thus managed and deleted by it. The list is cleared with
	/// clearCompilationState()
	typedef vector<CompositorInstance::RenderSystemOperation*> RenderSystemOperations;
	RenderSystemOperations mRenderSystemOperations;

	/** Clear compiled state */
	void clearCompiledState();

	/** Prepare a viewport, the camera and the scene for a rendering operation
	*/
	void preTargetOperation(CompositorInstance::TargetOperation &op, Viewport *vp, Camera *cam);

	/** Restore a viewport, the camera and the scene after a rendering operation
	*/
	void postTargetOperation(CompositorInstance::TargetOperation &op, Viewport *vp, Camera *cam);

	void createOriginalScene();
	void destroyOriginalScene();

	/// destroy internal resources
	void destroyResources(void);

	/** Render queue listener used to set up rendering events. */
	class RQListener: public RenderQueueListener
	{
	public:
		RQListener() : mOperation(0), mSceneManager(0), mRenderSystem(0), mViewport(0) {}

		/** @copydoc RenderQueueListener::renderQueueStarted
		*/
		virtual void renderQueueStarted(uint8 queueGroupId, bool& skipThisInvocation);
		/** @copydoc RenderQueueListener::renderQueueEnded
		*/
		virtual void renderQueueEnded(uint8 queueGroupId);

		/** Set current operation and target. */
		void setOperation(CompositorInstance::TargetOperation *op,SceneManager *sm,RenderFunction *rs);

		/** Notify current destination viewport. */
		void notifyViewport(Viewport* vp) { mViewport = vp; }

		/** Flush remaining render system operations. */
		void flushUpTo(uint8 id);
	private:
		CompositorInstance::TargetOperation *mOperation;
		SceneManager *mSceneManager;
		RenderFunction *mRenderSystem;
		Viewport* mViewport;
		CompositorInstance::RenderSystemOpPairs::iterator currentOp, lastOp;
	};
	RQListener mOurListener;

	/// Old viewport settings
	unsigned int mOldClearEveryFrameBuffers;
	/// Store old scene visibility mask
	uint32 mOldVisibilityMask;
	/// Store old find visible objects
	//bool mOldFindVisibleObjects;
	/// Store old camera LOD bias
	float mOldLodBias;
	/// Store old viewport material scheme
	String mOldMaterialScheme;
	/// Store old shadows enabled flag
	bool mOldShadowsEnabled;


};
#endif
