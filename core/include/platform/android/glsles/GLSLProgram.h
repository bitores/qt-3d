#ifndef __GLSLProgram_H__
#define __GLSLProgram_H__

#include "platform/RenderFunctionPrerequisites.h"

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include "hardwarebuffer/HardwareVertexBuffer.h"
#include "rendersystem/HighLevelGpuProgram.h"

/** Specialisation of HighLevelGpuProgram to provide support for OpenGL
	Shader Language (GLSL).
@remarks
	GLSL has no target assembler or entry point specification like DirectX 9 HLSL.
	Vertex and Fragment shaders only have one entry point called "main".
	When a shader is compiled, microcode is generated but can not be accessed by
	the application.
	GLSL also does not provide assembler low level output after compiling.  The GL Render
	system assumes that the Gpu program is a GL Gpu program so GLSLProgram will create a
	GLSLGpuProgram that is subclassed from GLGpuProgram for the low level implementation.
	The GLSLProgram class will create a shader object and compile the source but will
	not create a program object.  It's up to GLSLGpuProgram class to request a program object
	to link the shader object to.

@note
	GLSL supports multiple modular shader objects that can be attached to one program
	object to form a single shader.  This is supported through the "attach" material script
	command.  All the modules to be attached are listed on the same line as the attach command
	seperated by white space.

*/
class GLSLProgram : public HighLevelGpuProgram
{
public:
	/// Command object for attaching another GLSL Program
//	class CmdAttach : public ParamCommand
//	{
//	public:
//		String doGet(const void* target) const;
//		void doSet(void* target, const String& shaderNames);
//	};
	GLSLProgram(ResourceManager* creator,
		const String& name, ResourceHandle handle,
		const String& group, bool isManual, ManualResourceLoader* loader);
	~GLSLProgram();

	const GLuint getGLHandle() const { return mGLHandle; }
	void attachToProgramObject( const GLuint programObject );
	void detachFromProgramObject( const GLuint programObject );
//	String getAttachedShaderNames() const { return mAttachedShaderNames; }

	/// Overridden
	bool getPassTransformStates(void) const;
	bool getPassSurfaceAndLightStates(void) const;

	/** Attach another GLSL Shader to this one. */
	void attachChildShader(const String& name);

	/** Sets the preprocessor defines use to compile the program. */
	void setPreprocessorDefines(const String& defines) { mPreprocessorDefines = defines; }
	/** Sets the preprocessor defines use to compile the program. */
	const String& getPreprocessorDefines(void) const { return mPreprocessorDefines; }

	/// Overridden from GpuProgram
	const String& getLanguage(void) const;

	/** Returns the operation type that this geometry program expects to
		receive as input
	*/
	virtual RenderOperation::OperationType getInputOperationType(void) const
	{ return mInputOperationType; }
	/** Returns the operation type that this geometry program will emit
	*/
	virtual RenderOperation::OperationType getOutputOperationType(void) const
	{ return mOutputOperationType; }
	/** Returns the maximum number of vertices that this geometry program can
		output in a single run
	*/
	virtual int getMaxOutputVertices(void) const { return mMaxOutputVertices; }

	/** Sets the operation type that this geometry program expects to receive
	*/
	virtual void setInputOperationType(RenderOperation::OperationType operationType)
	{ mInputOperationType = operationType; }
	/** Set the operation type that this geometry program will emit
	*/
	virtual void setOutputOperationType(RenderOperation::OperationType operationType)
	{ mOutputOperationType = operationType; }
	/** Set the maximum number of vertices that a single run of this geometry program
		can emit.
	*/
	virtual void setMaxOutputVertices(int maxOutputVertices)
	{ mMaxOutputVertices = maxOutputVertices; }

