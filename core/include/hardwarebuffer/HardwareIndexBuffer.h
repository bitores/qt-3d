#ifndef __HardwareIndexBuffer__
#define __HardwareIndexBuffer__

// Precompiler options
#include "utils/include/prerequisites.h"
#include "utils/include/SharedPtr.h"
#include "HardwareBuffer.h"

class HardwareBufferManagerBase;

/** \addtogroup Core
*  @{
*/
/** \addtogroup RenderSystem
*  @{
*/
/** Specialisation of HardwareBuffer for vertex index buffers, still abstract. */
class HardwareIndexBuffer : public HardwareBuffer
{
	public:
		enum IndexType {
			IT_16BIT,
			IT_32BIT
		};

	protected:
		HardwareBufferManagerBase* mMgr;
		IndexType mIndexType;
		size_t mNumIndexes;
		size_t mIndexSize;

	public:
		/// Should be called by HardwareBufferManager
		HardwareIndexBuffer(HardwareBufferManagerBase* mgr, IndexType idxType, size_t numIndexes, HardwareBuffer::Usage usage,
			bool useSystemMemory, bool useShadowBuffer);
		~HardwareIndexBuffer();
		/// Return the manager of this buffer, if any
		HardwareBufferManagerBase* getManager() const { return mMgr; }
		/// Get the type of indexes used in this buffer
		IndexType getType(void) const { return mIndexType; }
		/// Get the number of indexes in this buffer
		size_t getNumIndexes(void) const { return mNumIndexes; }
		/// Get the size in bytes of each index
		size_t getIndexSize(void) const { return mIndexSize; }

		// NB subclasses should override lock, unlock, readData, writeData
};


/** Shared pointer implementation used to share index buffers. */
class HardwareIndexBufferSharedPtr : public SharedPtr<HardwareIndexBuffer>
{
public:
	HardwareIndexBufferSharedPtr() : SharedPtr<HardwareIndexBuffer>() {}
	explicit HardwareIndexBufferSharedPtr(HardwareIndexBuffer* buf);
};

/** Locking helper. */
typedef HardwareBufferLockGuard<HardwareIndexBufferSharedPtr> HardwareIndexBufferLockGuard;

/** @} */
/** @} */
#endif

