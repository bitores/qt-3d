#ifndef __Root__h
#define __Root__h

#include "utils/include/prerequisites.h"
#include "rendersystem/RenderWindow.h"
#include "utils/include/Singleton.h"
#include "utils/include/ColourValue.h"
#include "hardwarebuffer/HardwareVertexBuffer.h"
#include "platform/android/AndroidLogManager.h"
#include "rendersystem/Material.h"
#include "Runnable.h"
#include "scenegraph/SceneManagerEnumerator.h"
#include "compositor/CompositorManager.h"
#include "input/InputManager.h"
int gleswIsSupported(int major, int minor);
class RenderFunction;
class IAutoLayout;

class Root
{
private:
    SceneManagerEnumerator* mSceneManagerEnum;
    typedef deque<SceneManager*> SceneManagerStack;
    SceneManagerStack mSceneManagerStack;

    SceneManager* mSceneManager;
//    typedef HashMap<String, Camera*> CameraMap;
//    CameraMap mCameraMap;
//	Camera *mCamera;

//	ParticleSystemList mParticleSystemList; // TODO liuzx tmp
	ParticleSystemListener* mParticleSystemListener;

	Viewport *mViewport;

	typedef std::list<RunnablePtr> RunnableList;
	RunnableList mRunnableList;

	typedef std::list<RenderTarget*> RenderTargetList;
	RenderTargetList mRenderTargets;

	typedef std::list<IAutoLayout*> AutoLayoutList;
	AutoLayoutList mAutoLayoutList;

	CodecManager *mCodecManager;
	EncryptManager *mEncryptManager;

//	NameIDMap mMeshIdMap;
//	typedef HashMap<uint32, IMesh*> MeshIDMap;
	typedef HashMap<String, IMesh*> MeshMap;
	MeshMap mMeshMap;
	// 1. ��Ⱦ�����ģ�ϵͳ�п��Դ��ڶ�����Ⱦ�����ģ�MainRenderTarget����PrimaryTarget

	// 2.
	ArchiveManager *mArchiveManager;
//	ArchiveFactory *mFileSystemArchiveFactory;
//	ArchiveFactory *mZipArchiveFactory;
//	ArchiveFactory *mEmbeddedZipArchiveFactory;

	RenderFunction *mRenderFunction; // Ӧ��������Ⱦ�����ģ���Ҫfix
	MaterialManager *mMaterialManager;
	FontManager* mFontManager;
	HighLevelGpuProgramManager* mHighLevelGpuProgramManager;
	GLSLLinkProgramManager *mGLSLLinkProgramManager;
	ParticleSystemManager* mParticleSystemManager;

	ScriptEngineManager* mScriptEngineManager;
	// 3. ��Դ���ع������ȣ�����ϵͳ��ֻ��Ҫһ��ʵ��
	ResourceGroupManager* mResourceGroupManager;
	//LogManager* mLogManager;
	IDGenerator* mIDGenerator;
	NameGenerator* mNameGenerator;
	AnimationManager* mAnimationManager;
	ControllerManager* mControllerManager;
	MeshManager* mMeshManager;
	UIMeshManager* mUIMeshManager;
	CompositorManager* mCompositorManager;

	//add by xlh
	KeyFramesManager* mKeyFramesManager;

	String mPackageName;
	String mVersion;
	String mLocale;
	String mChannel;
public:
    InputManager *mInputManager;
	unsigned int mPhoneWidth;
	unsigned int mPhoneHeight;
	static String SCENE_GRAPH_NAME;

protected:
	Real mFrameSmoothingTime;

	ISurfaceTouchListener* mTouchListener;

	Timer* mTimer;
	unsigned long mNextFrame;
	/** Set of registered frame listeners */
	set<FrameListener*> mFrameListeners;

	/** Set of frame listeners marked for removal*/
	set<FrameListener*> mRemovedFrameListeners;

    /** Indicates the type of event to be considered by calculateEventTime(). */
    enum FrameEventTimeType {
        FETT_ANY = 0,
		FETT_STARTED = 1,
		FETT_QUEUED = 2,
		FETT_ENDED = 3,
		FETT_COUNT = 4
    };

    /// Contains the times of recently fired events
	typedef std::deque<unsigned long> EventTimesQueue;
    EventTimesQueue mEventTimes[FETT_COUNT];

