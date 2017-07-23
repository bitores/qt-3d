#ifndef __SceneManager_h__
#define __SceneManager_h__

#include "utils/include/prerequisites.h"
#include "utils/include/platform.h"
#include "utils/include/eBaseAdapter.h"
#include "rendersystem/GpuProgram.h"

#include "rendersystem/RenderQueue.h"
#include "rendersystem/AutoParamDataSource.h"
#include "input/InputEvent.h"
#include "input/IHitTestInfoProvider.h"
#include "input/IInputEventListener.h"

/// Bitmask containing scene types
typedef uint16 SceneTypeMask;

/** Classification of a scene to allow a decision of what type of
SceenManager to provide back to the application.
*/
enum SceneType
{
	ST_GENERIC = 1,
	ST_EXTERIOR_CLOSE = 2,
	ST_EXTERIOR_FAR = 4,
	ST_EXTERIOR_REAL_FAR = 8,
	ST_INTERIOR = 16
};

/** Structure containing information about a scene manager. */
struct SceneManagerMetaData
{
	/// A globally unique string identifying the scene manager type
	String typeName;
	/// A text description of the scene manager
	String description;
	/// A mask describing which sorts of scenes this manager can handle
	SceneTypeMask sceneTypeMask;
	/// Flag indicating whether world geometry is supported
	bool worldGeometrySupported;
};

class SceneManager : public Visitor, public IHitTestInfoProvider,public IInputEventListener
{
protected:
    typedef HashMap<String, CameraPtr> CameraList;
    /** Central list of cameras - for easy memory management and lookup.
    */
    CameraList mCameras;

    int mFPS;
	GameObject* mSkyDomeNode;

    // Sky dome
    bool mSkyDomeEnabled;
    uint8 mSkyDomeRenderQueue;
    Quaternion mSkyDomeOrientation;
//    SkyDomeGenParameters mSkyDomeGenParameters;

//	CullingMode mPassCullingMode;

    virtual GameObject* createGameObjectImpl(void);
    virtual GameObject* createGameObjectImpl(const String& name, bool visible = true);

	/// Instance name
	String mName;

	typedef HashMap<String, GameObject*> GameObjectMap;
	GameObjectMap mSceneNodes;
	
	Root *mRoot;
	GameObject* mSceneRoot;

	RenderQueue mRenderQueue;

	//GameObjectMap mLights;
	std::list<Light*> mLights;

	CompositorChain* mActiveCompositorChain;

	/// Camera in progress
	Camera* mCameraInProgress;
	/// Current Viewport
	Viewport* mCurrentViewport;

    /// Current ambient light, cached for RenderSystem
	ColourValue mAmbientLight;

    /// Cached light information, used to tracking light's changes
    struct LightInfo
    {
        Light* light;       /// Just a pointer for comparison, the light might destroyed for some reason
        int type;           /// Use int instead of Light::LightTypes to avoid header file dependence
        Real range;         /// Sets to zero if directional light
        Vector3 position;   /// Sets to zero if directional light
		//uint32 lightMask;   /// Light mask

        bool operator== (const LightInfo& rhs) const
        {
            return light == rhs.light && type == rhs.type &&
                range == rhs.range && position == rhs.position /*&& lightMask == rhs.lightMask*/;
        }

        bool operator!= (const LightInfo& rhs) const
        {
            return !(*this == rhs);
        }
    };

    typedef vector<LightInfo> LightInfoList;

    LightInfoList mCachedLightInfos;
	LightInfoList mTestLightInfos; // potentially new list

//    ulong mLightsDirtyCounter;
//	LightList mShadowTextureCurrentCasterLightList;

	// the collection of all lights within the scene
//	GameObjectMap mLights;
	// a list of lights that affecting the frustum
	LightList mLightsAffectingFrustum;
    /** Internal method for locating a list of lights which could be affecting the frustum.
    @remarks
        Custom scene managers are encouraged to override this method to make use of their
        scene partitioning scheme to more efficiently locate lights, and to eliminate lights
        which may be occluded by word geometry.
    */
    virtual void findLightsAffectingFrustum(const Camera* camera);

    /// Utility class for calculating automatic parameters for gpu programs
    AutoParamDataSource* mAutoParamDataSource;

