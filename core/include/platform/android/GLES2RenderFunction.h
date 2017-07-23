#ifndef __GLES2RenderFunction_H__
#define __GLES2RenderFunction_H__

#include "GLES2Prerequisites.h"

#include "rendersystem/MaterialManager.h"
#include "rendersystem/RenderFunction.h"
//#include "rendersystem/GLES2GpuProgram.h"

class GLES2Context;
class GLES2Support;
class GLES2RTTManager;
class GLES2GpuProgramManager;
class GLSLESProgramFactory;
class GLES2StateCacheManager;
#if !OGRE_NO_GLES2_CG_SUPPORT
class GLSLESCgProgramFactory;
#endif
class GLSLESGpuProgram;
class HardwareBufferManager;
#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
class AndroidResourceManager;
#endif
    
/**
  Implementation of GL ES 2.x as a rendering system.
 */
class GLES2RenderFunction : public RenderFunction
{
	private:
		/// View matrix to set world against
		Matrix4 mViewMatrix;
		Matrix4 mWorldMatrix;
		Matrix4 mTextureMatrix;

		/// Last min & mip filtering options, so we can combine them
		FilterOptions mMinFilter;
		FilterOptions mMipFilter;

		/// What texture coord set each texture unit is using
		size_t mTextureCoordIndex[E3D_MAX_TEXTURE_LAYERS];

		/// Holds texture type settings for every stage
		GLenum mTextureTypes[E3D_MAX_TEXTURE_LAYERS];

		/// Number of fixed-function texture units
		unsigned short mFixedFunctionTextureUnits;

		GLfloat mAutoTextureMatrix[16];

		bool mUseAutoTextureMatrix;

		/// GL support class, used for creating windows etc.
		GLES2Support *mGLSupport;

		/// State cache manager which responsible to reduce redundant state changes
		GLES2StateCacheManager* mStateCacheManager;

//		/* The main GL context - main thread only */
//		GLES2Context *mMainContext;
//
//		/* The current GL context  - main thread only */
//		GLES2Context *mCurrentContext;
//
//		typedef list<GLES2Context*> GLES2ContextList;
//		/// List of background thread contexts
//		GLES2ContextList mBackgroundContextList;
//
//		GLES2GpuProgramManager *mGpuProgramManager;
		GLSLESProgramFactory* mGLSLESProgramFactory;
//#if !OGRE_NO_GLES2_CG_SUPPORT
//		GLSLESCgProgramFactory* mGLSLESCgProgramFactory;
//#endif
		HardwareBufferManager* mHardwareBufferManager;

		/** Manager object for creating render textures.
			Direct render to texture via GL_OES_framebuffer_object is preferable
			to pbuffers, which depend on the GL support used and are generally
			unwieldy and slow. However, FBO support for stencil buffers is poor.
		  */
		GLES2RTTManager *mRTTManager;

		/// Check if the GL system has already been initialised
		bool mGLInitialised;

		// local data member of _render that were moved here to improve performance
		// (save allocations)
		vector<GLuint> mRenderAttribsBound;
		vector<GLuint> mRenderInstanceAttribsBound;

		GLint getCombinedMinMipFilter(void) const;

//		GLES2GpuProgram* mCurrentVertexProgram;
//		GLES2GpuProgram* mCurrentFragmentProgram;
		GLSLProgram* mCurrentVertexProgram;
		GLSLProgram* mCurrentFragmentProgram;

		/** The Active GPU programs and gpu program parameters*/
//		GpuProgramParametersSharedPtr mActiveVertexGpuProgramParameters;
//		GpuProgramParametersSharedPtr mActiveFragmentGpuProgramParameters;

		GLint getTextureAddressingMode(TextureUnitState::TextureAddressingMode tam) const;
		GLenum getBlendMode(SceneBlendFactor ogreBlend) const;
		void bindVertexElementToGpu( const VertexElement &elem, HardwareVertexBufferSharedPtr vertexBuffer,
									const size_t vertexStart,
									vector<GLuint> &attribsBound,
									vector<GLuint> &instanceAttribsBound,
									bool updateVAO);

		// Mipmap count of the actual bounded texture
		size_t mCurTexMipCount;
		GLint mViewport[4];
		GLint mScissor[4];

	public:
		// Default constructor / destructor
		GLES2RenderFunction(Root* root);
		virtual ~GLES2RenderFunction();

		friend class ShaderGeneratorTechniqueResolverListener;

