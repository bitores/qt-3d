#ifndef __GLWin32RenderFunction_h__
#define __GLWin32RenderFunction_h__

#include "rendersystem/RenderFunction.h"

class GLWin32RenderFunction : public RenderFunction
{
public:
	/** See
	RenderSystem
	*/
	void _setViewMatrix(const Matrix4 &m);
	/** See
	RenderSystem
	*/
	void _setProjectionMatrix(const Matrix4 &m);

	void _setViewport(Viewport *vp);


	/**
	* Set current render target to target, enabling its GL context if needed
	*/
	void _setRenderTarget(RenderTarget *target);

	void _render();
private:
	void makeGLMatrix(Real gl_matrix[16], const Matrix4& m);
};
#endif