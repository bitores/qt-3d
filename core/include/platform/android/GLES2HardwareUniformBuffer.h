#ifndef __GLES2HARDWAREUNIFORMBUFFER_H__
#define __GLES2HARDWAREUNIFORMBUFFER_H__

#include "GLES2Prerequisites.h"
#include "hardwarebuffer/HardwareUniformBuffer.h"

#if OGRE_NO_GLES3_SUPPORT == 0
/// Specialisation of HardwareUniformBuffer for OpenGL
class GLES2HardwareUniformBuffer : public HardwareUniformBuffer
{
	private:
		GLuint mBufferId;
		GLint mBinding;

	protected:
		/** See HardwareBuffer. */
		void* lockImpl(size_t offset, size_t length, LockOptions options);
		/** See HardwareBuffer. */
		void unlockImpl(void);

	public:
		GLES2HardwareUniformBuffer(HardwareBufferManagerBase* mgr, size_t bufferSize, HardwareBuffer::Usage usage, bool useShadowBuffer, const String& name);
		~GLES2HardwareUniformBuffer();

		/** See HardwareBuffer. */
		void readData(size_t offset, size_t length, void* pDest);

		/** See HardwareBuffer. */
		void writeData(size_t offset, size_t length, const void* pSource, bool discardWholeBuffer = false);

		/** See HardwareBuffer. */
		void copyData(HardwareBuffer& srcBuffer, size_t srcOffset, size_t dstOffset, size_t length, bool discardWholeBuffer = false);

		inline GLuint getGLBufferId(void) const { return mBufferId; }
		void setGLBufferBinding(GLint binding);
		inline GLint getGLBufferBinding(void) const { return mBinding; }
};
#endif
#endif // __GLES2HARDWAREUNIFORMBUFFER_H__
