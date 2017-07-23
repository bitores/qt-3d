#ifndef __FileSystem_H__
#define __FileSystem_H__

#include "Archive.h"
#include "ArchiveFactory.h"
//#include "base/HeaderPrefix.h"


/** \addtogroup Core
*  @{
*/
/** \addtogroup Resources
*  @{
*/
/** Specialisation of the Archive class to allow reading of files from
	filesystem folders / directories.
*/
class FileSystemArchive : public Archive
{
protected:
	/** Utility method to retrieve all files in a directory matching pattern.
	@param pattern
		File pattern.
	@param recursive
		Whether to cascade down directories.
	@param dirs
		Set to @c true if you want the directories to be listed instead of files.
	@param simpleList
		Populated if retrieving a simple list.
	@param detailList
		Populated if retrieving a detailed list.
	*/
//	void findFiles(const String& pattern, bool recursive, bool dirs,
//		StringVector* simpleList, FileInfoList* detailList) const;

	OGRE_AUTO_MUTEX;
public:
	FileSystemArchive(const String& name, const String& archType, bool readOnly );
	~FileSystemArchive();

	/// @copydoc Archive::isCaseSensitive
	bool isCaseSensitive(void) const;

	/// @copydoc Archive::load
	void load();
	/// @copydoc Archive::unload
	void unload();

	/// @copydoc Archive::open
	DataStreamPtr openImpl(const String& filename, bool readOnly = true) const;

//	/// @copydoc Archive::create
//	DataStreamPtr create(const String& filename) const;
//
//	/// @copydoc Archive::remove
//	void remove(const String& filename) const;
//
//	/// @copydoc Archive::list
//	StringVectorPtr list(bool recursive = true, bool dirs = false);
//
//	/// @copydoc Archive::listFileInfo
//	FileInfoListPtr listFileInfo(bool recursive = true, bool dirs = false);
//
//	/// @copydoc Archive::find
//	StringVectorPtr find(const String& pattern, bool recursive = true,
//		bool dirs = false);
//
//	/// @copydoc Archive::findFileInfo
//	FileInfoListPtr findFileInfo(const String& pattern, bool recursive = true,
//		bool dirs = false) const;
//
//	/// @copydoc Archive::exists
//	bool exists(const String& filename);
//
//	/// @copydoc Archive::getModifiedTime
//	time_t getModifiedTime(const String& filename);

	/// Set whether filesystem enumeration will include hidden files or not.
	/// This should be called prior to declaring and/or initializing filesystem
	/// resource locations. The default is true (ignore hidden files).
	static void setIgnoreHidden(bool ignore)
	{
		msIgnoreHidden = ignore;
	}

	/// Get whether hidden files are ignored during filesystem enumeration.
	static bool getIgnoreHidden()
	{
		return msIgnoreHidden;
	}

	static bool msIgnoreHidden;
};

/** Specialisation of ArchiveFactory for FileSystem files. */
class FileSystemArchiveFactory : public ArchiveFactory
{
public:
	virtual ~FileSystemArchiveFactory() {}
	/// @copydoc FactoryObj::getType
	const String& getType(void) const;
	/// @copydoc FactoryObj::createInstance
	Archive *createInstance( const String& name, bool readOnly )
	{
		return new FileSystemArchive(name, "FileSystem", readOnly);
	}
	/// @copydoc FactoryObj::destroyInstance
	void destroyInstance(Archive* ptr) { delete ptr; }
};

/** @} */
/** @} */

//#include "base/HeaderSuffix.h"

#endif // __FileSystem_H__
