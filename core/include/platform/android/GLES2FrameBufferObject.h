#ifndef __GLES2FBO_H__
#define __GLES2FBO_H__

#include "GLES2RenderTexture.h"
//#include "GLESContext.h"

class GLES2FBOManager;
struct GLES2SurfaceDesc;

/** Frame Buffer Object abstraction.
*/
class GLES2FrameBufferObject
{
public:
	GLES2FrameBufferObject(GLES2FBOManager *manager, uint fsaa);
	~GLES2FrameBufferObject();

	/** Bind a surface to a certain attachment point.
		attachment: 0..OGRE_MAX_MULTIPLE_RENDER_TARGETS-1
	*/
	void bindSurface(size_t attachment, const GLES2SurfaceDesc &target);
	/** Unbind attachment
	*/
	void unbindSurface(size_t attachment);

	/** Bind FrameBufferObject
	*/
	void bind();

	/** Swap buffers - only useful when using multisample buffers.
	*/
	void swapBuffers();

	/** This function acts very similar to @see GLES2FBORenderTexture::attachDepthBuffer
		The difference between D3D & OGL is that D3D setups the DepthBuffer before rendering,
		while OGL setups the DepthBuffer per FBO. So the DepthBuffer (RenderBuffer) needs to
		be attached for OGL.
	*/
	void attachDepthBuffer( DepthBuffer *depthBuffer );
	void detachDepthBuffer();

	/// Accessors
	uint32 getWidth();
	uint32 getHeight();
	PixelFormat getFormat();
	GLsizei getFSAA();

	GLES2FBOManager *getManager() { return mManager; }
	const GLES2SurfaceDesc &getSurface(size_t attachment) { return mColour[attachment]; }

#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
	/** See AndroidResource. */
	void notifyOnContextLost();

	/** See AndroidResource. */
	void notifyOnContextReset(const GLES2SurfaceDesc &target);
#endif

private:
	GLES2FBOManager *mManager;
	GLsizei mNumSamples;
	GLuint mFB;
	GLuint mMultisampleFB;
	GLES2SurfaceDesc mMultisampleColourBuffer;
	GLES2SurfaceDesc mDepth;
	GLES2SurfaceDesc mStencil;
	// Arbitrary number of texture surfaces
	GLES2SurfaceDesc mColour[E3D_MAX_MULTIPLE_RENDER_TARGETS];


	/** Initialise object (find suitable depth and stencil format).
		Must be called every time the bindings change.
		It fails with an exception (ERR_INVALIDPARAMS) if:
		- Attachment point 0 has no binding
		- Not all bound surfaces have the same size
		- Not all bound surfaces have the same internal format
	*/
	void initialise();
};


#endif