		GLES2RTTManager* getRTTManager() {return mRTTManager; }
		HardwareBufferManager* getHardwareBufferManager() { return mHardwareBufferManager;}
		// ----------------------------------
		// Overridden RenderFunction functions
		// ----------------------------------
		/** See
		  RenderFunction
		 */
		const String& getName(void) const;
//		/** See
//		  RenderFunction
//		 */
//		ConfigOptionMap& getConfigOptions(void);
//		/** See
//		  RenderFunction
//		 */
//		void setConfigOption(const String &name, const String &value);
//		/** See
//		  RenderFunction
//		 */
//		String validateConfigOptions(void);
		/** See
		  RenderFunction
		 */
		RenderWindow* _initialise(bool autoCreateWindow, const String& windowTitle = "OGRE Render NativeWindowType");
		/** See
		  RenderFunction
		 */
		virtual RenderSystemCapabilities* createRenderSystemCapabilities() const;
		/** See
		  RenderFunction
		 */
		void initialiseFromRenderSystemCapabilities(RenderSystemCapabilities* caps, RenderTarget* primary);
		/** See
		  RenderFunction
		 */
		void reinitialise(void); // Used if settings changed mid-rendering
		/** See
		  RenderFunction
		 */
		void shutdown(void);
		/** See
		  RenderFunction
		 */
		void setAmbientLight(float r, float g, float b) { };   // Not supported
		/** See
		  RenderFunction
		 */
		void setShadingType(ShadeOptions so) { };   // Not supported
		/** See
		  RenderFunction
		 */
		void setLightingEnabled(bool enabled) { };   // Not supported

		/// @copydoc RenderFunction::_createRenderWindow
		RenderWindow* _createRenderWindow(const String &name, unsigned int width, unsigned int height,
			bool fullScreen, const NameValuePairList *miscParams = 0);

		/// @copydoc RenderFunction::_createDepthBufferFor
		DepthBuffer* _createDepthBufferFor( RenderTarget *renderTarget );

		/// Mimics D3D9RenderFunction::_getDepthStencilFormatFor, if no FBO RTT manager, outputs GL_NONE
		void _getDepthStencilFormatFor( GLenum internalColourFormat, GLenum *depthFormat,
										GLenum *stencilFormat );

		/// @copydoc RenderFunction::createMultiRenderTarget
		virtual MultiRenderTarget * createMultiRenderTarget(const String & name);

		/** See
		  RenderFunction
		 */
		void destroyRenderWindow(RenderWindow* pWin);
		/** See
		  RenderFunction
		 */
		String getErrorDescription(long errorNumber) const;
		/** See
		  RenderFunction
		 */
		VertexElementType getColourVertexElementType(void) const;
		/** See
		  RenderFunction
		 */
		void setNormaliseNormals(bool normalise) { };   // Not supported

