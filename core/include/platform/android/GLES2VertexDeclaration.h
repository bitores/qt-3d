#ifndef __GLES2VERTEXDECLARATION_H__
#define __GLES2VERTEXDECLARATION_H__

#include "GLES2Prerequisites.h"
#include "hardwarebuffer/HardwareVertexBuffer.h"

/** Specialisation of VertexDeclaration for OpenGL ES 2 Vertex Array Object usage */
class GLES2VertexDeclaration : public VertexDeclaration
{
protected:
	/// OpenGL id for the vertex array object
	GLuint mVAO;
	bool mIsInitialised;

public:
	GLES2VertexDeclaration(HardwareBufferManagerBase* pHardwareBufferManagerBase);
	~GLES2VertexDeclaration();
	void bind(void);
	bool isInitialised(void) { return mIsInitialised; }
	void setInitialised(bool flag) { mIsInitialised = flag; }
};

#endif