    /** Internal method for calculating the average time between recently fired events.
    @param now The current time in ms.
    @param type The type of event to be considered.
    */
    Real calculateEventTime(unsigned long now, FrameEventTimeType type);

	/** Update a set of event times (note, progressive, only call once for each type per frame) */
	void populateFrameEvent(FrameEventTimeType type, FrameEvent& evtToUpdate);

public:
	/** Clears the history of all event times.
	@remarks
		OGRE stores a history of the last few event times in order to smooth
		out any inaccuracies and temporary fluctuations. However, if you
		pause or don't render for a little while this can cause a lurch, so
		if you're resuming rendering after a break, call this method to reset
		the stored times
	*/
	void clearEventTimes(void);

	/** Sets the period over which OGRE smooths out fluctuations in frame times.
	@remarks
		OGRE by default gives you the raw frame time, but can optionally
		smooths it out over several frames, in order to reduce the
		noticeable effect of occasional hiccups in framerate.
		These smoothed values are passed back as parameters to FrameListener
		calls.
	@par
		This method allow you to tweak the smoothing period, and is expressed
		in seconds. Setting it to 0 will result in completely unsmoothed
		frame times (the default).
	*/
	void setFrameSmoothingPeriod(Real period) { mFrameSmoothingTime = period; }
	/** Gets the period over which OGRE smooths out fluctuations in frame times. */
	Real getFrameSmoothingPeriod(void) const { return mFrameSmoothingTime; }

    /** Gets a pointer to the central timer used for all OGRE timings */
    Timer* getTimer(void);

    KeyFramesManager* getKeyFramesManager();

    /** Method for raising frame started events.
    @remarks
        This method is only for internal use when you use OGRE's inbuilt rendering
        loop (Root::startRendering). However, if you run your own rendering loop then
        you should call this method to ensure that FrameListener objects are notified
        of frame events; processes like texture animation and particle systems rely on
        this.
    @par
        Calling this method also increments the frame number, which is
        important for keeping some elements of the engine up to date.
    @note
        This method takes an event object as a parameter, so you can specify the times
        yourself. If you are happy for OGRE to automatically calculate the frame time
        for you, then call the other version of this method with no parameters.
    @param evt Event object which includes all the timing information which you have
        calculated for yourself
    @returns False if one or more frame listeners elected that the rendering loop should
        be terminated, true otherwise.
    */
    bool _fireFrameStarted(FrameEvent& evt);
    /** Method for raising frame rendering queued events.
    @remarks
        This method is only for internal use when you use OGRE's inbuilt rendering
        loop (Root::startRendering). However, if you run your own rendering loop then
        you should call this method too, to ensure that all state is updated
		correctly. You should call it after the windows have been updated
		but before the buffers are swapped, or if you are not separating the
		update and buffer swap, then after the update just before _fireFrameEnded.
    */
    bool _fireFrameRenderingQueued(FrameEvent& evt);

    /** Method for raising frame ended events.
    @remarks
        This method is only for internal use when you use OGRE's inbuilt rendering
        loop (Root::startRendering). However, if you run your own rendering loop then
        you should call this method to ensure that FrameListener objects are notified
        of frame events; processes like texture animation and particle systems rely on
        this.
    @note
        This method takes an event object as a parameter, so you can specify the times
        yourself. If you are happy for OGRE to automatically calculate the frame time
        for you, then call the other version of this method with no parameters.
    @param evt Event object which includes all the timing information which you have
        calculated for yourself
    @returns False if one or more frame listeners elected that the rendering loop should
        be terminated, true otherwise.
    */
    bool _fireFrameEnded(FrameEvent& evt);
    /** Method for raising frame started events.
    @remarks
        This method is only for internal use when you use OGRE's inbuilt rendering
        loop (Root::startRendering). However, if you run your own rendering loop then
        you should call this method to ensure that FrameListener objects are notified
        of frame events; processes like texture animation and particle systems rely on
        this.
    @par
        Calling this method also increments the frame number, which is
        important for keeping some elements of the engine up to date.
    @note
        This method calculates the frame timing information for you based on the elapsed
        time. If you want to specify elapsed times yourself you should call the other
        version of this method which takes event details as a parameter.
    @returns False if one or more frame listeners elected that the rendering loop should
        be terminated, true otherwise.
    */
    bool _fireFrameStarted();
    /** Method for raising frame rendering queued events.
    @remarks
        This method is only for internal use when you use OGRE's inbuilt rendering
        loop (Root::startRendering). However, if you run your own rendering loop then
        you you may want to call this method too, although nothing in OGRE relies on this
		particular event. Really if you're running your own rendering loop at
		this level of detail then you can get the same effect as doing your
		updates in a frameRenderingQueued callback by just calling
		RenderWindow::update with the 'swapBuffers' option set to false.
    */
    bool _fireFrameRenderingQueued();
    /** Method for raising frame ended events.
    @remarks
        This method is only for internal use when you use OGRE's inbuilt rendering
        loop (Root::startRendering). However, if you run your own rendering loop then
        you should call this method to ensure that FrameListener objects are notified
        of frame events; processes like texture animation and particle systems rely on
        this.
    @note
        This method calculates the frame timing information for you based on the elapsed
        time. If you want to specify elapsed times yourself you should call the other
        version of this method which takes event details as a parameter.
    @returns False if one or more frame listeners elected that the rendering loop should
        be terminated, true otherwise.
    */
    bool _fireFrameEnded();

