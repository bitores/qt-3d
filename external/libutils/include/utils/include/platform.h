#ifndef __platform_h__
#define __platform_h__

#define _un_export

/* Define the number of priority groups for the render system's render targets. */
#define E3D_NUM_RENDERTARGET_GROUPS 10
#define E3D_DEFAULT_RT_GROUP 4
#define E3D_REND_TO_TEX_RT_GROUP 2

#define OGRE_ENDIAN_LITTLE 1
#define OGRE_ENDIAN_BIG 2

#define OGRE_PLATFORM_WIN32 1
#define OGRE_PLATFORM_ANDROID 5

#define OGRE_PLATFORM OGRE_PLATFORM_WIN32

#define OGRE_COMPILER_MSVC 1

// Endian Settings
// check for BIG_ENDIAN config flag, set OGRE_ENDIAN correctly
//#define OGRE_CONFIG_BIG_ENDIAN

#ifdef OGRE_CONFIG_BIG_ENDIAN
#    define OGRE_ENDIAN OGRE_ENDIAN_BIG
#else
#    define OGRE_ENDIAN OGRE_ENDIAN_LITTLE
#endif

#define OGRE_UNICODE_SUPPORT 1

/* Finds the compiler type and version.
*/
//#if (defined( __WIN32__ ) || defined( _WIN32 )) && defined(__ANDROID__) // We are using NVTegra
//#   define OGRE_COMPILER OGRE_COMPILER_GNUC
//#   define OGRE_COMP_VER 470
//#elif defined( _MSC_VER )
//#   define OGRE_COMPILER OGRE_COMPILER_MSVC
//#   define OGRE_COMP_VER _MSC_VER
//#elif defined( __GNUC__ )
//#   define OGRE_COMPILER OGRE_COMPILER_GNUC
//#   define OGRE_COMP_VER (((__GNUC__)*100) + \
//	(__GNUC_MINOR__*10) + \
//	__GNUC_PATCHLEVEL__)
//#else
//#   pragma error "No known compiler. Abort! Abort!"
//#endif
#define OGRE_COMPILER OGRE_COMPILER_MSVC
#define OGRE_COMP_VER _MSC_VER


// Integer formats of fixed bit width
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef int int32;
typedef short int16;
typedef char int8;
typedef unsigned long long uint64;
typedef long long int64;

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

#endif
