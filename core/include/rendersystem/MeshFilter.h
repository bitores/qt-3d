#ifndef __MeshFilter_h__
#define __MeshFilter_h__

#include "component/Component.h"

class MeshFilter : public Component
{
protected:

public:
	IMesh* mMesh;
	bool mFreeOnDestroy;
	MeshFilter(IMesh* mesh, bool freeOnDestroy = true);
	~MeshFilter();
};

#endif
