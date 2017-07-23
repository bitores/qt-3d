#ifndef __GLES2DefaultHardwareBufferManager_H__
#define __GLES2DefaultHardwareBufferManager_H__

#include "GLES2Prerequisites.h"
#include "hardwarebuffer/HardwareBufferManager.h"
#include "hardwarebuffer/HardwareVertexBuffer.h"
#include "hardwarebuffer/HardwareUniformBuffer.h"
#include "hardwarebuffer/HardwareIndexBuffer.h"

/// Specialisation of HardwareVertexBuffer for emulation
class GLES2DefaultHardwareVertexBuffer : public HardwareVertexBuffer
{
	protected:
		unsigned char* mData;
		/// @copydoc HardwareBuffer::lock
		void* lockImpl(size_t offset, size_t length, LockOptions options);
		/// @copydoc HardwareBuffer::unlock
		void unlockImpl(void);

	public:
		GLES2DefaultHardwareVertexBuffer(size_t vertexSize, size_t numVertices, HardwareBuffer::Usage usage);
		GLES2DefaultHardwareVertexBuffer(HardwareBufferManagerBase* mgr, size_t vertexSize, size_t numVertices, HardwareBuffer::Usage usage);
		virtual ~GLES2DefaultHardwareVertexBuffer();
		/// @copydoc HardwareBuffer::readData
		void readData(size_t offset, size_t length, void* pDest);
		/// @copydoc HardwareBuffer::writeData
		void writeData(size_t offset, size_t length, const void* pSource, bool discardWholeBuffer = false);
		/** Override HardwareBuffer to turn off all shadowing. */
		void* lock(size_t offset, size_t length, LockOptions options);
		/** Override HardwareBuffer to turn off all shadowing. */
		void unlock(void);

		void* getDataPtr(size_t offset) const { return (void*)(mData + offset); }
};

/// Specialisation of HardwareIndexBuffer for emulation
class GLES2DefaultHardwareIndexBuffer : public HardwareIndexBuffer
{
	protected:
		unsigned char* mData;
		/// @copydoc HardwareBuffer::lock
		void* lockImpl(size_t offset, size_t length, LockOptions options);
		/// @copydoc HardwareBuffer::unlock
		void unlockImpl(void);

	public:
		GLES2DefaultHardwareIndexBuffer(IndexType idxType, size_t numIndexes, HardwareBuffer::Usage usage);
		virtual ~GLES2DefaultHardwareIndexBuffer();
		/// @copydoc HardwareBuffer::readData
		void readData(size_t offset, size_t length, void* pDest);
		/// @copydoc HardwareBuffer::writeData
		void writeData(size_t offset, size_t length, const void* pSource, bool discardWholeBuffer = false);
		/** Override HardwareBuffer to turn off all shadowing. */
		void* lock(size_t offset, size_t length, LockOptions options);
		/** Override HardwareBuffer to turn off all shadowing. */
		void unlock(void);

		void* getDataPtr(size_t offset) const { return (void*)(mData + offset); }
};

/// Specialisation of HardwareUniformBuffer for emulation
class GLES2DefaultHardwareUniformBuffer : public HardwareUniformBuffer
{
protected:
	unsigned char* mData;
	/// @copydoc HardwareBuffer::lock
	void* lockImpl(size_t offset, size_t length, LockOptions options);
	/// @copydoc HardwareBuffer::unlock
	void unlockImpl(void);

public:
	GLES2DefaultHardwareUniformBuffer(size_t bufferSize, HardwareBuffer::Usage usage, bool useShadowBuffer, const String& name);
	GLES2DefaultHardwareUniformBuffer(HardwareBufferManagerBase* mgr, size_t bufferSize, HardwareBuffer::Usage usage, bool useShadowBuffer, const String& name);
	~GLES2DefaultHardwareUniformBuffer();
	/// @copydoc HardwareBuffer::readData
	void readData(size_t offset, size_t length, void* pDest);
	/// @copydoc HardwareBuffer::writeData
	void writeData(size_t offset, size_t length, const void* pSource, bool discardWholeBuffer = false);
	/** Override HardwareBuffer to turn off all shadowing. */
	void* lock(size_t offset, size_t length, LockOptions options);
	/** Override HardwareBuffer to turn off all shadowing. */
	void unlock(void);

	void* getDataPtr(size_t offset) const { return (void*)(mData + offset); }
};

/** Specialisation of HardwareBufferManager to emulate hardware buffers.
@remarks
	You might want to instantiate this class if you want to utilise
	classes like MeshSerializer without having initialised the
	rendering system (which is required to create a 'real' hardware
	buffer manager.
*/
class GLES2DefaultHardwareBufferManagerBase : public HardwareBufferManagerBase
{
public:
	GLES2DefaultHardwareBufferManagerBase(Root* root);
	virtual ~GLES2DefaultHardwareBufferManagerBase();
	/// Creates a vertex buffer
	HardwareVertexBufferSharedPtr createVertexBuffer(size_t vertexSize, size_t numVerts, HardwareBuffer::Usage usage, bool useShadowBuffer = false);
	/// Create a hardware vertex buffer
	HardwareIndexBufferSharedPtr createIndexBuffer(HardwareIndexBuffer::IndexType itype, size_t numIndexes, HardwareBuffer::Usage usage, bool useShadowBuffer = false);
	/// Create a render to vertex buffer
	RenderToVertexBufferSharedPtr createRenderToVertexBuffer(void);

	HardwareUniformBufferSharedPtr createUniformBuffer(size_t sizeBytes, HardwareBuffer::Usage usage,bool useShadowBuffer, const String& name = "");

//	HardwareCounterBufferSharedPtr createCounterBuffer(size_t sizeBytes,  HardwareBuffer::Usage usage = HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE, bool useShadowBuffer = false, const String& name = "")
//	{
//		OGRE_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR,
//					"GLES2 does not support atomic counter buffers",
//					"GLES2DefaultHardwareBufferManagerBase::createCounterBuffer");
//	}
	/// Utility function to get the correct GL usage based on HBU's
	static GLenum getGLUsage(unsigned int usage);

	/// Utility function to get the correct GL type based on VET's
	static GLenum getGLType(unsigned int type);
};

/// GLES2DefaultHardwareBufferManagerBase as a Singleton
class GLES2DefaultHardwareBufferManager : public HardwareBufferManager
{
public:
	GLES2DefaultHardwareBufferManager(Root* root);
	~GLES2DefaultHardwareBufferManager();
};

#endif