#ifndef __Runnable_h__
#define __Runnable_h__

#include "utils/include/SharedPtr.h"

class Runnable
{
public:
	virtual void run() = 0;
	virtual ~Runnable() {

	}
};

typedef SharedPtr<Runnable> RunnablePtr;

#endif
