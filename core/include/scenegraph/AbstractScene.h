#ifndef __AbstractScene_h__
#define __AbstractScene_h__

class GameObject;

class AbstractScene
{
protected:
	GameObject* mRootTree;

public:
	AbstractScene();
	~AbstractScene();

	void createScene();
	void destroyScene();

	GameObject* getRootTree();

//	void enterScene();
//	void leaveScene();
};
#endif
