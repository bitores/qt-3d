#ifndef __eButton_h__
#define __eButton_h__

#include "utils/include/prerequisites.h"
#include "utils/include/Common.h"
#include "ui/eRect.h"
#include "rendersystem/Material.h"
#include "scenegraph/GameObject.h"

class eButton : public GameObject
{
private:
	Root *mRoot;
	FloatRect* mTexCoords;
	eRectPtr mRect;
	MaterialPtr mMaterial;
	IClickListener *mClickListener;

	int mCurrentIndex;
public:
	eButton(Root* root, const String& name, eRectPtr rect, MaterialPtr mat, FloatRect* texcoords=NULL);
	~eButton();

	bool OnTouchEvent(int action, float x, float y);
//	void setPosition(float x, float y, float z);
//	GameObject* getParent();

	void setTextureIndex(int index);
	void setOnClickListener(IClickListener *listener);

//	void resize(float width, float height);
};
#endif
