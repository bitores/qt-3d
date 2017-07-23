#ifndef __HighLevelGpuProgramManager_H__
#define __HighLevelGpuProgramManager_H__

#include "utils/include/prerequisites.h"
#include "asset/ResourceManager.h"
#include "HighLevelGpuProgram.h"

/** \addtogroup Core
*  @{
*/
/** \addtogroup Resources
*  @{
*/
/** Interface definition for factories of HighLevelGpuProgram. */
class HighLevelGpuProgramFactory
{
public:
	HighLevelGpuProgramFactory() {}
	virtual ~HighLevelGpuProgramFactory();
	/// Get the name of the language this factory creates programs for
	virtual const String& getLanguage(void) const = 0;
	virtual HighLevelGpuProgram* create(ResourceManager* creator,
		const String& name, ResourceHandle handle,
		const String& group, bool isManual, ManualResourceLoader* loader) = 0;
	virtual void destroy(HighLevelGpuProgram* prog) = 0;
};

/** This ResourceManager manages high-level vertex and fragment programs.
@remarks
	High-level vertex and fragment programs can be used instead of assembler programs
	as managed by GpuProgramManager; however they typically result in a GpuProgram
	being created as a derivative of the high-level program. High-level programs are
	easier to write, and can often be API-independent, unlike assembler programs.
@par
	This class not only manages the programs themselves, it also manages the factory
	classes which allow the creation of high-level programs using a variety of high-level
	syntaxes. Plugins can be created which register themselves as high-level program
	factories and as such the engine can be extended to accept virtually any kind of
	program provided a plugin is written.
*/
class HighLevelGpuProgramManager : public ResourceManager
{
public:
//	typedef std::map<String, HighLevelGpuProgramFactory*> FactoryMap;
protected:
	/// Factories capable of creating HighLevelGpuProgram instances
//	FactoryMap mFactories;

//	/// Factory for dealing with programs for languages we can't create
//	HighLevelGpuProgramFactory* mNullFactory;
//	/// Factory for unified high-level programs
//	HighLevelGpuProgramFactory* mUnifiedFactory;
	HighLevelGpuProgramFactory* mGLSLESFactory;

	HighLevelGpuProgramFactory* getFactory(const String& language);

	/// @copydoc ResourceManager::createImpl
	Resource* createImpl(const String& name, ResourceHandle handle,
		const String& group, bool isManual, ManualResourceLoader* loader,
		const NameValuePairList* createParams);
public:
	HighLevelGpuProgramManager(Root* root);
	~HighLevelGpuProgramManager();
	/** Add a new factory object for high-level programs of a given language. */
	void addFactory(HighLevelGpuProgramFactory* factory);
	/** Remove a factory object for high-level programs of a given language. */
	void removeFactory(HighLevelGpuProgramFactory* factory);

	/** Returns whether a given high-level language is supported. */
	bool isLanguageSupported(const String& lang);

	/// Get a resource by name
	/// @see ResourceManager::getResourceByName
	HighLevelGpuProgramPtr getByName(const String& name, const String& groupName/* = ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME*/);

	/** Create a new, unloaded HighLevelGpuProgram.
	@par
		This method creates a new program of the type specified as the second and third parameters.
		You will have to call further methods on the returned program in order to
		define the program fully before you can load it.
	@param name The identifying name of the program
	@param groupName The name of the resource group which this program is
		to be a member of
	@param language Code of the language to use (e.g. "cg")
	@param gptype The type of program to create
	*/
	HighLevelGpuProgramPtr createProgram(
		const String& name, const String& groupName,
		const String& language, GpuProgramType gptype);
};
/** @} */
/** @} */
#endif
