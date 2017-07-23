#ifndef __asm_math_h__
#define __asm_math_h__

#include "prerequisites.h"

float asm_rsq( float r )
{
// #if  OGRE_COMPILER == OGRE_COMPILER_MSVC &&  OGRE_ARCH_TYPE == OGRE_ARCHITECTURE_32
// 
//     __asm {
//         fld1 // r0 = 1.f
//         fld r // r1 = r0, r0 = r
//         fsqrt // r0 = sqrtf( r0 )
//         fdiv // r0 = r1 / r0
//     } // returns r0
// 
// #else

	return 1.f / sqrt( r );

// #endif
}

__inline float asm_rand()
{
	return float(rand());
}

__inline float asm_rand_max()
{
	return float(RAND_MAX);
}


#endif