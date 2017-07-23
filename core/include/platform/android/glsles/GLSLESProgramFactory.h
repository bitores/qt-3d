#ifndef __GLSLESProgramFactory_H__
#define __GLSLESProgramFactory_H__

#include "rendersystem/HighLevelGpuProgramManager.h"
//#include "OgreGLSLESExtSupport.h"

/** Factory class for GLSL ES programs. */
class GLSLESProgramFactory : public HighLevelGpuProgramFactory
{
protected:
	/*static */String sLanguageName;
public:
	GLSLESProgramFactory(void);
	~GLSLESProgramFactory(void);
	/// Get the name of the language this factory creates programs for
	const String& getLanguage(void) const;
	/// Create an instance of GLSLESProgram
	HighLevelGpuProgram* create(ResourceManager* creator,
		const String& name, ResourceHandle handle,
		const String& group, bool isManual, ManualResourceLoader* loader);
	void destroy(HighLevelGpuProgram* prog);
//
//private:
//	static GLSLESLinkProgramManager* mLinkProgramManager;
//	static GLSLESProgramPipelineManager* mProgramPipelineManager;
};

#endif // __GLSLESProgramFactory_H__
