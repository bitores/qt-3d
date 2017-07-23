#ifndef __ISurfaceTouchListener_h__
#define __ISurfaceTouchListener_h__


class ISurfaceTouchListener
{
public:
    ISurfaceTouchListener() {}
    ~ISurfaceTouchListener() {}

	virtual bool onTouchEvent(int action, int id, float x, float y) = 0;
};
#endif /* __ISurfaceTouchListener_h__ */