    /** Internal method for setting up the renderstate for a rendering pass.
        @param pass The Pass details to set.
		@param evenIfSuppressed Sets the pass details even if render state
			changes are suppressed; if you are using this to manually set state
			when render state changes are suppressed, you should set this to
			true.
		@param shadowDerivation If false, disables the derivation of shadow
			passes from original passes
        @returns
            A Pass object that was used instead of the one passed in, can
            happen when rendering shadow passes
    */
    virtual Pass* _setPass(Pass* pass, bool evenIfSuppressed = false, bool shadowDerivation = true);



public:
	/// Gpu params that need rebinding (mask of GpuParamVariability)
	uint16 mGpuParamsDirty;
    /// Query type mask which will be used for world geometry @see SceneQuery
    static uint32 WORLD_GEOMETRY_TYPE_MASK;
	/// Query type mask which will be used for entities @see SceneQuery
	static uint32 ENTITY_TYPE_MASK;
	/// Query type mask which will be used for effects like billboardsets / particle systems @see SceneQuery
	static uint32 FX_TYPE_MASK;
	/// Query type mask which will be used for StaticGeometry  @see SceneQuery
	static uint32 STATICGEOMETRY_TYPE_MASK;
	/// Query type mask which will be used for lights  @see SceneQuery
	static uint32 LIGHT_TYPE_MASK;
	/// Query type mask which will be used for frusta and cameras @see SceneQuery
	static uint32 FRUSTUM_TYPE_MASK;
	/// User type mask limit
	static uint32 USER_TYPE_MASK_LIMIT;
//	virtual void useLights(const LightList& lights, unsigned short limit);
//	virtual void setViewMatrix(const Matrix4& m);
//	virtual void useLightsGpuProgram(const Pass* pass, const LightList* lights);
	virtual void bindGpuProgram(GpuProgram* prog);
	virtual void updateGpuProgramParameters(const Pass* p);
public:
	SceneManager(Root *root, const String& instanceName);
//	SceneManager(Root *root);
	~SceneManager();

	/** Return the instance name of this SceneManager. */
	const String& getName(void) const { return mName; }
    /** Notifies the scene manager of its destination render system
        @remarks
            Called automatically by RenderSystem::addSceneManager
            this method simply notifies the manager of the render
            system to which its output must be directed.
        @param
            sys Pointer to the RenderSystem subclass to be used as a render target.
    */
    virtual void _setDestinationRenderSystem(RenderFunction* sys);
	/** Empties the entire scene, inluding all SceneNodes, Entities, Lights,
        BillboardSets etc. Cameras are not deleted at this stage since
        they are still referenced by viewports, which are not destroyed during
        this process.
    */
    virtual void clearScene(void);

	/** Retrieve the type name of this scene manager.
	@remarks
		This method has to be implemented by subclasses. It should
		return the type name of this SceneManager which agrees with
		the type name of the SceneManagerFactory which created it.
	*/
	virtual const String& getTypeName(void) const = 0;

	GameObject* getSceneNode(const String& name);

	virtual GameObject* createGameObject(void);

	virtual GameObject* createGameObject(const String& name, bool visible = true);

	virtual eGallery* createGallery(const String& name, eBaseAdapter/*Ptr*/* eba, int initIndex);
	virtual eButton* createButton(const String& name, eRectPtr mesh, MaterialPtr mat);

	virtual void destroyGameObject(const String& name);

	virtual void destroyGameObject(GameObject* sn);

	void destroyGameObjects();

	GameObject* getSceneRoot();
    GameObject* getComponentAt(float x, float y);
    bool processInputEvent(InputEvent &event);
	Root* getRoot() { return mRoot;}

	void OnTouchEvent(float x, float y);

	virtual void _renderScene(Camera* camera, Viewport* vp, bool includeOverlays);

	void collectLights();
//	void findAffectedLights(LightList& lights);

	void prepareRenderQueue();
	void updateSceneGraph();
	void findVisibleObject();
	void renderVisibleObjects();

	void acceptVisitor(GameObject* component);
	void renderSingleObject(GameObject* component, bool lightScissoringClipping = true, bool doLightIteration = true, const LightList* manualLightList = 0);
	void renderSingleObject(Pass* pass, IMesh *mesh, bool lightScissoringClipping = true, bool doLightIteration = true, const LightList* manualLightList = 0);
	/** Do actual rendering operation
	 */
	void renderMesh(RenderFunction* rf, IMesh *mesh);

