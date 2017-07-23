#ifndef __GLSLLinkProgram_H__
#define __GLSLLinkProgram_H__

#include "platform/RenderFunctionPrerequisites.h"
#include "GLSLProgram.h"
#include "hardwarebuffer/HardwareVertexBuffer.h"

/// structure used to keep track of named uniforms in the linked program object
struct GLUniformReference
{
	/// GL location handle
	GLint  mLocation;
	/// Which type of program params will this value come from?
	GpuProgramType mSourceProgType;
	/// The constant definition it relates to
	const GpuConstantDefinition* mConstantDef;
};

typedef vector<GLUniformReference> GLUniformReferenceList;
typedef GLUniformReferenceList::iterator GLUniformReferenceIterator;

/** C++ encapsulation of GLSL Program Object

*/

class GLSLLinkProgram
{
private:
	GLSLLinkProgramManager* mGLSLLinkProgramManager;
	/// container of uniform references that are active in the program object
	GLUniformReferenceList mGLUniformReferences;

	/// Linked vertex program
	GLSLProgram* mVertexProgram;
	/// Linked fragment program
	GLSLProgram* mFragmentProgram;

	/// flag to indicate that uniform references have already been built
	bool		mUniformRefsBuilt;
	/// GL handle for the program object
	GLuint		mGLHandle;
	/// flag indicating that the program object has been successfully linked
	GLint		mLinked;
	/// flag indicating skeletal animation is being performed
	bool mSkeletalAnimation;

	/// build uniform references from active named uniforms
	void buildGLUniformReferences(void);
	/// extract attributes
	void extractAttributes(void);

//	typedef set<GLuint> AttributeSet;
//	// Custom attribute bindings
//	AttributeSet mValidAttributes;
	typedef map<VertexElementSemantic, GLint> AttributeMap;
	AttributeMap mValidAttributes;

	/// Name / attribute list
	struct CustomAttribute
	{
		String name;
		GLint attrib;
		VertexElementSemantic ves;
		CustomAttribute(const String& _name, VertexElementSemantic _ves, GLint _attrib)
			:name(_name), ves(_ves), attrib(_attrib) {}
	};

	static CustomAttribute msCustomAttributes[];
	String getCombinedName();
public:
	/// constructor should only be used by GLSLLinkProgramManager
	GLSLLinkProgram(GLSLLinkProgramManager* glslLinkProgramManager, GLSLProgram* vertexProgram, GLSLProgram* fragmentProgram);
	~GLSLLinkProgram(void);

	/** Makes a program object active by making sure it is linked and then putting it in use.

	*/
	void activate(void);
	void _useProgram(void);
	void compileAndLink();
	/** updates program object uniforms using data from GpuProgramParamters.
	normally called by GLSLGpuProgram::bindParameters() just before rendering occurs.
	*/
	void updateUniforms(GpuProgramParametersSharedPtr params, uint16 mask, GpuProgramType fromProgType);
	/** updates program object uniforms using data from pass iteration GpuProgramParamters.
	normally called by GLSLGpuProgram::bindMultiPassParameters() just before multi pass rendering occurs.
	*/
	void updatePassIterationUniforms(GpuProgramParametersSharedPtr params);
	/// get the GL Handle for the program object
	GLuint getGLHandle(void) const { return mGLHandle; }
	/** Sets whether the linked program includes the required instructions
	to perform skeletal animation.
	@remarks
	If this is set to true, OGRE will not blend the geometry according to
	skeletal animation, it will expect the vertex program to do it.
	*/
	void setSkeletalAnimationIncluded(bool included)
	{ mSkeletalAnimation = included; }

	/** Returns whether the linked program includes the required instructions
		to perform skeletal animation.
	@remarks
		If this returns true, OGRE will not blend the geometry according to
		skeletal animation, it will expect the vertex program to do it.
	*/
	bool isSkeletalAnimationIncluded(void) const { return mSkeletalAnimation; }

	/// Get the index of a non-standard attribute bound in the linked code
	GLuint getAttributeIndex(VertexElementSemantic semantic, uint index);
	/// Is a non-standard attribute bound in the linked code?
	bool isAttributeValid(VertexElementSemantic semantic, uint index);

};

#endif // __GLSLLinkProgram_H__
