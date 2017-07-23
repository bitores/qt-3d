#ifndef __Component_h__
#define __Component_h__

#include "utils/include/prerequisites.h"
#include "utils/include/platform.h"
#include "utils/include/SharedPtr.h"

class Component
{
protected:
	GameObject* mGameObject;
//	Transform* mTransform;
public:
//	Component(GameObject* pGameObject);
	Component();
	virtual ~Component();

	// notified by GameObject when transform has been changed;
	virtual void _notifyTransformChanged() {}

	virtual void _notifyAttached(GameObject* parent) {}

//	void setTransform(Transform* transform);
//	Transform* getTransform();

	void setGameObject(GameObject* pGameObject);
	GameObject* getGameObject();
};
typedef SharedPtr<Component> ComponentPtr;

#endif