	void initializeContext();

	void initializeSceneManager();
	void initializeRenderTarget();
	void initializeCamera();
	void initializeViewport();
	void initializeProjection();


   /** Returns the scene manager currently being used to render a frame.
	@remarks
		This is only intended for internal use; it is only valid during the
		rendering of a frame.
	*/
//	SceneManager* _getCurrentSceneManager(void) const;
	/** Pushes the scene manager currently being used to render.
	@remarks
		This is only intended for internal use.
	*/
	void _pushCurrentSceneManager(SceneManager* sm);
	/** Pops the scene manager currently being used to render.
	@remarks
	This is only intended for internal use.
	*/
	void _popCurrentSceneManager(SceneManager* sm);

	/** Register a new SceneManagerFactory, a factory object for creating instances
		of specific SceneManagers.
	@remarks
		Plugins should call this to register as new SceneManager providers.
	*/
	void addSceneManagerFactory(SceneManagerFactory* fact);

	/** Unregister a SceneManagerFactory.
	*/
	void removeSceneManagerFactory(SceneManagerFactory* fact);

	/** Get more information about a given type of SceneManager.
	@remarks
		The metadata returned tells you a few things about a given type
		of SceneManager, which can be created using a factory that has been
		registered already.
	@param typeName The type name of the SceneManager you want to enquire on.
		If you don't know the typeName already, you can iterate over the
		metadata for all types using getMetaDataIterator.
	*/
	const SceneManagerMetaData* getSceneManagerMetaData(const String& typeName) const;

	/** Iterate over all types of SceneManager available for construction,
		providing some information about each one.
	*/
	SceneManagerEnumerator::MetaDataIterator getSceneManagerMetaDataIterator(void) const;

	/** Create a SceneManager instance of a given type.
	@remarks
		You can use this method to create a SceneManager instance of a
		given specific type. You may know this type already, or you may
		have discovered it by looking at the results from getMetaDataIterator.
	@note
		This method throws an exception if the named type is not found.
	@param typeName String identifying a unique SceneManager type
	@param instanceName Optional name to given the new instance that is
		created. If you leave this blank, an auto name will be assigned.
	*/
	SceneManager* createSceneManager(const String& typeName, const String& instanceName = StringUtil::BLANK);

	/** Create a SceneManager instance based on scene type support.
	@remarks
		Creates an instance of a SceneManager which supports the scene types
		identified in the parameter. If more than one type of SceneManager
		has been registered as handling that combination of scene types,
		in instance of the last one registered is returned.
	@note This method always succeeds, if a specific scene manager is not
		found, the default implementation is always returned.
	@param typeMask A mask containing one or more SceneType flags
	@param instanceName Optional name to given the new instance that is
		created. If you leave this blank, an auto name will be assigned.
	*/
	SceneManager* createSceneManager(SceneTypeMask typeMask, const String& instanceName = StringUtil::BLANK);

	/** Destroy an instance of a SceneManager. */
	void destroySceneManager(SceneManager* sm);

	/** Get an existing SceneManager instance that has already been created,
		identified by the instance name.
	@param instanceName The name of the instance to retrieve.
	*/
	SceneManager* getSceneManager(const String& instanceName) const;
	SceneManager* getSceneManager() const;
	void setActiveSceneManager(SceneManager *sm) { mSceneManager = sm; }