	/// Command object for setting macro defines
	class CmdPreprocessorDefines : public ParamCommand
	{
	public:
		String doGet(const void* target) const;
		void doSet(void* target, const String& val);
	};
	/// Command object for setting the input operation type (geometry shader only)
	class  CmdInputOperationType : public ParamCommand
	{
	public:
		String doGet(const void* target) const;
		void doSet(void* target, const String& val);
	};
	/// Command object for setting the output operation type (geometry shader only)
	class  CmdOutputOperationType : public ParamCommand
	{
	public:
		String doGet(const void* target) const;
		void doSet(void* target, const String& val);
	};
	/// Command object for setting the maximum output vertices (geometry shader only)
	class  CmdMaxOutputVertices : public ParamCommand
	{
	public:
		String doGet(const void* target) const;
		void doSet(void* target, const String& val);
	};

	/** Get the attribute index for a given semantic.
	@remarks
		This can be used to identify the attribute index to bind non-builtin
		attributes like tangent and binormal.
	*/
	virtual GLuint getAttributeIndex(VertexElementSemantic semantic, uint index);
	/** Test whether attribute index for a given semantic is valid.
	*/
	virtual bool isAttributeValid(VertexElementSemantic semantic, uint index);

	/** Get the fixed attribute bindings normally used by GL for a semantic. */
	static GLuint getFixedAttributeIndex(VertexElementSemantic semantic, uint index);

	const GpuNamedConstants& getConstantDefinitions() const;

    /// Execute the binding functions for this program
    void bindProgram(void);
    /// Execute the binding functions for this program
    void unbindProgram(void);

	/// compile source into shader object
	bool compile( const bool checkErrors = true);

    /// Get the assigned GL program id
    GLuint getProgramID(void) const { return mProgramID; }
protected:
	static CmdPreprocessorDefines msCmdPreprocessorDefines;
//	static CmdAttach msCmdAttach;
	static CmdInputOperationType msInputOperationTypeCmd;
	static CmdOutputOperationType msOutputOperationTypeCmd;
	static CmdMaxOutputVertices msMaxOutputVerticesCmd;
//	void checkForGLSLError(const String& ogreMethod, const String& errorTextPrefix, const GLuint obj, const bool forceInfoLog = false, const bool forceException = false);
	/** Internal load implementation, must be implemented by subclasses.
	*/
	void loadFromSource(void);
	/** Internal method for creating a dummy low-level program for this
	high-level program.	GLSL does not give access to the low level implementation of the
	shader so this method creates an object sub-classed from GLGpuProgram just to be
	compatible with	GLRenderSystem.
	*/
	/// Overridden from HighLevelGpuProgram
	void unloadImpl(void);

	GpuProgramParametersSharedPtr createParameters(void);
	/// Populate the passed parameters with name->index map
	void populateParameterNames(GpuProgramParametersSharedPtr params);
	/// Populate the passed parameters with name->index map, must be overridden
	void buildConstantDefinitions() const;

private:
	/// GL handle for shader object
	GLuint mGLHandle;
	/// flag indicating if shader object successfully compiled
	GLint mCompiled;

	GLuint mProgramID; // TODO liuzx

	/// Keep track of the number of vertex shaders created
	static GLuint mVertexShaderCount;
	/// Keep track of the number of fragment shaders created
	static GLuint mFragmentShaderCount;

	/// The input operation type for this (geometry) program
	RenderOperation::OperationType mInputOperationType;
	/// The output operation type for this (geometry) program
	RenderOperation::OperationType mOutputOperationType;
	/// The maximum amount of vertices that this (geometry) program can output
	int mMaxOutputVertices;
	/// attached Shader names
//	String mAttachedShaderNames;
	/// Preprocessor options
	String mPreprocessorDefines;
	/// container of attached programs
//	typedef vector< GLSLProgram* > GLSLProgramContainer;
//	typedef GLSLProgramContainer::iterator GLSLProgramContainerIterator;
//	GLSLProgramContainer mAttachedGLSLPrograms;
};

//typedef SharedPtr<GLSLProgram> GLSLProgramPtr;

#endif // __GLSLProgram_H__
