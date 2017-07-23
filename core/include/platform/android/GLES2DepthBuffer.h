#ifndef __GLES2DepthBuffer_H__
#define __GLES2DepthBuffer_H__

#include "platform/RenderFunctionPrerequisites.h"
#include "base/DepthBuffer.h"

class GLES2Context;
class GLES2RenderBuffer;
class GLES2RenderFunction;
/**
	@copydoc DepthBuffer

	OpenGL supports 2 different methods: FBO & Copy.
	Each one has it's own limitations. Non-FBO methods are solved using "dummy" DepthBuffers.
	That is, a DepthBuffer pointer is attached to the RenderTarget (for the sake of consistency)
	but it doesn't actually contain a Depth surface/renderbuffer (mDepthBuffer & mStencilBuffer are
	null pointers all the time) Those dummy DepthBuffers are identified thanks to their GL context.
	Note that FBOs don't allow sharing with the main window's depth buffer. Therefore even
	when FBO is enabled, a dummy DepthBuffer is still used to manage the windows.
*/
class GLES2DepthBuffer : public DepthBuffer
{
public:
	GLES2DepthBuffer( uint16 poolId, GLES2RenderFunction*renderSystem, GLES2Context *creatorContext,
					GLES2RenderBuffer *depth, GLES2RenderBuffer *stencil,
					uint32 width, uint32 height, uint32 fsaa, uint32 multiSampleQuality,
					bool isManual );
	~GLES2DepthBuffer();

	/// @copydoc DepthBuffer::isCompatible
	virtual bool isCompatible( RenderTarget *renderTarget ) const;

	GLES2Context* getGLContext() const { return mCreatorContext; }
	GLES2RenderBuffer* getDepthBuffer() const  { return mDepthBuffer; }
	GLES2RenderBuffer* getStencilBuffer() const { return mStencilBuffer; }

protected:
	uint32						mMultiSampleQuality;
	GLES2Context				*mCreatorContext;
	GLES2RenderBuffer			*mDepthBuffer;
	GLES2RenderBuffer			*mStencilBuffer;
	GLES2RenderFunction			*mRenderSystem;
};

#endif
