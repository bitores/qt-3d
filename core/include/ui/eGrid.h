#ifndef __eGrid_h__
#define __eGrid_h__

#include "utils/include/prerequisites.h"
#include "utils/include/Common.h"
#include "asset/IMesh.h"

class eGrid : public IMesh
{
private:
	Root *mRoot;
	float mWidth;
	float mHeight;
	VertexData* mVertexData;
//	IndexData* mIndexData;
	void _init(float width, float height, int row, int col);
public:
	eGrid(Root* root, float width, float height, int row, int col);
	~eGrid();

	void getRenderOperation(RenderOperationList &opl);
//	void resize(float width, float height);
};
#endif
