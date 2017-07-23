#ifndef __GLTEXTURE_H__
#define __GLTEXTURE_H__

#include "platform/RenderFunctionPrerequisites.h"
#include "utils/include/platform.h"
#include "rendersystem/RenderTexture.h"
#include "rendersystem/Texture.h"
#include "GLES2Support.h"
#include "hardwarebuffer/HardwarePixelBuffer.h"

class GLES2Texture : public Texture
{
public:
	// Constructor
	GLES2Texture(ResourceManager* creator, const String& name, ResourceHandle handle,
		const String& group, bool isManual, ManualResourceLoader* loader, GLES2Support& support/*, Root* root*/);

	virtual ~GLES2Texture();

	void createRenderTexture();

	/// @copydoc Texture::getBuffer
	HardwarePixelBufferSharedPtr getBuffer(size_t face, size_t mipmap);

	// Takes the OGRE texture type (1d/2d/3d/cube) and returns the appropriate GL one
	GLenum getGLES2TextureTarget(void) const;

	GLuint getGLID() const
	{
		return mTextureID;
	}

//	void getCustomAttribute(const String& name, void* pData);

	void texSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels);
protected:
	/// @copydoc Texture::createInternalResourcesImpl
	void createInternalResourcesImpl(void);
	/// @copydoc Resource::prepareImpl
	void prepareImpl(void);
	/// @copydoc Resource::unprepareImpl
	void unprepareImpl(void);
	/// @copydoc Resource::loadImpl
	void loadImpl(void);
	/// @copydoc Resource::freeInternalResourcesImpl
	void freeInternalResourcesImpl(void);

	/** internal method, create GLHardwarePixelBuffers for every face and
		 mipmap level. This method must be called after the GL texture object was created,
		the number of mipmaps was set (GL_TEXTURE_MAX_LEVEL) and glTexImageXD was called to
		actually allocate the buffer
	*/
	void _createSurfaceList();

	/// Used to hold images between calls to prepare and load.
	typedef SharedPtr< std::vector<Image> > LoadedImages;

	/** Vector of images that were pulled from disk by
		prepareLoad but have yet to be pushed into texture memory
		by loadImpl.  Images should be deleted by loadImpl and unprepareImpl.
	*/
	LoadedImages mLoadedImages;

    /// Create gl texture
    void _createGLTexResource();

private:
	GLuint mTextureID;
	GLES2Support& mGLSupport;

	/// Vector of pointers to subsurfaces
	typedef vector<HardwarePixelBufferSharedPtr> SurfaceList;
	SurfaceList	mSurfaceList;
};

#endif // __GLTEXTURE_H__
