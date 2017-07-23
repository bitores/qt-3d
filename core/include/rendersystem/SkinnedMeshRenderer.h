#ifndef __SkinnedMeshRenderer_h__
#define __SkinnedMeshRenderer_h__

#include "Renderer.h"

/*
 * The "Mesh Render" takes the geometry from "Mesh Filter" and renders it
 * at the position defined by the object's Transform component.
 */
class SkinnedMeshRenderer : public Renderer
{
protected:

public:
	SkinnedMeshRenderer(Material* mat);
	~SkinnedMeshRenderer();
};
#endif
