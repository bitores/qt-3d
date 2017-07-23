#ifndef __GLES2HardwareIndexBuffer_H__
#define __GLES2HardwareIndexBuffer_H__

#include "GLES2Prerequisites.h"
#include "hardwarebuffer/HardwareIndexBuffer.h"
//#include "OgreGLES2ManagedResource.h"

class GLES2HardwareIndexBuffer : public HardwareIndexBuffer/* MANAGED_RESOURCE*/
{
	private:
		GLuint mBufferId;
		unsigned char* mData;
	protected:
		/** See HardwareBuffer. */
		void* lockImpl(size_t offset, size_t length, LockOptions options);
		/** See HardwareBuffer. */
		void unlockImpl(void);

		void createBuffer();

		void destroyBuffer();

#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
		/** See AndroidResource. */
		virtual void notifyOnContextLost();

		/** See AndroidResource. */
		virtual void notifyOnContextReset();
#endif

	public:
		GLES2HardwareIndexBuffer(HardwareBufferManagerBase* mgr, IndexType idxType, size_t numIndexes, HardwareBuffer::Usage usage, bool useShadowBuffer);
		virtual ~GLES2HardwareIndexBuffer();
		/** See HardwareBuffer. */
		void readData(size_t offset, size_t length, void* pDest);
		/** See HardwareBuffer. */
		void writeData(size_t offset, size_t length, const void* pSource, bool discardWholeBuffer = false);
#if OGRE_NO_GLES3_SUPPORT == 0
		/** See HardwareBuffer. */
		void copyData(HardwareBuffer& srcBuffer, size_t srcOffset, size_t dstOffset, size_t length, bool discardWholeBuffer = false);
#endif
		/** See HardwareBuffer. */
		void _updateFromShadow(void);

		inline GLuint getGLBufferId(void) const { return mBufferId; }
};

#endif
