#ifndef __GLES2HardwareBufferManager_H__
#define __GLES2HardwareBufferManager_H__

#include "GLES2Prerequisites.h"
#include "hardwarebuffer/HardwareBufferManager.h"

class GLES2StateCacheManager;

/** Implementation of HardwareBufferManager for OpenGL ES. */
class GLES2HardwareBufferManagerBase : public HardwareBufferManagerBase
{
	protected:
		GLES2StateCacheManager* mStateCacheManager;
		/// Internal method for creates a new vertex declaration, may be overridden by certain rendering APIs
		VertexDeclaration* createVertexDeclarationImpl(void);
		/// Internal method for destroys a vertex declaration, may be overridden by certain rendering APIs
		void destroyVertexDeclarationImpl(VertexDeclaration* decl);

	public:
		GLES2HardwareBufferManagerBase(Root* root);
		virtual ~GLES2HardwareBufferManagerBase();
		/// Creates a vertex buffer
		HardwareVertexBufferSharedPtr createVertexBuffer(size_t vertexSize, size_t numVerts, HardwareBuffer::Usage usage, bool useShadowBuffer = false);
		/// Create a hardware vertex buffer
		HardwareIndexBufferSharedPtr createIndexBuffer(HardwareIndexBuffer::IndexType itype, size_t numIndexes, HardwareBuffer::Usage usage, bool useShadowBuffer = false);
		/// Create a render to vertex buffer
		RenderToVertexBufferSharedPtr createRenderToVertexBuffer();
		HardwareUniformBufferSharedPtr createUniformBuffer(size_t sizeBytes, HardwareBuffer::Usage usage, bool useShadowBuffer, const String& name = "");
		/// Create a uniform buffer
		HardwareUniformBufferSharedPtr createUniformBuffer(size_t sizeBytes, HardwareBuffer::Usage usage, bool useShadowBuffer, size_t binding, const String& name = "");
//		HardwareCounterBufferSharedPtr createCounterBuffer(size_t sizeBytes, HardwareBuffer::Usage usage = HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE, bool useShadowBuffer = false, const String& name = "");

		/// Utility function to get the correct GL usage based on HBU's
		static GLenum getGLUsage(unsigned int usage);

		/// Utility function to get the correct GL type based on VET's
		static GLenum getGLType(unsigned int type);

		GLES2StateCacheManager * getStateCacheManager() { return mStateCacheManager; }
};

/// GLES2HardwareBufferManagerBase as a Singleton
class GLES2HardwareBufferManager : public HardwareBufferManager
{
public:
	GLES2HardwareBufferManager(Root *root);

	~GLES2HardwareBufferManager()
	{
		delete mImpl;
	}

	/// Utility function to get the correct GL usage based on HBU's
	static GLenum getGLUsage(unsigned int usage)
		{ return GLES2HardwareBufferManagerBase::getGLUsage(usage); }

	/// Utility function to get the correct GL type based on VET's
	static GLenum getGLType(unsigned int type)
		{ return GLES2HardwareBufferManagerBase::getGLType(type); }
};
#endif
