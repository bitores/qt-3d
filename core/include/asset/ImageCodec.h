#ifndef _ImageCodec_H__
#define _ImageCodec_H__

#include "io/Codec.h"
#include "utils/include/PixelFormat.h"


/** \addtogroup Core
*  @{
*/
/** \addtogroup Image
*  @{
*/
/** Codec specialized in images.
	@remarks
		The users implementing subclasses of ImageCodec are required to return
		a valid pointer to a ImageData class from the decode(...) function.
*/
class ImageCodec : public Codec
{
public:
	virtual ~ImageCodec();
	/** Codec return class for images. Has information about the size and the
		pixel format of the image. */
	class ImageData : public Codec::CodecData
	{
	public:
		ImageData():
			height(0), width(0), depth(1), size(0),
			num_mipmaps(0), flags(0), format(PF_UNKNOWN)
		{
		}
		uint32 height;
		uint32 width;
		uint32 depth;
		size_t size;

		uint8 num_mipmaps;
		uint flags;

		PixelFormat format;

	public:
		String dataType() const
		{
			return "ImageData";
		}
	};

public:
	String getDataType() const
	{
		return "ImageData";
	}
};

/** @} */
/** @} */

#endif
