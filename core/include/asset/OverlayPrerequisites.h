#ifndef __Ogre_Overlay_Prereq_H__
#define __Ogre_Overlay_Prereq_H__

#include "utils/include/prerequisites.h"

//namespace Ogre
//{
	// forward decls
	class Font;
	class FontManager;
	//class Overlay;
	class OverlayContainer;
	class OverlayElement;
	//class OverlayElementFactory;
	//class OverlayManager;

	typedef SharedPtr<Font> FontPtr;
//}
//
//#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WINRT
//#	if defined( OGRE_STATIC_LIB )
//#   	define _OgreOverlayExport
//#   else
//#   	if defined( OGRE_OVERLAY_EXPORTS )
//#       	define _OgreOverlayExport __declspec( dllexport )
//#   	else
//#           if defined( __MINGW32__ )
//#               define _OgreOverlayExport
//#           else
//#       	    define _OgreOverlayExport __declspec( dllimport )
//#           endif
//#   	endif
//#	endif
//#elif defined ( OGRE_GCC_VISIBILITY )
//#   define _OgreOverlayExport __attribute__ ((visibility("default")))
//#else
//#	define _OgreOverlayExport
//#endif
//


#endif 
