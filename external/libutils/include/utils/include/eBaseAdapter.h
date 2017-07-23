#ifndef __eBaseAdapter_h__
#define __eBaseAdapter_h__

#include "SharedPtr.h"

class eBaseAdapter
{
public:
	eBaseAdapter();
	virtual ~eBaseAdapter();
	virtual int getSize() = 0;
	virtual int getItem(int position) = 0;
	virtual GameObject* getUI(int position) = 0;
	virtual bool isHit(float x, float y) = 0;
};

typedef SharedPtr<eBaseAdapter> eBaseAdapterPtr;
#endif
