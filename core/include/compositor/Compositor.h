#ifndef __Compositor_h__
#define __Compositor_h__

#include "utils/include/prerequisites.h"
#include "utils/include/SharedPtr.h"
#include "rendersystem/Texture.h"
#include "base/Object.h"
#include "compositor/CompositorTargetPass.h"
#include "utils/include/IteratorWrapper.h"

/** Class representing a Compositor object. Compositors provide the means
	to flexibly "composite" the final rendering result from multiple scene renders
	and intermediate operations like rendering fullscreen quads. This makes
	it possible to apply postfilter effects, HDRI postprocessing, and shadow
	effects to a Viewport.
 */
class Compositor : public Resource
{
public:
    Compositor(ResourceManager* creator, const String& name, ResourceHandle handle,
        const String& group, bool isManual = false, ManualResourceLoader* loader = 0);
	~Compositor();

	//The scope of a texture defined by the compositor
	enum TextureScope {
		//Local texture - only available to the compositor passes in this technique
		TS_LOCAL,
		//Chain texture - available to the other compositors in the chain
		TS_CHAIN,
		//Global texture - available to everyone in every scope
		TS_GLOBAL
	};

	/// Local texture definition
	class TextureDefinition
	{
	public:
		String name;
		//Texture definition being a reference is determined by these two fields not being empty.
		String refCompName; //If a reference, the name of the compositor being referenced
		String refTexName;	//If a reference, the name of the texture in the compositor being referenced
		size_t width;       // 0 means adapt to target width
		size_t height;      // 0 means adapt to target height
		float widthFactor;  // multiple of target width to use (if width = 0)
		float heightFactor; // multiple of target height to use (if height = 0)
		PixelFormatList formatList; // more than one means MRT
		bool fsaa;			// FSAA enabled; true = determine from main target (if render_scene), false = disable
		bool hwGammaWrite;	// Do sRGB gamma correction on write (only 8-bit per channel formats)
		uint16 depthBufferId;//Depth Buffer's pool ID. (unrelated to "pool" variable below)
		bool pooled;		// whether to use pooled textures for this one
		TextureScope scope; // Which scope has access to this texture

		TextureDefinition() :width(0), height(0), widthFactor(1.0f), heightFactor(1.0f),
			fsaa(true), hwGammaWrite(false), depthBufferId(1), pooled(false), scope(TS_LOCAL) {}
	};

	typedef std::vector<TextureDefinition*> TextureDefinitions;
	typedef VectorIterator<TextureDefinitions> TextureDefinitionIterator;
	typedef std::vector<CompositorTargetPass*> TargetPasses;
	typedef VectorIterator<TargetPasses> TargetPassIterator;

	/** Create a new local texture definition, and return a pointer to it.
		@param name     Name of the local texture
	*/
	TextureDefinition *createTextureDefinition(const String &name);

	/** Remove and destroy a local texture definition.
	*/
	void removeTextureDefinition(size_t idx);

	/** Get a local texture definition.
	*/
	TextureDefinition *getTextureDefinition(size_t idx);

	/** Get a local texture definition with a specific name.
	*/
	TextureDefinition *getTextureDefinition(const String& name);

	/** Get an iterator over the TextureDefinitions in this Technique. */
	TextureDefinitionIterator getTextureDefinitionIterator(void);

	/** Get the number of local texture definitions.
	*/
	size_t getNumTextureDefinitions();

	 /** Remove all Texture Definitions
	*/
	void removeAllTextureDefinitions();

	 /** Create a new target pass, and return a pointer to it.
	*/
	CompositorTargetPass *createTargetPass();

	/** Remove a target pass. It will also be destroyed.
	*/
	void removeTargetPass(size_t idx);

	/** Get a target pass.
	*/
	CompositorTargetPass *getTargetPass(size_t idx);

	/** Get an iterator over the TargetPasses in this compositor. */
	TargetPassIterator getTargetPassIterator(void);

	/** Get the number of target passes.
	*/
	size_t getNumTargetPasses();

	/** Remove all target passes.
	*/
	void removeAllTargetPasses();

	/** Get output (final) target pass
	 */
	CompositorTargetPass *getOutputTargetPass();

	/** Set the name of the compositor logic assigned to this technique.
		Instances of this technique will be auto-coupled with the matching logic.
	*/
	void setCompositorLogicName(const String& compositorLogicName)
				{ mCompositorLogicName = compositorLogicName; }
	/** Get the compositor logic name assigned to this technique */
	const String& getCompositorLogicName() const { return mCompositorLogicName; }

	 /** 'Touches' the resource to indicate it has been used.(resource manager)
	*/
	void touch(void);

	void loadImpl(void);
    /// @copydoc Resource::unloadImpl
    void unloadImpl(void);
    /// @copydoc Resource::calculateSize
    size_t calculateSize(void) const;

	/** Get the instance name for a global texture.
	@param name The name of the texture in the original compositor definition
	@param mrtIndex If name identifies a MRT, which texture attachment to retrieve
	@return The instance name for the texture, corresponds to a real texture
	*/
	const String& getTextureInstanceName(const String& name, size_t mrtIndex);

	/** Get the instance of a global texture.
	@param name The name of the texture in the original compositor definition
	@param mrtIndex If name identifies a MRT, which texture attachment to retrieve
	@return The texture pointer, corresponds to a real texture
	*/
	TexturePtr getTextureInstance(const String& name, size_t mrtIndex);

	/** Get the render target for a given render texture name.
	@remarks
		You can use this to add listeners etc, but do not use it to update the
		targets manually or any other modifications, the compositor instance
		is in charge of this.
	*/
	RenderTarget* getRenderTarget(const String& name);


	// (resource manager)
	virtual const String& getName(void) const { return mName;}


private:
	/// Local texture definitions
	TextureDefinitions mTextureDefinitions;

	/// Intermediate target passes
	TargetPasses mTargetPasses;

	/// Output target pass (can be only one)
	CompositorTargetPass *mOutputTarget;


	/// Optional compositor logic name
	String mCompositorLogicName;



	// --- global render textures ---
	// Create global rendertextures.
	void createGlobalTextures();

	// Destroy global rendertextures.
	void freeGlobalTextures();

	/// Map from name->local texture
	typedef HashMap<String,TexturePtr> GlobalTextureMap;
	GlobalTextureMap mGlobalTextures;
	/// Store a list of MRTs we've created
	typedef HashMap<String,MultiRenderTarget*> GlobalMRTMap;
	GlobalMRTMap mGlobalMRTs;
	// -----------------------------



};

#endif
