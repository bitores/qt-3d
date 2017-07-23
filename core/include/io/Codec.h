#ifndef _Codec_H__
#define _Codec_H__

#include "utils/include/prerequisites.h"
#include "utils/include/SharedPtr.h"
#include "utils/include/IteratorWrappers.h"
#include "utils/include/StringVector.h"
#include "DataStream.h"

/** \addtogroup Core
*  @{
*/
/** \addtogroup General
*  @{
*/

/** Abstract class that defines a 'codec'.
	@remarks
		A codec class works like a two-way filter for data - data entered on
		one end (the decode end) gets processed and transformed into easily
		usable data while data passed the other way around codes it back.
	@par
		The codec concept is a pretty generic one - you can easily understand
		how it can be used for images, sounds, archives, even compressed data.
*/
class Codec
{
protected:

public:
	class CodecData
	{
	public:
		virtual ~CodecData() {}

		/** Returns the type of the data.
		*/
		virtual String dataType() const { return "CodecData"; }
	};
	typedef SharedPtr<CodecData> CodecDataPtr;

public:
	virtual ~Codec();

//	/** Gets the codec that can handle the given 'magic' identifier.
//	@param magicNumberPtr Pointer to a stream of bytes which should identify the file.
//		Note that this may be more than needed - each codec may be looking for
//		a different size magic number.
//	@param maxbytes The number of bytes passed
//	*/
//	Codec* getCodec(char *magicNumberPtr, size_t maxbytes);

//	/** Codes the data in the input stream and saves the result in the output
//		stream.
//	*/
//	virtual DataStreamPtr encode(MemoryDataStreamPtr& input, CodecDataPtr& pData) const = 0;
//	/** Codes the data in the input chunk and saves the result in the output
//		filename provided. Provided for efficiency since coding to memory is
//		progressive therefore memory required is unknown leading to reallocations.
//	@param input The input data
//	@param outFileName The filename to write to
//	@param pData Extra information to be passed to the codec (codec type specific)
//	*/
//	virtual void encodeToFile(MemoryDataStreamPtr& input, const String& outFileName, CodecDataPtr& pData) const = 0;

	/// Result of a decoding; both a decoded data stream and CodecData metadata
	typedef std::pair<MemoryDataStreamPtr, CodecDataPtr> DecodeResult;
	/** Codes the data from the input chunk into the output chunk.
		@param input Stream containing the encoded data
	*/
	virtual DecodeResult decode(DataStreamPtr& input) const = 0;

	/** Returns the type of the codec as a String
	*/
	virtual String getType() const = 0;

	/** Returns the type of the data that supported by this codec as a String
	*/
	virtual String getDataType() const = 0;

//	/** Returns whether a magic number header matches this codec.
//	@param magicNumberPtr Pointer to a stream of bytes which should identify the file.
//		Note that this may be more than needed - each codec may be looking for
//		a different size magic number.
//	@param maxbytes The number of bytes passed
//	*/
//	virtual bool magicNumberMatch(const char *magicNumberPtr, size_t maxbytes) const
//	{ return !magicNumberToFileExt(magicNumberPtr, maxbytes).empty(); }
//	/** Maps a magic number header to a file extension, if this codec recognises it.
//	@param magicNumberPtr Pointer to a stream of bytes which should identify the file.
//		Note that this may be more than needed - each codec may be looking for
//		a different size magic number.
//	@param maxbytes The number of bytes passed
//	@return A blank string if the magic number was unknown, or a file extension.
//	*/
//	virtual String magicNumberToFileExt(const char *magicNumberPtr, size_t maxbytes) const = 0;
};

class CodecManager
{
private:
	typedef map< String, Codec* > CodecList;
	/** A map that contains all the registered codecs.
	*/
	CodecList msMapCodecs;

	typedef ConstMapIterator<CodecList> CodecIterator;

public:
	/** Registers a new codec in the database.
	*/
	void registerCodec( Codec *pCodec );

	/** Return whether a codec is registered already.
	*/
	bool isCodecRegistered( const String& codecType );

	/** Unregisters a codec from the database.
	*/
	void unregisterCodec( Codec *pCodec );

	/** Gets the iterator for the registered codecs. */
	CodecIterator getCodecIterator(void) {
		return CodecIterator(msMapCodecs.begin(), msMapCodecs.end());
	}
	/** Gets the file extension list for the registered codecs. */
	StringVector getExtensions(void);

	/** Gets the codec registered for the passed in file extension. */
	Codec* getCodec(const String& extension);
};
/** @} */
/** @} */

#endif
