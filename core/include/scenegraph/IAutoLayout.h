#ifndef __IAutoLayout_h__
#define __IAutoLayout_h__

#include "utils/include/Vector3.h"
#include "ui/eRect.h"

class Transform;

class IAutoLayout
{
protected:
	Vector3 mScaleFactor;
	int mSMode;
public:
	IAutoLayout(Vector3 sf, int mode);
	virtual ~IAutoLayout();
	virtual void autoLayout(float width, float height) = 0;
};

class MeshLayout : public IAutoLayout
{
private:
	eRectPtr mRect;
public:
	MeshLayout(eRectPtr target, Vector3 sf, int mode);
	void autoLayout(float width, float height);
};

class TransformLayout : public IAutoLayout
{
private:
	int mTMode;
	Vector3 mTranslateFactor;
	Transform* mTransform;
public:
	TransformLayout(Transform* target, Vector3 sf, int mode, Vector3 tf, int tmode);
	void autoLayout(float width, float height);
};

#endif
