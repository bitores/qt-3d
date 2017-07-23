#ifndef __FboRenderTarget__h
#define __FboRenderTarget__h

#include "utils/include/platform.h"
#include "utils/include/prerequisites.h"
#include "platform/RenderFunctionPrerequisites.h"
#include "platform/win/glInfo.h"

#include "RenderTarget.h"

class FboRenderTarget : public RenderTarget
{
private:
	uint mFrameBufferHandle;
	uint mRenderbufferHandle;
	uint mTextureHandle;
	glInfo glInfo;

private:
	bool isInitialized;
	void initialize();
	// Plane mPostProcessingQuad
	// Camera2D mPostProcessingCam;
public:
	FboRenderTarget(uint width, uint height);

	void bind();
	void unbind();

	void create();
	void destroy();

	void printFramebufferInfo();
	std::string convertInternalFormatToString(GLenum format);
	std::string getTextureParameters(GLuint id);
	std::string getRenderbufferParameters(GLuint id);

	void clear(bool clearColorBuffer, float r, float g, float b, float a, bool clearDepthBuffer);

	uint getTextureHandle() {
		return mTextureHandle;
	}
};
#endif