	/** This function is used by Compositor Module
	 *  Render a GameObject using a specfic Pass instead of the Pass from its internal Material
	 */
	void _renderSingleObjectWithPass(GameObject* component, Pass* pass, bool shadowDerivation = true, bool doLightIteration = false, const LightList* manualLightList = 0, bool useIdentityWorldMatrix = true);

	/** Gets the current viewport being rendered (advanced use only, only
		valid during viewport update. */
	Viewport* getCurrentViewport(void) const { return mCurrentViewport; }

	/** Render something as if it came from the current queue.
		@param pass		Material pass to use for setting up this quad.
		@param rend		Renderable to render
		@param shadowDerivation Whether passes should be replaced with shadow caster / receiver passes
	 */
	//virtual void _injectRenderWithPass(Pass* pass, IMesh* rend);


    /** Internal method for queueing the sky objects with the params as
        previously set through setSkyBox, setSkyPlane and setSkyDome.
    */
    virtual void _queueSkiesForRendering(Camera* cam);

    enum BoxPlane
    {
        BP_FRONT = 0,
        BP_BACK = 1,
        BP_LEFT = 2,
        BP_RIGHT = 3,
        BP_UP = 4,
        BP_DOWN = 5
    };
    enum RenderQueueGroupID
    {
        /// Use this queue for objects which must be rendered first e.g. backgrounds
        RENDER_QUEUE_BACKGROUND = 0,
        /// First queue (after backgrounds), used for skyboxes if rendered first
        RENDER_QUEUE_SKIES_EARLY = 5,
        RENDER_QUEUE_1 = 10,
        RENDER_QUEUE_2 = 20,
		RENDER_QUEUE_WORLD_GEOMETRY_1 = 25,
        RENDER_QUEUE_3 = 30,
        RENDER_QUEUE_4 = 40,
		/// The default render queue
        RENDER_QUEUE_MAIN = 50,
        RENDER_QUEUE_6 = 60,
        RENDER_QUEUE_7 = 70,
		RENDER_QUEUE_WORLD_GEOMETRY_2 = 75,
        RENDER_QUEUE_8 = 80,
        RENDER_QUEUE_9 = 90,
        /// Penultimate queue(before overlays), used for skyboxes if rendered last
        RENDER_QUEUE_SKIES_LATE = 95,
        /// Use this queue for objects which must be rendered last e.g. overlays
        RENDER_QUEUE_OVERLAY = 100,
		/// Final possible render queue, don't exceed this
		RENDER_QUEUE_MAX = 105
    };
    /* Internal utility method for creating the planes of a skydome.
    */
    virtual Mesh* createSkydomePlane(
        BoxPlane bp,
        Real curvature, Real tiling, Real distance,
        const Quaternion& orientation,
        int xsegments, int ysegments, int ySegmentsToKeep,
        const String& groupName);

