#ifndef __Rectangle2D_h__
#define __Rectangel2D_h__

#include "utils/include/prerequisites.h"
#include "utils/include/platform.h"
#include "utils/include/Common.h"
#include "base/eCommon.h"
#include "asset/IMesh.h"

class Rectangle2D : public IMesh
{
private:

	Root* mRoot;
	VertexData* mVertexData;
	IndexData* mIndexData;

	HardwareVertexBufferSharedPtr mMainBuf;

	float r, g, b, a;
	void _init();
public:

	Rectangle2D (Root* root);

	~Rectangle2D();


	 /** Sets the corners of the rectangle, in relative coordinates.
	@param
	left Left position in screen relative coordinates, -1 = left edge, 1.0 = right edge
	@param top Top position in screen relative coordinates, 1 = top edge, -1 = bottom edge
	@param right Right position in screen relative coordinates
	@param bottom Bottom position in screen relative coordinates
	@param depth Depth value
	the new corners. If false, the axis aligned bounding box will remain identical.
	*/
	void setCorners(float left, float top, float right, float bottom);

	/** Sets the normals of the rectangle
	*/
	void setNormals(const Vector3 &topLeft, const Vector3 &bottomLeft, const Vector3 &topRight, const Vector3 &bottomRight);

	/** Sets the UVs of the rectangle
	@remarks
	Doesn't do anything if the rectangle wasn't built with texture coordinates
	*/
	void setUVs( const Vector2 &topLeft, const Vector2 &bottomLeft,
				 const Vector2 &topRight, const Vector2 &bottomRight);

	void setDefaultUVs();

	void getRenderOperation(RenderOperationList &opl);

};
#endif
