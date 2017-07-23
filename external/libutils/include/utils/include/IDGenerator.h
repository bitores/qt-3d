#ifndef __IDGenerator_h__
#define __IDGenerator_h__

#include "platform.h"

#include "Singleton.h"

class IDGenerator// : public Singleton<IDGenerator>
{
public:
	uint32 _id;

	uint32 next () { return _id++; }

	IDGenerator();
	~IDGenerator();
//	static IDGenerator& getSingleton();
//	static IDGenerator* getSingletonPtr();
};

#endif
