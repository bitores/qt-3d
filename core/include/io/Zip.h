#ifndef __Zip_H__
#define __Zip_H__

#include "utils/include/prerequisites.h"
#include "Archive.h"
#include "ArchiveFactory.h"
#if OGRE_THREAD_SUPPORT
#include "Threading/OgreThreadHeaders.h"
#endif

// Forward declaration for zziplib to avoid header file dependency.
typedef struct zzip_dir	ZZIP_DIR;
typedef struct zzip_file	ZZIP_FILE;
typedef union _zzip_plugin_io zzip_plugin_io_handlers;

/** \addtogroup Core
*  @{
*/
/** \addtogroup Resources
*  @{
*/
/** Specialisation of the Archive class to allow reading of files from a zip
	format source archive.
@remarks
	This archive format supports all archives compressed in the standard
	zip format, including iD pk3 files.
*/
class ZipArchive : public Archive
{
protected:
	/// Handle to root zip file
	ZZIP_DIR* mZzipDir;
	/// Handle any errors from zzip
	void checkZzipError(int zzipError, const String& operation) const;
	/// File list (since zziplib seems to only allow scanning of dir tree once)
	/// FileInfoList mFileList;
	/// A pointer to file io alternative implementation
	zzip_plugin_io_handlers* mPluginIo;

	OGRE_AUTO_MUTEX;
public:
	ZipArchive(const String& name, const String& archType, zzip_plugin_io_handlers* pluginIo = NULL);
	~ZipArchive();
	/// @copydoc Archive::isCaseSensitive
	bool isCaseSensitive(void) const { return false; }

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
//	FileInfoListPtr findFileInfo(const String& pattern, bool recursive = true, bool dirs = false) const;
//
//	/// @copydoc Archive::exists
//	bool exists(const String& filename);
//
//	/// @copydoc Archive::getModifiedTime
//	time_t getModifiedTime(const String& filename);
};

/** Specialisation of ArchiveFactory for Zip files. */
class ZipArchiveFactory : public ArchiveFactory
{
public:
	virtual ~ZipArchiveFactory() {}
	/// @copydoc FactoryObj::getType
	const String& getType(void) const;
	/// @copydoc FactoryObj::createInstance
	Archive *createInstance( const String& name, bool readOnly )
	{
		if(!readOnly)
			return NULL;

		return new ZipArchive(name, "Zip");
	}
	/// @copydoc FactoryObj::destroyInstance
	void destroyInstance( Archive* ptr) { delete ptr; }
};

///** Specialisation of ZipArchiveFactory for embedded Zip files. */
//class EmbeddedZipArchiveFactory : public ZipArchiveFactory
//{
//protected:
//	/// A static pointer to file io alternative implementation for the embedded files
//	static zzip_plugin_io_handlers* mPluginIo;
//public:
//	EmbeddedZipArchiveFactory();
//	virtual ~EmbeddedZipArchiveFactory();
//	/// @copydoc FactoryObj::getType
//	const String& getType(void) const;
//	/// @copydoc FactoryObj::createInstance
//	Archive *createInstance( const String& name, bool readOnly )
//	{
//		ZipArchive * resZipArchive = new ZipArchive(name, "EmbeddedZip", mPluginIo);
//		return resZipArchive;
//	}
//
//	/** a function type to decrypt embedded zip file
//	@param pos pos in file
//	@param buf current buffer to decrypt
//	@param len - length of buffer
//	@return success
//	*/
//	typedef bool (*DecryptEmbeddedZipFileFunc)(size_t pos, void* buf, size_t len);
//
//	/// Add an embedded file to the embedded file list
//	static void addEmbbeddedFile(const String& name, const uint8 * fileData,
//					size_t fileSize, DecryptEmbeddedZipFileFunc decryptFunc);
//
//	/// Remove an embedded file to the embedded file list
//	static void removeEmbbeddedFile(const String& name);
//
//};

/** Specialisation of DataStream to handle streaming data from zip archives. */
class ZipDataStream : public DataStream
{
protected:
	ZZIP_FILE* mZzipFile;
	/// We need caching because sometimes serializers step back in data stream and zziplib behaves slow
	StaticCache<2 * OGRE_STREAM_TEMP_SIZE> mCache;
public:
	/// Unnamed constructor
	ZipDataStream(ZZIP_FILE* zzipFile, size_t uncompressedSize);
	/// Constructor for creating named streams
	ZipDataStream(const String& name, ZZIP_FILE* zzipFile, size_t uncompressedSize);
	~ZipDataStream();
	/// @copydoc DataStream::read
	size_t read(void* buf, size_t count);
	/// @copydoc DataStream::write
	size_t write(void* buf, size_t count);
	/// @copydoc DataStream::skip
	void skip(long count);
	/// @copydoc DataStream::seek
	void seek( size_t pos );
	/// @copydoc DataStream::seek
	size_t tell(void) const;
	/// @copydoc DataStream::eof
	bool eof(void) const;
	/// @copydoc DataStream::close
	void close(void);
};

/** @} */
/** @} */
#endif
