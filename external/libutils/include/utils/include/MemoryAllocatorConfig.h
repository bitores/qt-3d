#ifndef __memoryallocatorconfig_h__
#define __memoryallocatorconfig_h__

#define OGRE_ALLOC_T(T, count) static_cast<T*>(malloc(sizeof(T)*(count)))

#endif