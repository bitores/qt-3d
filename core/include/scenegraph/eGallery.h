#ifndef __eGallery_h__
#define __eGallery_h__

#include "GameObject.h"
#include "utils/include/eBaseAdapter.h"

struct T_ORGANIZE_MODE
{
	enum TYPE
	{
		VOERLAP = 0,
		TILE_X_DIRECTION,
		TILE_Y_DIRECTION
	};
};

struct T_SWITCH_MODE
{
	enum TYPE
	{
		NO_ANIMATION = 0,
		X_TRANSLATE_ANIMATION,
		Y_TRANSLATE_ANIMATION,
		CENTER_SCALE_ANIMATION,
		CENTER_SCALE_TRANSPARENT_ANIMATION
	};
};

class eGallery : public GameObject
{
protected:
	float mWidth;
	float mHeight;
	Vector3 mPosition;
	eBaseAdapter/*Ptr */ *mBaseAdapterPtr;
	int mCurrIndex;
	bool mDir;
//	bool mFirstResize;
	T_SWITCH_MODE::TYPE mSwitchMode;
	float mFlingSlop;

	std::vector<GameObject*> mItems;
	Root* mRoot;
	void animate(float fromX, float toX);
public:
	eGallery(const String& name, Root* root, eBaseAdapter/*Ptr */ * eba, int initIndex);
	~eGallery();

	void setSwitchMode(T_SWITCH_MODE::TYPE mode);
	T_SWITCH_MODE::TYPE getSwitchMode();

	bool isHit(float x, float y);

	int toLeft();
	int toRight();
	int activatePage(int index);
	void addUI(int position);

	bool onFlingEvent(float fromX, float fromY, float toX, float toY, long deltaTime);
	void resize(float width, float height);
	void setPosition(Real x, Real y, Real z);
	void layout(bool dir);

	int getCurrentIndex();
	int getCurrentItemIndex();
private:
	float mOffset;
	void _init();
};
#endif
