#ifndef __ThreadDefines_H__
#define __ThreadDefines_H__

#define OGRE_THREAD_PROVIDER 0

#define OGRE_AUTO_MUTEX_NAME mutex
#if OGRE_THREAD_PROVIDER == 0
	#include "ThreadDefinesNone.h"
#elif OGRE_THREAD_PROVIDER == 1
	#include "OgreThreadDefinesBoost.h"
#elif OGRE_THREAD_PROVIDER == 2
	#include "OgreThreadDefinesPoco.h"
#elif OGRE_THREAD_PROVIDER == 3
	#include "OgreThreadDefinesTBB.h"
#endif

#endif

