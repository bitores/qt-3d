#ifndef __HighLevelGpuProgram_H__
#define __HighLevelGpuProgram_H__

#include "utils/include/prerequisites.h"
#include "GpuProgram.h"

/** \addtogroup Core
*  @{
*/
/** \addtogroup Resources
*  @{
*/
/** Abstract base class representing a high-level program (a vertex or
	fragment program).
@remarks
	High-level programs are vertex and fragment programs written in a high-level
	language such as Cg or HLSL, and as such do not require you to write assembler code
	like GpuProgram does. However, the high-level program does eventually
	get converted (compiled) into assembler and then eventually microcode which is
	what runs on the GPU. As well as the convenience, some high-level languages like Cg allow
	you to write a program which will operate under both Direct3D and OpenGL, something
	which you cannot do with just GpuProgram (which requires you to write 2 programs and
	use each in a Technique to provide cross-API compatibility). Ogre will be creating
	a GpuProgram for you based on the high-level program, which is compiled specifically
	for the API being used at the time, but this process is transparent.
@par
	You cannot create high-level programs direct - use HighLevelGpuProgramManager instead.
	Plugins can register new implementations of HighLevelGpuProgramFactory in order to add
	support for new languages without requiring changes to the core Ogre API. To allow
	custom parameters to be set, this class extends StringInterface - the application
	can query on the available custom parameters and get/set them without having to
	link specifically with it.
*/
class HighLevelGpuProgram : public GpuProgram
{
//protected:
//	/// Whether the high-level program (and it's parameter defs) is loaded
//	bool mHighLevelLoaded;
//	/// The underlying assembler program
//	GpuProgramPtr mAssemblerProgram;
//	/// Have we built the name->index parameter map yet?
//	mutable bool mConstantDefsBuilt;
//
//	/// Internal load high-level portion if not loaded
//	virtual void loadHighLevel(void);
//	/// Internal unload high-level portion if loaded
//	virtual void unloadHighLevel(void);
//	/** Internal load implementation, loads just the high-level portion, enough to
//		get parameters.
//	*/
//	virtual void loadHighLevelImpl(void);
//	/** Internal method for creating an appropriate low-level program from this
//	high-level program, must be implemented by subclasses. */
//	virtual void createLowLevelImpl(void) = 0;
//	/// Internal unload implementation, must be implemented by subclasses
//	virtual void unloadHighLevelImpl(void) = 0;
//	/// Populate the passed parameters with name->index map
//	virtual void populateParameterNames(GpuProgramParametersSharedPtr params);
//	/** Build the constant definition map, must be overridden.
//	@note The implementation must fill in the (inherited) mConstantDefs field at a minimum,
//		and if the program requires that parameters are bound using logical
//		parameter indexes then the mFloatLogicalToPhysical and mIntLogicalToPhysical
//		maps must also be populated.
//	*/
//	virtual void buildConstantDefinitions() const = 0;
//
//	/** @copydoc Resource::loadImpl */
//	void loadImpl();
//	/** @copydoc Resource::unloadImpl */
//	void unloadImpl();
public:
	/** Constructor, should be used only by factory classes. */
	HighLevelGpuProgram(ResourceManager* creator, const String& name, ResourceHandle handle,
		const String& group, bool isManual = false, ManualResourceLoader* loader = 0);
	~HighLevelGpuProgram();


//	/** Creates a new parameters object compatible with this program definition.
//	@remarks
//		Unlike low-level assembly programs, parameters objects are specific to the
//		program and therefore must be created from it rather than by the
//		HighLevelGpuProgramManager. This method creates a new instance of a parameters
//		object containing the definition of the parameters this program understands.
//	*/
//	GpuProgramParametersSharedPtr createParameters(void);
//	/** @copydoc GpuProgram::_getBindingDelegate */
//	GpuProgram* _getBindingDelegate(void) { return mAssemblerProgram.getPointer(); }
//
//	/** Get the full list of GpuConstantDefinition instances.
//	@note
//	Only available if this parameters object has named parameters.
//	*/
//	const GpuNamedConstants& getConstantDefinitions() const;
//
//	/// Override GpuProgram::getNamedConstants to ensure built
//	const GpuNamedConstants& getNamedConstants() const { return getConstantDefinitions(); }
//
//	virtual size_t calculateSize(void) const;
};
/** @} */
/** @} */

#endif