		// -----------------------------
		// Low-level overridden members
		// -----------------------------
		/** See
		 RenderFunction
		 */
		void _useLights(const LightList& lights, unsigned short limit) { };   // Not supported
		/** See
		 RenderFunction
		 */
		bool areFixedFunctionLightsInViewSpace() const { return true; }
		/** See
		 RenderFunction
		 */
		void _setWorldMatrix(const Matrix4 &m);
		/** See
		 RenderFunction
		 */
		void _setViewMatrix(const Matrix4 &m);
		/** See
		 RenderFunction
		 */
		void _setProjectionMatrix(const Matrix4 &m);
		/** See
		 RenderFunction
		 */
		void _setSurfaceParams(const ColourValue &ambient,
							   const ColourValue &diffuse, const ColourValue &specular,
							   const ColourValue &emissive, Real shininess,
							   TrackVertexColourType tracking) {}
		/** See
		 RenderFunction
		 */
		void _setPointParameters(Real size, bool attenuationEnabled,
								 Real constant, Real linear, Real quadratic, Real minSize, Real maxSize) {}
		/** See
		 RenderFunction
		 */
		void _setPointSpritesEnabled(bool enabled) {}
		/** See
		 RenderFunction
		 */
		void _setTexture(size_t unit, bool enabled, const TexturePtr &tex);
		/** See
		 RenderFunction
		 */
		void _setTextureCoordSet(size_t stage, size_t index);
		/** See
		 RenderFunction
		 */
		void _setTextureCoordCalculation(size_t stage, TexCoordCalcMethod m,
				const Frustum* frustum = 0) { };   // Not supported
		/** See
		 RenderFunction
		 */
		void _setTextureBlendMode(size_t stage, const LayerBlendModeEx& bm) { };   // Not supported
		/** See
		 RenderFunction
		 */
		void _setTextureAddressingMode(size_t stage, const TextureUnitState::UVWAddressingMode& uvw);
		/** See
		 RenderFunction
		 */
		void _setTextureBorderColour(size_t stage, const ColourValue& colour) { };   // Not supported
		/** See
		 RenderFunction
		 */
		void _setTextureMipmapBias(size_t unit, float bias) { };   // Not supported
		/** See
		 RenderFunction
		 */
		void _setTextureMatrix(size_t stage, const Matrix4& xform) { };   // Not supported
		/** See
		 RenderFunction
		 */
		void _setViewport(Viewport *vp);
		/** See
		 RenderFunction
		 */
		void _beginFrame(void);
		/** See
		 RenderFunction
		 */
		void _endFrame(void);
		/** See
		 RenderFunction
		 */
		void _setCullingMode(CullingMode mode);
		/** See
		 RenderFunction
		 */
		void _setDepthBufferParams(bool depthTest = true, bool depthWrite = true, CompareFunction depthFunction = CMPF_LESS_EQUAL);
		/** See
		 RenderFunction
		 */
		void _setDepthBufferCheckEnabled(bool enabled = true);
		/** See
		 RenderFunction
		 */
		void _setDepthBufferWriteEnabled(bool enabled = true);
		/** See
		 RenderFunction
		 */
		void _setDepthBufferFunction(CompareFunction func = CMPF_LESS_EQUAL);
		/** See
		 RenderFunction
		 */
		void _setDepthBias(float constantBias, float slopeScaleBias);
		/** See
		 RenderFunction
		 */
		void _setColourBufferWriteEnabled(bool red, bool green, bool blue, bool alpha);
		/** See
		 RenderFunction
		 */
		void _setFog(FogMode mode, const ColourValue& colour, Real density, Real start, Real end);
		/** See
		 RenderFunction
		 */
		void _convertProjectionMatrix(const Matrix4& matrix,
				Matrix4& dest, bool forGpuProgram = false);
		/** See
		 RenderFunction
		 */
		void _makeProjectionMatrix(const Radian& fovy, Real aspect, Real nearPlane, Real farPlane,
				Matrix4& dest, bool forGpuProgram = false);
		/** See
		 RenderFunction
		 */
		void _makeProjectionMatrix(Real left, Real right, Real bottom, Real top,
				Real nearPlane, Real farPlane, Matrix4& dest, bool forGpuProgram = false);
		/** See
		 RenderFunction
		 */
		void _makeOrthoMatrix(const Radian& fovy, Real aspect, Real nearPlane, Real farPlane,
				Matrix4& dest, bool forGpuProgram = false);
		/** See
		 RenderFunction
		 */
		void _applyObliqueDepthProjection(Matrix4& matrix, const Plane& plane,
				bool forGpuProgram);
		/** See
		 RenderFunction
		 */
		void setClipPlane (ushort index, Real A, Real B, Real C, Real D);
		/** See
		 RenderFunction
		 */
		void enableClipPlane (ushort index, bool enable);
		/** See
		 RenderFunction
		 */
		void _setPolygonMode(PolygonMode level);
		/** See
		 RenderFunction
		 */
		void setStencilCheckEnabled(bool enabled);
		/** See
		 RenderFunction
		 */
		void setStencilBufferParams(CompareFunction func = CMPF_ALWAYS_PASS,
				uint32 refValue = 0, uint32 compareMask = 0xFFFFFFFF, uint32 writeMask = 0xFFFFFFFF,
				StencilOperation stencilFailOp = SOP_KEEP,
				StencilOperation depthFailOp = SOP_KEEP,
				StencilOperation passOp = SOP_KEEP,
				bool twoSidedOperation = false);
		 /** See
		  RenderFunction
		 */
		void _setTextureUnitCompareFunction(size_t unit, CompareFunction function);
		 /** See
		  RenderFunction
		 */
		void _setTextureUnitCompareEnabled(size_t unit, bool compare);
		/** See
		 RenderFunction
		 */
		virtual void _setTextureUnitFiltering(size_t unit, FilterOptions minFilter,
			FilterOptions magFilter, FilterOptions mipFilter);
		/** See
		 RenderFunction
		 */
		void _setTextureUnitFiltering(size_t unit, FilterType ftype, FilterOptions filter);
		/** See
		 RenderFunction
		 */
		void _setTextureLayerAnisotropy(size_t unit, unsigned int maxAnisotropy);
		/** See
		 RenderFunction
		 */
		virtual bool hasAnisotropicMipMapFilter() const { return false; }
		/** See
		 RenderFunction
		 */
		void setVertexDeclaration(VertexDeclaration* decl);
		/** See
		 RenderFunction
		 */
		void setVertexDeclaration(VertexDeclaration* decl, VertexBufferBinding* binding);
		/** See
		 RenderFunction
		 */
		void setVertexBufferBinding(VertexBufferBinding* binding) {}
		/** See
		 RenderFunction
		 */
		void _render(const RenderOperation& op);
		/** See
		 RenderFunction
		 */
		void setScissorTest(bool enabled, size_t left = 0, size_t top = 0, size_t right = 800, size_t bottom = 600);

