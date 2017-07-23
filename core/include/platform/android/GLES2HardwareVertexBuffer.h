#ifndef __GLES2HardwareVertexBuffer_H__
#define __GLES2HardwareVertexBuffer_H__

#include "GLES2Prerequisites.h"
#include "hardwarebuffer/HardwareVertexBuffer.h"
//#include "GLES2ManagedResource.h"

/// Specialisation of HardwareVertexBuffer for OpenGL ES
class GLES2HardwareVertexBuffer : public HardwareVertexBuffer /*MANAGED_RESOURCE*/
{
	private:
		GLuint mBufferId;
//		GLsync mFence;
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
		GLES2HardwareVertexBuffer(HardwareBufferManagerBase* mgr, size_t vertexSize, size_t numVertices, HardwareBuffer::Usage usage, bool useShadowBuffer);
		virtual ~GLES2HardwareVertexBuffer();

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
		void setFence(void);
};
#endif