	/** Enables / disables a 'sky dome' i.e. an illusion of a curved sky.
        @remarks
            A sky dome is actually formed by 5 sides of a cube, but with
            texture coordinates generated such that the surface appears
            curved like a dome. Sky domes are appropriate where you need a
            realistic looking sky where the scene is not going to be
            'fogged', and there is always a 'floor' of some sort to prevent
            the viewer looking below the horizon (the distortion effect below
            the horizon can be pretty horrible, and there is never anyhting
            directly below the viewer). If you need a complete wrap-around
            background, use the setSkyBox method instead. You can actually
            combine a sky box and a sky dome if you want, to give a positional
            backdrop with an overlayed curved cloud layer.
        @par
            Sky domes work well with 2D repeating textures like clouds. You
            can change the apparant 'curvature' of the sky depending on how
            your scene is viewed - lower curvatures are better for 'open'
            scenes like landscapes, whilst higher curvatures are better for
            say FPS levels where you don't see a lot of the sky at once and
            the exaggerated curve looks good.
        @param
            enable True to enable the skydome, false to disable it
        @param
            materialName The name of the material the dome will use
        @param
            curvature The curvature of the dome. Good values are
            between 2 and 65. Higher values are more curved leading to
            a smoother effect, lower values are less curved meaning
            more distortion at the horizons but a better distance effect.
        @param
            tiling How many times to tile the texture(s) across the
            dome.
        @param
            distance Distance in world coorinates from the camera to
            each plane of the box the dome is rendered on. The default
            is normally OK.
        @param
            drawFirst If true, the dome is drawn before all other
            geometry in the scene, without updating the depth buffer.
            This is the safest rendering method since all other objects
            will always appear in front of the sky. However this is not
            the most efficient way if most of the sky is often occluded
            by other objects. If this is the case, you can set this
            parameter to false meaning it draws <em>after</em> all other
            geometry which can be an optimisation - however you must
            ensure that the distance value is large enough that no
            objects will 'poke through' the sky when it is rendered.
        @param
            orientation Optional parameter to specify the orientation
            of the dome. By default the 'top' of the dome is deemed to
            be in the +y direction, and the 'front' at the -z direction.
            You can use this parameter to rotate the sky if you want.
        @param groupName
            The name of the resource group to which to assign the plane mesh.
            */
    virtual void setSkyDome(
        bool enable, const String& materialName, Real curvature = 10,
        Real tiling = 8, Real distance = 500, bool drawFirst = true,
        const Quaternion& orientation = Quaternion::IDENTITY,
        int xsegments = 16, int ysegments = 16, int ysegments_keep = -1,
        const String& groupName = "DEFAULT_RESOURCE_GROUP_NAME");

	/** Enables / disables a 'sky dome' i.e. an illusion of a curved sky.
        @remarks
            A sky dome is actually formed by 5 sides of a cube, but with
            texture coordinates generated such that the surface appears
            curved like a dome. Sky domes are appropriate where you need a
            realistic looking sky where the scene is not going to be
            'fogged', and there is always a 'floor' of some sort to prevent
            the viewer looking below the horizon (the distortion effect below
            the horizon can be pretty horrible, and there is never anyhting
            directly below the viewer). If you need a complete wrap-around
            background, use the setSkyBox method instead. You can actually
            combine a sky box and a sky dome if you want, to give a positional
            backdrop with an overlayed curved cloud layer.
        @par
            Sky domes work well with 2D repeating textures like clouds. You
            can change the apparant 'curvature' of the sky depending on how
            your scene is viewed - lower curvatures are better for 'open'
            scenes like landscapes, whilst higher curvatures are better for
            say FPS levels where you don't see a lot of the sky at once and
            the exaggerated curve looks good.
        @param
            enable True to enable the skydome, false to disable it
        @param
            materialName The name of the material the dome will use
        @param
            curvature The curvature of the dome. Good values are
            between 2 and 65. Higher values are more curved leading to
            a smoother effect, lower values are less curved meaning
            more distortion at the horizons but a better distance effect.
        @param
            tiling How many times to tile the texture(s) across the
            dome.
        @param
            distance Distance in world coorinates from the camera to
            each plane of the box the dome is rendered on. The default
            is normally OK.
        @param
            renderQueue The render queue to use when rendering this object
        @param
            orientation Optional parameter to specify the orientation
            of the dome. By default the 'top' of the dome is deemed to
            be in the +y direction, and the 'front' at the -z direction.
            You can use this parameter to rotate the sky if you want.
        @param groupName
            The name of the resource group to which to assign the plane mesh.
            */
    virtual void _setSkyDome(
        bool enable, const String& materialName, Real curvature = 10,
        Real tiling = 8, Real distance = 500, uint8 renderQueue = RENDER_QUEUE_SKIES_EARLY,
        const Quaternion& orientation = Quaternion::IDENTITY,
        int xsegments = 16, int ysegments = 16, int ysegments_keep = -1,
        const String& groupName = "DEFAULT_RESOURCE_GROUP_NAME");

	/** Enables / disables a 'sky dome' */
	virtual void setSkyDomeEnabled(bool enable) { mSkyDomeEnabled = enable; }

	/** Return whether a skydome is enabled */
	virtual bool isSkyDomeEnabled(void) const { return mSkyDomeEnabled; }

	/** Get the sky dome node, if enabled. */
	virtual GameObject* getSkyDomeNode(void) const { return mSkyDomeNode; }

