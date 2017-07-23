#ifndef _ArchiveManager_H__
#define _ArchiveManager_H__

#include "utils/include/prerequisites.h"
#include "asset/ResourceManager.h"
//#include "base/HeaderPrefix.h"


/** \addtogroup Core
*  @{
*/
/** \addtogroup Resources
*  @{
*/
/** This class manages the available ArchiveFactory plugins.
*/
class ArchiveManager
{
protected:
	typedef map<String, ArchiveFactory*> ArchiveFactoryMap;
	/// Factories available to create archives, indexed by archive type (String identifier e.g. 'Zip')
	ArchiveFactoryMap mArchFactories;
	/// Currently loaded archives
	typedef map<String, Archive*> ArchiveMap;
	ArchiveMap mArchives;

public:
	/** Default constructor - should never get called by a client app.
	*/
	ArchiveManager();
	/** Default destructor.
	*/
	virtual ~ArchiveManager();

	/** Opens an archive for file reading.
		@remarks
			The archives are created using class factories within
			extension libraries.
		@param filename
			The filename that will be opened
		@param archiveType
			The type of archive that this is. For example: "Zip".
		@return
			If the function succeeds, a valid pointer to an Archive
			object is returned.
		@par
			If the function fails, an exception is thrown.
	*/
	Archive* load( const String& filename, const String& archiveType, bool readOnly);

	/** Unloads an archive.
	@remarks
		You must ensure that this archive is not being used before removing it.
	*/
	void unload(Archive* arch);
	/** Unloads an archive by name.
	@remarks
		You must ensure that this archive is not being used before removing it.
	*/
	void unload(const String& filename);
	typedef MapIterator<ArchiveMap> ArchiveMapIterator;
	/** Get an iterator over the Archives in this Manager. */
	ArchiveMapIterator getArchiveIterator(void);

	/** Adds a new ArchiveFactory to the list of available factories.
		@remarks
			Plugin developers who add new archive codecs need to call
			this after defining their ArchiveFactory subclass and
			Archive subclasses for their archive type.
	*/
	void addArchiveFactory(ArchiveFactory* factory);
};
/** @} */
/** @} */

//#include "base/HeaderSuffix.h"

#endif
