#ifndef __Renderer_h__
#define __Renderer_h__

#include "component/Component.h"
#include "utils/include/SharedPtr.h"
#include "rendersystem/Material.h"

class Renderer : public Component
{
protected:
    Material* mMaterial;
    
public:
	
	Renderer(Material* mat);
	~Renderer();

    Material* getMaterial();
    void setMaterial(Material* material);
};
typedef SharedPtr<Renderer> RendererPtr;
typedef std::list<RendererPtr> RendererList;

#endif
