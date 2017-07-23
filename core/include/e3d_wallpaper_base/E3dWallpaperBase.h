#ifndef __E3dWallpaperBase_h__
#define __E3dWallpaperBase_h__
#include <jni.h>

#include "base/Root.h"
#include "ui/eRect.h"
#include "scenegraph/SceneManager.h"
#include "scenegraph/GameObject.h"
#include "scenegraph/eGallery.h"

#include "asset/Image.h"


#include "rendersystem/TextureManager.h"
#include "rendersystem/MeshFilter.h"
#include "rendersystem/Material.h"
#include "rendersystem/Renderer.h"

//#include "rendersystem/Shader.h"
//#include "animation/Animation.h"

#include "utils/include/Transform.h"
#include "utils/include/IDGenerator.h"
#include "utils/include/eBaseAdapter.h"

//#include "external/particle/ParticleScriptData.h"
//#include "Particle.h"
//
//class eScoreWidget;
//class eSwitchBackground;
class xml_parser_manager;

class E3dWallpaperBase : public Object{
public:
	/// TODO liuzx
	bool isWallpaper;
	eGallery* mGallery;
	int mLastTouchEventAction;
	float  mTouchDownTime;
	float  mTouchDownX, mTouchDownY;

//	String arcType;
//	String arcName;
//	String scenefile;

	Root *mRoot;
	float width;
	float height;
//	bool mEnableSound;
	bool mEnableRunning;
//	eRect *gBackGround;
//	xml_parser_manager* mXml_parser_manager;
//	typedef list<Animation*> AnimationList;
//	AnimationList mAnimationList;
public:
	E3dWallpaperBase();
	~E3dWallpaperBase();

	void initJellyFish(bool isWallpaper);

private:
//	void createSwitchBackground();
//	void createParticleSystem();

protected:
//	GameObject* createSceneGameobject(GameObject* parentGo, const String& goName, IMesh* mesh, int matTexId);
//	virtual void prepareSceneData() = 0;

	void disableLuaScript();
public:
//	virtual FeedbackListener* getFeedbackListener() = 0;
//
//	virtual void initSceneGlue(JNIEnv* env, jobject renderer);

	virtual void prevCreateScene() = 0;
	void createScene(const char* arcType, const char* arcName, const char* scenefile);
	virtual void postCreateScene() = 0;

//	virtual void onTouchEvent(int action, float x, float y);
	virtual void onOffsetsChanged(float xOffset, float yOffset, float xStep, float yStep, int xPixels, int yPixels);

	void onStop(bool beStop);
	virtual void onSize(Real w, Real h);

public:
//	virtual void setEnableSound(bool enable, bool putToFile);
//	void setEnableRunning(bool enable);
//	void openSettingActivity();
//
//	int setBackgroundImage(int idx);
////	void updateBackgroundImage(AAssetManager* mgr, String & bgImage);
//	void updateScore();
//	void updateCustomBgImage(String& customBgImage);
//	void updateCustomBgImage(int customBgItem, String& customBgImage);

	void pauseAnimation();
	void resumeAnimation();
//	JNIEnv* env;
//	jweak mRenderderObj;
//	jmethodID mClickCallbackID;
//	jmethodID mEventClickCallbackID;
//	jmethodID mPutIntID;
//	jmethodID mGetIntID;
//	jmethodID mPutBoolID;
//	jmethodID mGetBoolID;
//	jmethodID mPutStringID;
//	jmethodID mGetStringID;
////	jmethodID mGetScoreID;
//
//	// call java function
////	jobject getRealObject(JNIEnv* env, jobject obj);
//	bool clickCallback(int tid, int pid = 0);
//	int clickCallback(int event_id, int arg1, int arg2);
//
//	void putIntCallback(String name, int score);
//	int getIntCallback(String name, int defValue = 0);
//
//	void putBoolCallback(String name, bool value);
//	bool getBoolCallback(String name, bool defValue = true);
//
//	void putStringCallback(String name, String val);
//	String getStringCallback(String name);
//	void setParticleNumber(int number);
};
#endif
