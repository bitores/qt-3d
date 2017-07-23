#ifndef __RenderToVertexBuffer_H__
#define __RenderToVertexBuffer_H__

#include "utils/include/prerequisites.h"
#include "rendersystem/Material.h"
#include "rendersystem/RenderOperation.h"

/** \addtogroup Core
*  @{
*/
/** \addtogroup RenderSystem
*  @{
*/
/**
	An object which renders geometry to a vertex.
@remarks
	This is especially useful together with geometry shaders, as you can
	render procedural geometry which will get saved to a vertex buffer for
	reuse later, without regenerating it again. You can also create shaders
	that run on previous results of those shaders, creating stateful
	shaders.
*/
class RenderToVertexBuffer
{
public:
	/** C'tor */
	RenderToVertexBuffer();
	/** D'tor */
	virtual ~RenderToVertexBuffer();

	/**
		Get the vertex declaration that the pass will output.
	@remarks
		Use this object to set the elements of the buffer. Object will calculate
		buffers on its own. Only one source allowed!
	*/
	VertexDeclaration* getVertexDeclaration();

	/**
		Get the maximum number of vertices that the buffer will hold
	*/
	unsigned int getMaxVertexCount() const { return mMaxVertexCount; }

	/**
		Set the maximum number of vertices that the buffer will hold
	*/
	void setMaxVertexCount(unsigned int maxVertexCount) { mMaxVertexCount = maxVertexCount; }

	/**
		What type of primitives does this object generate?
	*/
	RenderOperation::OperationType getOperationType() const { return mOperationType; }

	/**
		Set the type of primitives that this object generates
	*/
	void setOperationType(RenderOperation::OperationType operationType) { mOperationType = operationType; }

	/**
		Set whether this object resets its buffers each time it updates.
	*/
	void setResetsEveryUpdate(bool resetsEveryUpdate) { mResetsEveryUpdate = resetsEveryUpdate; }

	/**
		Does this object reset its buffer each time it updates?
	*/
	bool getResetsEveryUpdate() const { return mResetsEveryUpdate; }

	/**
		Get the render operation for this buffer
	*/
	virtual void getRenderOperation(RenderOperation& op) = 0;

	/**
		Update the contents of this vertex buffer by rendering
	*/
	virtual void update(SceneManager* sceneMgr) = 0;

	/**
		Reset the vertex buffer to the initial state. In the next update,
		the source renderable will be used as input.
	*/
	virtual void reset() { mResetRequested = true; }

//	/**
//		Set the source renderable of this object. During the first (and
//		perhaps later) update of this object, this object's data will be
//		used as input)
//	*/
//	void setSourceRenderable(Renderable* source) { mSourceRenderable = source; }
//
//	/**
//		Get the source renderable of this object
//	*/
//	const Renderable* getSourceRenderable() const { return mSourceRenderable; }

	/**
		Get the material which is used to render the geometry into the
		vertex buffer.
	*/
	const MaterialPtr& getRenderToBufferMaterial() { return mMaterial; }

	/**
		Set the material name which is used to render the geometry into
		the vertex buffer
	*/
	void setRenderToBufferMaterialName(const String& materialName);
protected:
	RenderOperation::OperationType mOperationType;
	bool mResetsEveryUpdate;
	bool mResetRequested;
	MaterialPtr mMaterial;
//	Renderable* mSourceRenderable;
	VertexData* mVertexData;
	unsigned int mMaxVertexCount;
};

typedef SharedPtr<RenderToVertexBuffer> RenderToVertexBufferSharedPtr;
/** @} */
/** @} */

#endif
