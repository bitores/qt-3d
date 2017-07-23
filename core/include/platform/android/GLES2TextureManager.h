#ifndef __GLES2TextureManager_H__
#define __GLES2TextureManager_H__

#include "GLES2Prerequisites.h"
#include "rendersystem/TextureManager.h"
#include "GLES2Texture.h"
#include "GLES2Support.h"

/** GL ES-specific implementation of a TextureManager */
class GLES2TextureManager : public TextureManager
{
	public:
		GLES2TextureManager(Root* root, GLES2Support& support);
		virtual ~GLES2TextureManager();

		GLuint getWarningTextureID() { return mWarningTextureID; }

		/// @copydoc TextureManager::getNativeFormat
		PixelFormat getNativeFormat(TextureType ttype, PixelFormat format, int usage);

		/// @copydoc TextureManager::isHardwareFilteringSupported
		bool isHardwareFilteringSupported(TextureType ttype, PixelFormat format, int usage,
										  bool preciseFormatOnly = false);
protected:
	friend class GLES2RenderFunction;

	/// @copydoc ResourceManager::createImpl
	Resource* createImpl(const String& name, ResourceHandle handle,
						 const String& group, bool isManual, ManualResourceLoader* loader,
						 const NameValuePairList* createParams);


	/// Internal method to create a warning texture (bound when a texture unit is blank)
	void createWarningTexture();

	GLES2Support& mGLSupport;
	GLuint mWarningTextureID;
};

#endif
