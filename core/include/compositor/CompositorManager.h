#ifndef __CompositorManager_h__
#define __CompositorManager_h__

#include "utils/include/prerequisites.h"
#include "compositor/Compositor.h"
#include "compositor/CompositorCustomPass.h"
#include "asset/ResourceManager.h"

class CompositorManager : public ResourceManager
{
private:

public:
	CompositorManager(Root* root);
	~CompositorManager();

    /// Overridden from ResourceManager
    Resource* createImpl(const String& name, ResourceHandle handle,
        const String& group, bool isManual, ManualResourceLoader* loader,
        const NameValuePairList* params);

	/** Initialises the Compositor manager, which also triggers it to
		parse all available .compositor scripts. */
	void initialise(void);

	/**
	 * Create a new compositor
	 * @see ResourceManager::createResource
	 */
	CompositorPtr create (const String& name, const String& group,
						bool isManual = false, ManualResourceLoader* loader = 0,
						const NameValuePairList* createParams = 0);

	/// Get a resource by name
	/// @see ResourceManager::getResourceByName
	CompositorPtr getByName(const String& name, const String& groupName/* = ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME*/);


    /** @see ScriptLoader::parseScript
    */
    void parseScript(DataStreamPtr& stream, const String& groupName);


	 /** Get the compositor chain for a Viewport. If there is none yet, a new
		compositor chain is registered.
		XXX We need a _notifyViewportRemoved to find out when this viewport disappears,
		so we can destroy its chain as well.
	*/
	CompositorChain *getCompositorChain(Viewport *vp);

	/** Returns whether exists compositor chain for a viewport.
	*/
	bool hasCompositorChain(Viewport *vp) const;

	/** Remove the compositor chain from a viewport if exists.
	*/
	void removeCompositorChain(Viewport *vp);

	/** Add a compositor to a viewport. By default, it is added to end of the chain,
		after the other compositors.
		@param vp			Viewport to modify
		@param compositor	The name of the compositor to apply
		@param addPosition	At which position to add, defaults to the end (-1).
		@return pointer to instance, or 0 if it failed.
	*/
	CompositorInstance *addCompositor(Viewport *vp, const String &compositor, const String &groupName, int addPosition=-1);

	/** Remove a compositor from a viewport
	*/
	void removeCompositor(Viewport *vp, const String &compositor);

	/** Set the state of a compositor on a viewport to enabled or disabled.
		Disabling a compositor stops it from rendering but does not free any resources.
		This can be more efficient than using removeCompositor and addCompositor in cases
		the filter is switched on and off a lot.
	*/
	void setCompositorEnabled(Viewport *vp, const String &compositor, bool value);

	/** Get a textured fullscreen 2D rectangle, for internal use.
	*/
	//Rectangle2D *_getTexturedRectangle2D();

	/** Get a textured fullscreen 2D rectangle object, for internal use.
	*/
	GameObject* _getTexturedRectangled2DGameObject();

	/** Removes all compositors. (resource manager)
	@note
		The word 'Destroy' is not used here, since
		if any other pointers are referring to these resources, they will persist
		until they have been finished with; however to all intents and purposes
		the resources no longer exist and will get destroyed imminently.
	@note
		If you do have shared pointers to resources hanging around after the
		ResourceManager is destroyed, you may get problems on destruction of
		these resources if they were relying on the manager (especially if
		it is a plugin). If you find you get problems on shutdown in the
		destruction of resources, try making sure you release all your
		shared pointers before you shutdown OGRE.
	*/
	void removeAll(void);

	typedef set<Texture*> UniqueTextureSet;

	/** Utility function to get an existing pooled texture matching a given
		definition, or creating one if one doesn't exist. It also takes into
		account whether a pooled texture has already been supplied to this
		same requester already, in which case it won't give the same texture
		twice (this is important for example if you request 2 ping-pong textures,
		you don't want to get the same texture for both requests!
	*/
	TexturePtr getPooledTexture(const String& name, const String& localName,
		size_t w, size_t h,
		PixelFormat f, uint aa, const String& aaHint, bool srgb, UniqueTextureSet& texturesAlreadyAssigned,
		CompositorInstance* inst, Compositor::TextureScope scope);

	/** Free pooled textures from the shared pool (compositor instances still
		using them will keep them in memory though).
	*/
	void freePooledTextures(bool onlyIfUnreferenced = true);


	/** Register a compositor logic for listening in to expecting composition
		techniques.
	*/
	void registerCompositorLogic(const String& name, CompositorLogic* logic);

	/** Removes a listener for compositor logic registered with registerCompositorLogic
	*/
	void unregisterCompositorLogic(const String& name);

	/** Get a compositor logic by its name
	*/
	CompositorLogic* getCompositorLogic(const String& name);

	/** Register a custom composition pass.
	*/
	void registerCustomCompositorPass(const String& name, CompositorCustomPass* customPass);

	/** Get a custom composition pass by its name
	*/
	CompositorCustomPass* getCustomCompositorPass(const String& name);

private:

	typedef map<Viewport*, CompositorChain*> Chains;
	Chains mChains;

	/** Clear composition chains for all viewports
	 */
	void freeChains();

	//Rectangle2D* mRectangle;
	GameObject* mRectGameObj;

	/// List of instances
	typedef vector<CompositorInstance*> Instances;
	Instances mInstances;


	// Map of registered compositor logics
	typedef map<String, CompositorLogic*> CompositorLogicMap;
	CompositorLogicMap mCompositorLogics;


	// Map of registered custom composition passes
	typedef map<String, CompositorCustomPass*> CompositorCustomPassMap;
	CompositorCustomPassMap mCompositorCustomPasses;


	/*
	struct TextureDef
	{
		size_t width, height;
		PixelFormat format;
		uint fsaa;
		String fsaaHint;
		bool sRGBwrite;

		TextureDef(size_t w, size_t h, PixelFormat f, uint aa, const String& aaHint, bool srgb)
			: width(w), height(h), format(f), fsaa(aa), fsaaHint(aaHint), sRGBwrite(srgb)
		{

		}
	};
	*/

};
#endif
