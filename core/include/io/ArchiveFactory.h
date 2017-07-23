#ifndef _ArchiveFactory_H__
#define _ArchiveFactory_H__

#include "base/FactoryObj.h"
#include "base/HeaderPrefix.h"


/** \addtogroup Core
*  @{
*/
/** \addtogroup Resources
*  @{
*/
/** Abstract factory class, archive codec plugins can register concrete
	subclasses of this.
	@remarks
		All access to 'archives' (collections of files, compressed or
		just folders, maybe even remote) is managed via the abstract
		Archive class. Plugins are expected to provide the
		implementation for the actual codec itself, but because a
		subclass of Archive has to be created for every archive, a
		factory class is required to create the appropriate subclass.
	@par
		So archive plugins create a subclass of Archive AND a subclass
		of ArchiveFactory which creates instances of the Archive
		subclass. See the 'Zip' and 'FileSystem' plugins for examples.
		Each Archive and ArchiveFactory subclass pair deal with a
		single archive type (identified by a string).
*/
class ArchiveFactory : public FactoryObj< Archive >
{
public:
	virtual ~ArchiveFactory() {}
	/** Creates a new object.
	@param name Name of the object to create
	@return
		An object created by the factory. The type of the object depends on
		the factory.
	*/
	virtual Archive* createInstance(const String& name, bool readOnly) = 0;

	virtual Archive* createInstance(const String& name) { return createInstance(name, true); }
};
/** @} */
/** @} */

#include "base/HeaderSuffix.h"

#endif
