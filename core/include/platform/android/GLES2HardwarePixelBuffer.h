#ifndef __GLES2HardwarePixelBuffer_H__
#define __GLES2HardwarePixelBuffer_H__

#include "platform/RenderFunctionPrerequisites.h"
#include "hardwarebuffer/HardwarePixelBuffer.h"

class GLES2HardwarePixelBuffer: public HardwarePixelBuffer
{
	protected:
		/// Lock a box
		PixelBox lockImpl(const Box lockBox,  LockOptions options);

		/// Unlock a box
		void unlockImpl(void);

		// Internal buffer; either on-card or in system memory, freed/allocated on demand
		// depending on buffer usage
		PixelBox mBuffer;
		GLenum mGLInternalFormat; // GL internal format
		LockOptions mCurrentLockOptions;

		// Buffer allocation/freeage
		void allocateBuffer();

		void freeBuffer();

		// Upload a box of pixels to this buffer on the card
		virtual void upload(const PixelBox &data, const Box &dest);

		// Download a box of pixels from the card
		virtual void download(const PixelBox &data);

	public:
		/// Should be called by HardwareBufferManager
		GLES2HardwarePixelBuffer(uint32 mWidth, uint32 mHeight, uint32 mDepth,
							  PixelFormat mFormat,
							  HardwareBuffer::Usage usage);

		/// @copydoc HardwarePixelBuffer::blitFromMemory
		void blitFromMemory(const PixelBox &src, const Box &dstBox);

		/// @copydoc HardwarePixelBuffer::blitToMemory
		void blitToMemory(const Box &srcBox, const PixelBox &dst);

		virtual ~GLES2HardwarePixelBuffer();

		/** Bind surface to frame buffer. Needs FBO extension.
		*/
		virtual void bindToFramebuffer(GLenum attachment, size_t zoffset);
		GLenum getGLFormat() { return mGLInternalFormat; }
};

/** Texture surface.
*/
class GLES2TextureBuffer: public GLES2HardwarePixelBuffer
{
public:
    /** Texture constructor */
    GLES2TextureBuffer(const String &baseName, GLenum target, GLuint id, GLint width, GLint height, GLint depth, GLint internalFormat,
                       GLint format, GLint face, GLint level, Usage usage, bool softwareMipmap, bool writeGamma, uint fsaa, Root* root);
    virtual ~GLES2TextureBuffer();

    /// @copydoc HardwarePixelBuffer::bindToFramebuffer
    virtual void bindToFramebuffer(GLenum attachment, size_t zoffset);

    /// @copydoc HardwarePixelBuffer::getRenderTarget
    RenderTexture* getRenderTarget(size_t slice);

    /// Upload a box of pixels to this buffer on the card
    virtual void upload(const PixelBox &data, const Box &dest);

    /// Download a box of pixels from the card
    virtual void download(const PixelBox &data);

    /// Hardware implementation of blitFromMemory
    virtual void blitFromMemory(const PixelBox &src_orig, const Box &dstBox);

    /// Notify TextureBuffer of destruction of render target
    void _clearSliceRTT(size_t zoffset)
    {
        mSliceTRT[zoffset] = 0;
    }

    // Copy from framebuffer
    void copyFromFramebuffer(size_t zoffset);

    /// @copydoc HardwarePixelBuffer::blit
    void blit(const HardwarePixelBufferSharedPtr &src, const Box &srcBox, const Box &dstBox);
    // Blitting implementation
    void blitFromTexture(GLES2TextureBuffer *src, const Box &srcBox, const Box &dstBox);

#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
// Friends.
protected:
    friend class GLES2Texture;

    void updateTextureId(GLuint textureID);
#endif

protected:
    // In case this is a texture level
    GLenum mTarget;
    GLenum mFaceTarget; // same as mTarget in case of GL_TEXTURE_xD, but cubemap face for cubemaps
    GLuint mTextureID;
    GLuint mBufferId;
    GLint mFace;
    GLint mLevel;
    bool mSoftwareMipmap;
    Root* mRoot;

    typedef vector<RenderTexture*> SliceTRT;
    SliceTRT mSliceTRT;

    void buildMipmaps(const PixelBox &data);
};

 /** Renderbuffer surface.  Needs FBO extension.
 */
class GLES2RenderBuffer: public GLES2HardwarePixelBuffer
{
public:
    GLES2RenderBuffer(GLenum format, size_t width, size_t height, GLsizei numSamples);
    virtual ~GLES2RenderBuffer();

    /// @copydoc GLES2HardwarePixelBuffer::bindToFramebuffer
    virtual void bindToFramebuffer(GLenum attachment, size_t zoffset);

protected:
    // In case this is a render buffer
    GLuint mRenderbufferID;
    GLsizei mNumSamples;
};

#endif