	/** Sets the active compositor chain of the current scene being rendered.
		@note CompositorChain does this automatically, no need to call manually.
	*/
	virtual void _setActiveCompositorChain(CompositorChain* chain) { mActiveCompositorChain = chain; }

	/** Gets the active compositor chain of the current scene being rendered */
	virtual CompositorChain* _getActiveCompositorChain() const { return mActiveCompositorChain; }

	/** Registers a new RenderQueueListener which will be notified when render queues
		are processed.
	*/
	virtual void addRenderQueueListener(RenderQueueListener* newListener) {mRenderQueue.addRenderQueueListener(newListener);}

	/** Removes a listener previously added with addRenderQueueListener. */
	virtual void removeRenderQueueListener(RenderQueueListener* delListener) {mRenderQueue.removeRenderQueueListener(delListener);}

    /** Sets the ambient light level to be used for the scene.
        @remarks
            This sets the colour and intensity of the ambient light in the scene, i.e. the
            light which is 'sourceless' and illuminates all objects equally.
            The colour of an object is affected by a combination of the light in the scene,
            and the amount of light that object reflects (in this case based on the Material::ambient
            property).
        @remarks
            By default the ambient light in the scene is ColourValue::Black, i.e. no ambient light. This
            means that any objects rendered with a Material which has lighting enabled (see Material::setLightingEnabled)
            will not be visible unless you have some dynamic lights in your scene.
    */
    void setAmbientLight(const ColourValue& colour);

    /** Returns the ambient light level to be used for the scene.
    */
    const ColourValue& getAmbientLight(void) const;

    /** Creates a camera to be managed by this scene manager.
        @remarks
            This camera must be added to the scene at a later time using
            the attachObject method of the SceneNode class.
        @param
            name Name to give the new camera.
    */
    virtual CameraPtr createCamera(const String& name);

    /** Retrieves a pointer to the named camera.
    @note Throws an exception if the named instance does not exist
    */
    virtual CameraPtr getCamera(const String& name) const;

    /** Returns whether a camera with the given name exists.
    */
    virtual bool hasCamera(const String& name) const;

    /** Removes a camera from the scene.
        @remarks
            This method removes a previously added camera from the scene.
            The camera is deleted so the caller must ensure no references
            to it's previous instance (e.g. in a SceneNode) are used.
        @param
            cam Pointer to the camera to remove
    */
    virtual void destroyCamera(CameraPtr cam);

    /** Removes a camera from the scene.
        @remarks
            This method removes an camera from the scene based on the
            camera's name rather than a pointer.
    */
    virtual void destroyCamera(const String& name);

    /** Removes (and destroys) all cameras from the scene.
        @remarks
            Some cameras are internal created to dealing with texture shadow,
            their aren't supposed to destroy outside. So, while you are using
            texture shadow, don't call this method, or you can set the shadow
            technique other than texture-based, which will destroy all internal
            created shadow cameras and textures.
    */
    virtual void destroyAllCameras(void);

    Camera* getCameraInProgress(void) const { return mCameraInProgress; }

    int getFPS() const { return mFPS;}
};


/** Class which will create instances of a given SceneManager. */
class SceneManagerFactory
{
protected:
	Root* mRoot;
	mutable SceneManagerMetaData mMetaData;
	mutable bool mMetaDataInit;
	/// Internal method to initialise the metadata, must be implemented
	virtual void initMetaData(void) const = 0;
public:
	SceneManagerFactory(Root* root)/* : mMetaDataInit(true)*/ {mRoot = root;}
	virtual ~SceneManagerFactory() {}
	/** Get information about the SceneManager type created by this factory. */
	virtual const SceneManagerMetaData& getMetaData(void) const
	{
		if (mMetaDataInit)
		{
			initMetaData();
			mMetaDataInit = false;
		}
		return mMetaData;
	}
	/** Create a new instance of a SceneManager.
	@remarks
	Don't call directly, use SceneManagerEnumerator::createSceneManager.
	*/
	virtual SceneManager* createInstance(const String& instanceName) = 0;
	/** Destroy an instance of a SceneManager. */
	virtual void destroyInstance(SceneManager* instance) = 0;
};


#endif
