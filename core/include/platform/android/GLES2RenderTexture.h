#ifndef __GLES2RenderTexture_H__
#define __GLES2RenderTexture_H__

#include "GLES2Texture.h"

class GLES2HardwarePixelBuffer;

/** GL surface descriptor. Points to a 2D surface that can be rendered to.
*/
struct GLES2SurfaceDesc
{
	public:
		GLES2HardwarePixelBuffer *buffer;
		uint32 zoffset;
		uint numSamples;

		GLES2SurfaceDesc() :buffer(0), zoffset(0), numSamples(0) {}
};

/** Base class for GL Render Textures
*/
class GLES2RenderTexture : public RenderTexture
{
	public:
		GLES2RenderTexture(Root* root, const String &name, const GLES2SurfaceDesc &target, bool writeGamma, uint fsaa);
		virtual ~GLES2RenderTexture();
		bool requiresTextureFlipping() const { return true; }
};

/** Manager/factory for RenderTextures.
*/
class GLES2RTTManager/* : public Singleton<GLES2RTTManager>*/
{
	public:
		Root* mRoot;
		GLES2RTTManager(Root* root);

		virtual ~GLES2RTTManager();

		/** Create a texture rendertarget object
		*/
		virtual RenderTexture *createRenderTexture(const String &name, const GLES2SurfaceDesc &target, bool writeGamma, uint fsaa) = 0;

		 /** Check if a certain format is usable as rendertexture format
		*/
		virtual bool checkFormat(PixelFormat format) = 0;

		/** Bind a certain render target.
		*/
		virtual void bind(RenderTarget *target) = 0;

		/** Unbind a certain render target. This is called before binding another RenderTarget, and
			before the context is switched. It can be used to do a copy, or just be a noop if direct
			binding is used.
		*/
		virtual void unbind(RenderTarget *target) = 0;

		virtual void getBestDepthStencil(GLenum internalFormat, GLenum *depthFormat, GLenum *stencilFormat)
		{
			*depthFormat = GL_NONE;
			*stencilFormat = GL_NONE;
		}

		/** Create a multi render target
		*/
		virtual MultiRenderTarget* createMultiRenderTarget(const String & name);

		/** Get the closest supported alternative format. If format is supported, returns format.
		*/
		virtual PixelFormat getSupportedAlternative(PixelFormat format);
};

/** RenderTexture for simple copying from frame buffer
*/
class GLES2CopyingRTTManager;
class GLES2CopyingRenderTexture : public GLES2RenderTexture
{
	public:
		GLES2CopyingRenderTexture(Root* root, GLES2CopyingRTTManager *manager,
							   const String &name,
							   const GLES2SurfaceDesc &target,
							   bool writeGamma, uint fsaa);

		virtual void getCustomAttribute(const String& name, void* pData);
};

/** Simple, copying manager/factory for RenderTextures. This is only used as the last fallback if
	FBOs aren't supported.
*/
class GLES2CopyingRTTManager : public GLES2RTTManager
{
	public:
		GLES2CopyingRTTManager(Root* root);
		virtual ~GLES2CopyingRTTManager();

		/** @copydoc GLES2RTTManager::createRenderTexture
		*/
		virtual RenderTexture *createRenderTexture(const String &name, const GLES2SurfaceDesc &target, bool writeGamma, uint fsaa);

		/** @copydoc GLES2RTTManager::checkFormat
		*/
		virtual bool checkFormat(PixelFormat format);

		/** @copydoc GLES2RTTManager::bind
		*/
		virtual void bind(RenderTarget *target);

		/** @copydoc GLES2RTTManager::unbind
		*/
		virtual void unbind(RenderTarget *target);
};
#endif