		void clearFrameBuffer(unsigned int buffers,
			const ColourValue& colour = ColourValue::Black,
			Real depth = 1.0f, unsigned short stencil = 0);
		HardwareOcclusionQuery* createHardwareOcclusionQuery(void);
		Real getHorizontalTexelOffset(void) { return 0.0; }               // No offset in GL
		Real getVerticalTexelOffset(void) { return 0.0; }                 // No offset in GL
		Real getMinimumDepthInputValue(void) { return -1.0f; }            // Range [-1.0f, 1.0f]
		Real getMaximumDepthInputValue(void) { return 1.0f; }             // Range [-1.0f, 1.0f]
		OGRE_MUTEX(mThreadInitMutex);
		void registerThread();
		void unregisterThread();
		void preExtraThreadsStarted();
		void postExtraThreadsStarted();
		void setClipPlanesImpl(const PlaneList& planeList) {}
//		GLES2Support* getGLSupportRef() { return mGLSupport; }

//		// ----------------------------------
//		// GLES2RenderFunction specific members
//		// ----------------------------------
//		/** Returns the main context */
//		GLES2Context* _getMainContext() { return mMainContext; }
//		/** Unregister a render target->context mapping. If the context of target
//		 is the current context, change the context to the main context so it
//		 can be destroyed safely.
//
//		 @note This is automatically called by the destructor of
//		 GLES2Context.
//		 */
//		void _unregisterContext(GLES2Context *context);
//		/** Switch GL context, dealing with involved internal cached states too
//		 */
//		void _switchContext(GLES2Context *context);
		/** One time initialization for the RenderState of a context. Things that
		 only need to be set once, like the LightingModel can be defined here.
		 */
		void _oneTimeContextInitialization();
		void initialiseContext(RenderWindow* primary);
		/**
		 * Set current render target to target, enabling its GL context if needed
		 */
		void _setRenderTarget(RenderTarget *target);

		GLES2Support* getGLES2SupportRef();
		GLint convertCompareFunction(CompareFunction func) const;
		GLint convertStencilOp(StencilOperation op, bool invert = false) const;

		void bindGpuProgram(GpuProgram* prg);
		void unbindGpuProgram(GpuProgramType gptype);
		void bindGpuProgramParameters(GpuProgramType gptype, GpuProgramParametersSharedPtr params, uint16 mask);
		void bindGpuProgramPassIterationParameters(GpuProgramType gptype);

		/// @copydoc RenderFunction::_setSceneBlending
		void _setSceneBlending( SceneBlendFactor sourceFactor, SceneBlendFactor destFactor, SceneBlendOperation op );
		/// @copydoc RenderFunction::_setSeparateSceneBlending
		void _setSeparateSceneBlending( SceneBlendFactor sourceFactor, SceneBlendFactor destFactor, SceneBlendFactor sourceFactorAlpha, SceneBlendFactor destFactorAlpha, SceneBlendOperation op, SceneBlendOperation alphaOp );
		/// @copydoc RenderFunction::_setAlphaRejectSettings
		void _setAlphaRejectSettings( CompareFunction func, unsigned char value, bool alphaToCoverage );
		/// @copydoc RenderFunction::getDisplayMonitorCount
		unsigned int getDisplayMonitorCount() const;

		/// Internal method for anisotropy validation
		GLfloat _getCurrentAnisotropy(size_t unit);

		void _setSceneBlendingOperation(SceneBlendOperation op);
		void _setSeparateSceneBlendingOperation(SceneBlendOperation op, SceneBlendOperation alphaOp);

		unsigned int getDiscardBuffers(void);

		void _destroyDepthBuffer(RenderWindow* pRenderWnd);

		/// @copydoc RenderFunction::beginProfileEvent
		virtual void beginProfileEvent( const String &eventName );

		/// @copydoc RenderFunction::endProfileEvent
		virtual void endProfileEvent( void );

		/// @copydoc RenderFunction::markProfileEvent
		virtual void markProfileEvent( const String &eventName );

		void releaseResources();
//#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
//		void resetRenderer(RenderWindow* pRenderWnd);
//
//		static AndroidResourceManager* getResourceManager();
//private:
//		static AndroidResourceManager* mResourceManager;
//#endif
};

#endif
