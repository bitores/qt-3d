#ifndef __IClickListener_h__
#define __IClickListener_h__

class Object;

class IClickListener
{
public:
	virtual void click(Object* sender) = 0;
};
#endif
