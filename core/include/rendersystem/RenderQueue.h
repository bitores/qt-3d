#ifndef __RenderQueue_h__
#define __RenderQueue_h__

#include "utils/include/platform.h"
#include "utils/include/prerequisites.h"

enum RenderQueueGroupID {
	/// Use this queue for objects which must be rendered first e.g. backgrounds
	RENDER_QUEUE_BACKGROUND,
	/// First queue(after backgrounds), used for sky boxes if renderer first
	RENDER_QUEUE_SKIES_EARLY,
//		RENDER_QUEUE_1,
//		RENDER_QUEUE_2,
	RENDER_QUEUE_OPAQUE,
	RENDER_QUEUE_TRANSPARENT,
	RENDER_QUEUE_SKIES_LATE,
	RENDER_QUEUE_OVERLAY,
	RENDER_QUEUE_OVERLAY_2,
	RENDER_QUEUE_COUNT
};


class Visitor {
public:
	virtual void acceptVisitor(GameObject* gameObject) = 0;
};

class RenderQueue
{
protected:

	typedef vector<RenderQueueListener*> RenderQueueListenerList;
	RenderQueueListenerList mRenderQueueListeners;

	typedef std::list<GameObject*> RenderableList;
	RenderableList mBackgroundRenderQueue;
	RenderableList mSkiesEarlyQueue;
	RenderableList mOpaqueRenderQueue;
	RenderableList mTransparentRenderQueue;
	RenderableList mSkiesLateRenderQueue;
	RenderableList mOverlayRenderQueue;
	RenderableList mOverlayRenderQueue2;


public:
	RenderQueue();
	~RenderQueue();

	void addRenderable(Camera* camera, GameObject* render);
	void addToQueue(GameObject* render, RenderQueueGroupID id);
	void render(Visitor* visitor);
	void renderOverlay(Visitor* visitor);
	void render(RenderableList queue, Visitor* visitor);
	void clear();

	/** Registers a new RenderQueueListener which will be notified when render queues
		are processed.
	*/
	virtual void addRenderQueueListener(RenderQueueListener* newListener) {mRenderQueueListeners.push_back(newListener);}

	/** Removes a listener previously added with addRenderQueueListener. */
	virtual void removeRenderQueueListener(RenderQueueListener* delListener);

	/// Internal method for firing the queue start event, returns true if queue is to be skipped
	void fireRenderQueueStarted(uint8 queueId, bool& skipThisQueue);
	/// Internal method for firing the queue end event, returns true if queue is to be repeated
	void fireRenderQueueEnded(uint8 queueId);
};

class RenderQueueListener
{
public:
	virtual ~RenderQueueListener() {}

	/** Event raised before all render queues are processed.
	*/
	virtual void preRenderQueues() {}
	/** Event raised after all render queues are processed.
	*/
	virtual void postRenderQueues() {}

	/** Event raised before a queue group is rendered.
	@remarks
		This method is called by the SceneManager before each queue group is
		rendered.
	@param queueGroupId The id of the queue group which is about to be rendered
	@param invocation Name of the invocation which is causing this to be
		called (@see RenderQueueInvocation)
	@param skipThisInvocation A boolean passed by reference which is by default set to
		false. If the event sets this to true, the queue will be skipped and not
		rendered. Note that in this case the renderQueueEnded event will not be raised
		for this queue group.
	*/
	virtual void renderQueueStarted(uint8 queueGroupId, bool& skipThisInvocation) {}

	/** Event raised after a queue group is rendered.
	@remarks
		This method is called by the SceneManager after each queue group is
		rendered.
	@param queueGroupId The id of the queue group which has just been rendered
	@param invocation Name of the invocation which is causing this to be
		called (@see RenderQueueInvocation)
	@param repeatThisInvocation A boolean passed by reference which is by default set to
		false. If the event sets this to true, the queue which has just been
		rendered will be repeated, and the renderQueueStarted and renderQueueEnded
		events will also be fired for it again.
	*/
	virtual void renderQueueEnded(uint8 queueGroupId) {}
};

#endif
