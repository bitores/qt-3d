#ifndef __GLES2FBORTT_H__
#define __GLES2FBORTT_H__

#include "GLES2RenderTexture.h"
//#include "GLESContext.h"
#include "GLES2FrameBufferObject.h"

class GLES2FBOManager;
class GLES2RenderBuffer;

/** RenderTexture for GL ES 2 FBO
*/
class GLES2FBORenderTexture: public GLES2RenderTexture /*MANAGED_RESOURCE*/
{
public:
	GLES2FBORenderTexture(Root* root, GLES2FBOManager *manager, const String &name, const GLES2SurfaceDesc &target, bool writeGamma, uint fsaa);

	virtual void getCustomAttribute(const String& name, void* pData);

	/// Override needed to deal with multisample buffers
	virtual void swapBuffers();

	/// Override so we can attach the depth buffer to the FBO
	virtual bool attachDepthBuffer( DepthBuffer *depthBuffer );
	virtual void detachDepthBuffer();
	virtual void _detachDepthBuffer();
protected:
	GLES2FrameBufferObject mFB;

#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
	/** See AndroidResource. */
	virtual void notifyOnContextLost();

	/** See AndroidResource. */
	virtual void notifyOnContextReset();
#endif
};

/** Factory for GL ES 2 Frame Buffer Objects, and related things.
*/
class GLES2FBOManager: public GLES2RTTManager
{
public:
	GLES2FBOManager(Root* root);
	~GLES2FBOManager();

	/** Bind a certain render target if it is a FBO. If it is not a FBO, bind the
		main frame buffer.
	*/
	void bind(RenderTarget *target);

	/** Unbind a certain render target. No-op for FBOs.
	*/
	void unbind(RenderTarget *target) {};

	/** Get best depth and stencil supported for given internalFormat
	*/
	void getBestDepthStencil(GLenum internalFormat, GLenum *depthFormat, GLenum *stencilFormat);

	/** Create a texture rendertarget object
	*/
	virtual GLES2FBORenderTexture *createRenderTexture(const String &name,
		const GLES2SurfaceDesc &target, bool writeGamma, uint fsaa);

	/** Create a multi render target
	*/
	virtual MultiRenderTarget* createMultiRenderTarget(const String & name);

	/** Request a render buffer. If format is GL_NONE, return a zero buffer.
	*/
	GLES2SurfaceDesc requestRenderBuffer(GLenum format, size_t width, size_t height, uint fsaa);
	/** Request the specify render buffer in case shared somewhere. Ignore
		silently if surface.buffer is 0.
	*/
	void requestRenderBuffer(const GLES2SurfaceDesc &surface);
	/** Release a render buffer. Ignore silently if surface.buffer is 0.
	*/
	void releaseRenderBuffer(const GLES2SurfaceDesc &surface);

	/** Check if a certain format is usable as FBO rendertarget format
	*/
	bool checkFormat(PixelFormat format) { return mProps[format].valid; }

	/** Get a FBO without depth/stencil for temporary use, like blitting between textures.
	*/
	GLuint getTemporaryFBO() { return mTempFBO; }

	/** Detects all supported fbo's and recreates the tempory fbo */
	void _reload();

private:
	/** Frame Buffer Object properties for a certain texture format.
	*/
	struct FormatProperties
	{
		bool valid; // This format can be used as RTT (FBO)

		/** Allowed modes/properties for this pixel format
		*/
		struct Mode
		{
			size_t depth;     // Depth format (0=no depth)
			size_t stencil;   // Stencil format (0=no stencil)
		};

		vector<Mode> modes;
	};
	/** Properties for all internal formats defined by OGRE
	*/
	FormatProperties mProps[PF_COUNT];

	/** Stencil and depth renderbuffers of the same format are re-used between surfaces of the
		same size and format. This can save a lot of memory when a large amount of rendertargets
		are used.
	*/
	struct RBFormat
	{
		RBFormat(GLenum inFormat, size_t inWidth, size_t inHeight, uint fsaa):
			format(inFormat), width(inWidth), height(inHeight), samples(fsaa)
		{}
		GLenum format;
		size_t width;
		size_t height;
		uint samples;
		// Overloaded comparison operator for usage in map
		bool operator < (const RBFormat &other) const
		{
			if(format < other.format)
			{
				return true;
			}
			else if(format == other.format)
			{
				if(width < other.width)
				{
					return true;
				}
				else if(width == other.width)
				{
					if(height < other.height)
						return true;
					else if (height == other.height)
					{
						if (samples < other.samples)
							return true;
					}
				}
			}
			return false;
		}
	};
	struct RBRef
	{
		RBRef(){}
		RBRef(GLES2RenderBuffer *inBuffer):
			buffer(inBuffer), refcount(1)
		{ }
		GLES2RenderBuffer *buffer;
		size_t refcount;
	};
	typedef map<RBFormat, RBRef> RenderBufferMap;
	RenderBufferMap mRenderBufferMap;
	// map(format, sizex, sizey) -> [GLSurface*,refcount]

	/** Temporary FBO identifier
	 */
	GLuint mTempFBO;

	/** Detect allowed FBO formats */
	void detectFBOFormats();
	GLuint _tryFormat(GLenum depthFormat, GLenum stencilFormat);
	bool _tryPackedFormat(GLenum packedFormat);
	void _createTempFramebuffer(PixelFormat pixFmt, GLuint internalFormat, GLuint fmt, GLenum dataType, GLuint &fb, GLuint &tid);
};
#endif
