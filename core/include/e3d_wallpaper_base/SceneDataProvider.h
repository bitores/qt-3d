#ifndef _SceneDataProvider_h__
#define _SceneDataProvider_h__

#include "utils/include/prerequisites.h"


enum TEXTURE_LOAD_METHOD
{
	TLM_FROM_ASSET,       // pure data from .dat
	TLM_FROM_RES_BITMAP,  // bitmap from resource
	TLM_FROM_SDCARD,
	TLM_FROM_MIX
};

enum TEXTURE_USE_TYPE
{
	TUT_BACKGROUND,      // background texture
	TUT_PARTICLESYSTEM   // particle system texture
};

enum TEXTURE_LOCATION
{
	TLT_SDCARD,
	TLT_ASSET
};

enum TEXTURE_FILE_TYPE
{
	TFT_RAW_DATA,
	TFT_COMPRESS_DATA
};

typedef struct _Texture_Source_Info
{
	unsigned char id;
	String srcImageFile;
//	TEXTURE_USE_TYPE useType;

	void setId(unsigned char id) {
		this->id = id;
	}

	unsigned char getId() {
		return id;
	}

	void setImageFile(String & file) {
		srcImageFile = file;
	}

	String & getImageFile() {
		return srcImageFile;
	}
}TTextureSourceInfo;

typedef std::vector<TTextureSourceInfo> TTextureSourceInfoArray;
typedef std::vector<unsigned char> TBackgroundTextureSrcIndices;

class SceneDataProvider
{
public:
	String gParticleSystemScript;
	TEXTURE_LOAD_METHOD gTextureLoadMethod;
	TTextureSourceInfoArray gTextureSourceInfoArray;// all texture image used
	TBackgroundTextureSrcIndices gBgTextureSrcIndices;// represent indices from gTextureSourceInfoArray
	int gCustomBgPosition;// represent index value from gBgTextureSrcIndices

	long gAnimationShortDurationMillis;
	long gAnimationLongDurationMillis;

	SceneDataProvider();
	~SceneDataProvider();

	bool hasCustomBackground();
	int getCustomBgPosition();
	int getCustomBgTextureSrcIndex();
	int getCustomBgTextureSourceId();
	int getCustomBgTextureSourceFile(String& customBgImage);
	void insertTextureSource(String & file, bool putAsBackground, bool isCustomBackground);

	String& getImageFile(int id);
	void setImageFile(int id, String & file);
	virtual void prepareSceneData() = 0;
};

#endif
