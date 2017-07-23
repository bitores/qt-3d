#ifndef __GLES2RenderToVertexBuffer_H__
#define __GLES2RenderToVertexBuffer_H__

#include "hardwarebuffer/RenderToVertexBuffer.h"
#include "GLES2Prerequisites.h"

#if OGRE_NO_GLES3_SUPPORT == 0

/**
	An object which renders geometry to a vertex.
@remarks
	This is especially useful together with geometry shaders, as you can
	render procedural geometry which will get saved to a vertex buffer for
	reuse later, without regenerating it again. You can also create shaders
	that run on previous results of those shaders, creating stateful
	shaders.
*/
class GLES2RenderToVertexBuffer : public RenderToVertexBuffer
{
public:
	/** C'tor */
	GLES2RenderToVertexBuffer();
	/** D'tor */
	virtual ~GLES2RenderToVertexBuffer();

	/**
		Get the render operation for this buffer
	*/
	virtual void getRenderOperation(RenderOperation& op);

	/**
		Update the contents of this vertex buffer by rendering
	*/
	virtual void update(SceneManager* sceneMgr);
protected:
	void reallocateBuffer(size_t index);
	void bindVerticesOutput(Pass* pass);
	String getSemanticVaryingName(VertexElementSemantic semantic, unsigned short index);
	HardwareVertexBufferSharedPtr mVertexBuffers[2];
	size_t mFrontBufferIndex;
	GLuint mPrimitivesDrawnQuery;
	bool mFeedbackActive;
};

#endif
#endif