	/** Determines if a given SceneManager already exists
	@param instanceName The name of the instance to retrieve.
	*/
	bool hasSceneManager(const String& instanceName) const;
	/** Get an iterator over all the existing SceneManager instances. */
	SceneManagerEnumerator::SceneManagerIterator getSceneManagerIterator(void);

	MeshManager* getMeshManager();
	UIMeshManager* getUIMeshManager();

	CodecManager* getCodecManager() const;
	EncryptManager* getEncryptManager() const;

//	AbstractScene *createScene();
//	Camera* createCamera(String name, SceneManager *sceneMgr);
//	Camera* createCamera(String name, SceneManager *sceneMgr, Real width, Real height);
//	void destroyCamera();
	Camera* getCamera(const String& name);

	RenderFunction * createRenderFunction();
	void destroyRenderFunction();
	RenderFunction* getRenderFunction();
	void setRenderFunction(RenderFunction* rf);

	//FboRenderTarget* createFboRenderTarget(Real width, Real height);
	RenderTarget* createRenderTarget(Real width, Real height);
	void destroyRenderTargets();
	
//	void addShaderPtr(uint32 id, ShaderPtr sp);
//	ShaderPtr getShaderPtr(uint32 id);
//
//	uint32 getMaterialPtrId(String name);
//	void addMaterialPtr(String name, MaterialPtr matptr);
//	void addMaterialPtr(uint32 id, MaterialPtr matptr);
//	MaterialPtr getMaterialPtr(uint32 id);

	void setCurrentViewport(Viewport* vp) { mViewport = vp;}
	Viewport* getCurrentViewport() const { return mViewport;}

//	uint32 getMeshId(String name);
	void addMesh(String name, IMesh* pMesh);
//	void addMesh(uint32 id, IMesh* pMesh);
//	IMesh* getMesh(uint32 id);
	IMesh* getMesh(String name);
//	void addMesh(MeshMap* pMeshMap);
    void destroyMesh();

	void OnCreate(int width, int height);
	void OnResize(int width, int height);
	void OnDrawFrame();
	void OnTouchEvent(float x, float y);
	void OnTouchEvent(int action, int id, float x, float y);
	void OnStop(bool beStop);
	void OnPause();
	void OnResume();
	void OnDestroy();

	void OnUpdate();

	void OnEvent();


	Root();
	~Root();
//	static Root& getSingleton();
//	static Root* getSingletonPtr();

	void setTouchListener(ISurfaceTouchListener* listener);

	ISurfaceTouchListener* getTouchListener();

	void postRunnable(RunnablePtr r);
	
	void addAutoLayout(IAutoLayout* al);
	void destroyAutoLayout();

	TextureManager* getTextureManager();
	MaterialManager *getMaterialManager();
	FontManager *getFontManager();
	ParticleSystemManager* getParticleSystemManager();
//	ParticleSystemList& getParticleSystemList();
	ParticleSystemListener* getParticleSystemListener();
	void setParticleSystemListener(ParticleSystemListener* listener);
	ScriptEngineManager* getScriptEngineManager();

	HighLevelGpuProgramManager *getHighLevelGpuProgramManager();
	GLSLLinkProgramManager *getGLSLLinkProgramManager();
	ResourceGroupManager* getResourceGroupManager();
	ArchiveManager* getArchiveManager();
//	LogManager* getLogManager();
	IDGenerator* getIDGenerator();
	NameGenerator* getNameGenerator();
	AnimationManager* getAnimationManager();
	ControllerManager* getControllerManager();
	CompositorManager* getCompositorManager();

	VertexElementType getColourVertexElementType(void) const;
	void convertColourValue(const ColourValue& colour, uint32* pDest);

    void addFrameListener(FrameListener* newListener);

    Camera* getMainCamera(const String& name="main_camera");
    /** Removes a FrameListener from the list of listening classes.
        @see
            FrameListener, Root::addFrameListener
    */
    void removeFrameListener(FrameListener* oldListener);
	unsigned long getNextFrameNumber(void) const { return mNextFrame; }

public:
	void dynamicLoad();
	void dynamicUnload();
	void releaseResourceByGroupName(const String& groupName = StringUtil::BLANK);


	void setPackageName(String packageName);
	String getPackageName();

	void setVersion(String version);
	String getVersion();

	void setLocale(String locale);
	String getLocale();

	void setChannel(String channel);
	String getChannel();
};
#endif
