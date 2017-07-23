#ifndef __gl_prerequisites__h
#define __gl_prerequisites__h

#include "android/GLES2Prerequisites.h"

//#if defined(_WIN32)
//#include "platform/win/glut.h"
//#include "platform/win/glext.h"
//#elif _WIN64
//#include "platform/win/glut.h"
//#include "platform/win/glext.h"
//#elif _ANDROID
////#include <GLES/gl.h>
////#include <GLES/glext.h>
////
//#include <GLES2/gl2.h>
//#include <GLES2/gl2ext.h>
//
//#ifdef _DEBUG_GL_
//#include "platform/android/GLLogWrapper.h"
//#endif
//
//#define OGRE_NO_GLES3_SUPPORT 1
//#define OGRE_NO_ETC_CODEC 1
//
//#define ENABLE_GL_CHECK 1
//
//#ifdef ENABLE_GL_CHECK
//#include "utils/include/StringVector.h"
//#include "base/LogManager.h"
//#endif
//
//#if ENABLE_GL_CHECK
//#define OGRE_CHECK_GL_ERROR(glFunc) \
//{ \
//        glFunc; \
//        int e = glGetError(); \
//        if (e != 0) \
//        { \
//            const char * errorString = ""; \
//            switch(e) \
//            { \
//            case GL_INVALID_ENUM:       errorString = "GL_INVALID_ENUM";        break; \
//            case GL_INVALID_VALUE:      errorString = "GL_INVALID_VALUE";       break; \
//            case GL_INVALID_OPERATION:  errorString = "GL_INVALID_OPERATION";   break; \
//            case GL_OUT_OF_MEMORY:      errorString = "GL_OUT_OF_MEMORY";       break; \
//            default:                                                            break; \
//            } \
//            char msgBuf[4096]; \
//            StringVector tokens = StringUtil::split(#glFunc, "("); \
//            sprintf(msgBuf, "OpenGL error 0x%04X %s in %s at line %i for %s\n", e, errorString, __PRETTY_FUNCTION__, __LINE__, tokens[0].c_str()); \
//            LogManager::log(TAG_GL2, msgBuf); \
//        } \
//    }
//#else
//#   define OGRE_CHECK_GL_ERROR(glFunc) { glFunc; }
//#endif
//
//#endif

#endif
