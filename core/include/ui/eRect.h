#ifndef __eRect_h__
#define __eRect_h__

#include "utils/include/prerequisites.h"
#include "utils/include/platform.h"
#include "utils/include/Common.h"
#include "base/eCommon.h"
#include "asset/Mesh.h"

class eRect : public Mesh
{
private:
	Anchor mAnchor;
	float mCustomizeAnchorX;
	float mCustomizeAnchorY;

	float mWidth;
	float mHeight;
	float mDepth;
	FloatRect mTextureCoord;
	VertexData* mVertexData;
	IndexData* mIndexData;

	HardwareVertexBufferSharedPtr mMainBuf;

	void getVertices(float& x0, float& y0, float& x1, float& y1, float& x2, float& y2, float& x3, float& y3);
public:
	eRect(ResourceManager* creator, const String& name, ResourceHandle handle, const String& group, bool isManual = false, ManualResourceLoader* loader = 0);
	~eRect();

	void setAnchor(Anchor anchor);
	void setWidth(float width);
	void setHeight(float height);
	void setDepth(float depth);
	float getWidth();
	float getHeight();
	float getDepth();
	void setCustomizeAnchor(float x, float y, bool bCustomizeAnchor = true);
	void setTextureCoord(const FloatRect& r);

	void updateTexCoords(const FloatRect& r);

	void updateTexCoords(float left, float right, float top, float bottom);
	/*

	 v0(0, 0) -------------------v2(w,0)
			  |					|
			  |					|
			  |		  00 		|
			  |					|
			  |					|
	 v1(0, h) -------------------v3(w,h)

	*/
	void resize(float width, float height);
protected:
	void loadImpl();
};

//class MeshManipulator
//{
//public:
//	MeshManipulator(Root* root, MeshPtr mesh);
//	~MeshManipulator();
//
//	void setAnchor(Anchor anchor);
//	void setWidth(float width);
//	void setHeight(float height);
//	void setDepth(float depth);
//	void setCustomizeAnchor(float x, float y, bool bCustomizeAnchor = true);
//	void setTextureCoord(const FloatRect& r);
//	void updateTexCoords(const FloatRect& r);
//	void load();
//	/*
//
//	 v0(0, 0) -------------------v2(w,0)
//			  |					|
//			  |					|
//			  |		  00 		|
//			  |					|
//			  |					|
//	 v1(0, h) -------------------v3(w,h)
//
//	*/
//	void resize(float width, float height);
//public:
//	MeshPtr mMesh;
//private:
//	Anchor mAnchor;
//	float mCustomizeAnchorX;
//	float mCustomizeAnchorY;
//
//	float mWidth;
//	float mHeight;
//	float mDepth;
//	FloatRect mTextureCoord;
//	VertexData* mVertexData;
//	IndexData* mIndexData;
//
//	Root* mRoot;
//
//	HardwareVertexBufferSharedPtr mMainBuf;
//
//	void getVertices(float& x0, float& y0, float& x1, float& y1, float& x2, float& y2, float& x3, float& y3);
//};

//class eRect : public IMesh
//{
//private:
//	Anchor mAnchor;
//	float mCustomizeAnchorX;
//	float mCustomizeAnchorY;
//
//	float mWidth;
//	float mHeight;
//	Root* mRoot;
//	VertexData* mVertexData;
//	IndexData* mIndexData;
//
//	HardwareVertexBufferSharedPtr mMainBuf;
//
//	float r, g, b, a;
//	void _init(float width, float height, float depth, const FloatRect& r);
//	void getVertices(float& x0, float& y0, float& x1, float& y1, float& x2, float& y2, float& x3, float& y3);
//public:
//
//	eRect(Root* root, float width, float height) {
//		mAnchor = CENTER;
//		mRoot = root;
//		mVertexData = 0;
//		mIndexData = 0;
//		_init(width, height, 0, FloatRect(0, 1, 1, 0));
//	}
//
//	eRect(Root* root, float width, float height, float depth) {
//		mAnchor = CENTER;
//		mRoot = root;
//		mVertexData = 0;
//		mIndexData = 0;
//		_init(width, height, depth, FloatRect(0, 1, 1, 0));
//	}
//
//	eRect(Root* root, const FloatRect& r, float width, float height, float depth) {
//		mAnchor = CENTER;
//		mRoot = root;
//		mVertexData = 0;
//		mIndexData = 0;
//		_init(width, height, depth, r);
//	}
//
//	eRect(Root* root, Anchor anchor, float width, float height) {
//		mAnchor = anchor;
//		mRoot = root;
//		mVertexData = 0;
//		mIndexData = 0;
//		_init(width, height, 0, FloatRect(0, 1, 1, 0));
//	}
//
//	eRect(Root* root, Anchor anchor, const FloatRect& r, float width, float height) {
//		mAnchor = anchor;
//		mRoot = root;
//		mVertexData = 0;
//		mIndexData = 0;
//		_init(width, height, 0, r);
//	}
//
//	eRect(Root* root, Anchor anchor, const FloatRect& r, float width, float height, float depth) {
//		mAnchor = anchor;
//		mRoot = root;
//		mVertexData = 0;
//		mIndexData = 0;
//		_init(width, height, depth, r);
//	}
//
//	virtual ~eRect()
//	{
//		AUTO_DELETE(mVertexData);
//		AUTO_DELETE(mIndexData);
//	}
//
//	void setCustomizeAnchor(float x, float y, bool bCustomizeAnchor = true);
//
//	bool hitTest(float x, float y);
//
//	void getRenderOperation(RenderOperationList &opl);
//
//	void updateTexCoords(const FloatRect& r);
//
//	/*
//
//	 v0(0, 0) -------------------v2(w,0)
//			  |					|
//			  |					|
//			  |		  00 		|
//			  |					|
//			  |					|
//	 v1(0, h) -------------------v3(w,h)
//
//	*/
//	void resize(float width, float height);
//
//	float getWidth() const;
//	float getHeight() const;
//};
#endif
