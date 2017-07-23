#ifndef __MeshRenderer_h__
#define __MeshRenderer_h__

#include "rendersystem/Renderer.h"

class MeshRenderer : public Renderer
{
public:
	MeshRenderer(Material* mat);
	~MeshRenderer();
};

#endif
