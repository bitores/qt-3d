#ifndef __GLSLESExtSupport_H__
#define __GLSLESExtSupport_H__

#include "platform/RenderFunctionPrerequisites.h"

//
// OpenGL Shading Language ES entry points
//
namespace e3d
{

	// forward declarations
	class GLSLProgram;
//	class GLSLGpuProgram;
	class GLSLLinkProgram;
	class GLSLLinkProgramManager;
//	class GLSLESProgramPipelineManager;
	class GLSLESProgramFactory;

	/** If there is a message in GL info log then post it in the Ogre Log
	@param msg The info log message string is appended to this string
	@param obj The GL object that is used to retrieve the info log
	*/
	String logObjectInfo(const String& msg, const GLuint obj);


} // namespace Ogre

#endif // __GLSLESExtSupport_H__
