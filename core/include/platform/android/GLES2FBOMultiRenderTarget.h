#ifndef __GLES2MULTIRENDERTARGET_H__
#define __GLES2MULTIRENDERTARGET_H__

#include "GLES2FrameBufferObject.h"

class GLES2FBOManager;

/** MultiRenderTarget for GL ES 2.x.
*/
class GLES2FBOMultiRenderTarget : public MultiRenderTarget
{
public:
	GLES2FBOMultiRenderTarget(Root* root, GLES2FBOManager *manager, const String &name);
	~GLES2FBOMultiRenderTarget();

	virtual void getCustomAttribute( const String& name, void *pData );

	bool requiresTextureFlipping() const { return true; }

	/// Override so we can attach the depth buffer to the FBO
	virtual bool attachDepthBuffer( DepthBuffer *depthBuffer );
	virtual void detachDepthBuffer();
	virtual void _detachDepthBuffer();
private:
	virtual void bindSurfaceImpl(size_t attachment, RenderTexture *target);
	virtual void unbindSurfaceImpl(size_t attachment);
	GLES2FrameBufferObject fbo;
};

#endif // __GLES2MULTIRENDERTARGET_H__
