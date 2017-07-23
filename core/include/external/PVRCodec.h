#ifndef __PVRCodec_h__
#define __PVRCodec_h__
#include "asset/ImageCodec.h"
#include "utils/include/PixelFormat.h"
#include "OGLES2Tools.h"
class PVRCodec : public ImageCodec
{
private:
	String mType;
public:
	PVRCodec();
	~PVRCodec();
    /// @copydoc Codec::decode
    DecodeResult decode(DataStreamPtr& input) const;
	virtual String getType() const;

	unsigned char* getStream(DataStreamPtr& input) const;
	PixelFormat getPixFormatFromPVRHead(unsigned long long pvrFormat) const;
};

/*PVRTuint32 PVRTGetTextureDataSizeJCode( PVRTuint64 u64PixelFormat,PVRTuint32 u32MIPMapCount,
		PVRTuint32 u32Width, PVRTuint32 u32Height,PVRTuint32 u32Depth,PVRTuint32 u32NumFaces,PVRTuint32 u32NumSurfaces,
	PVRTint32 iMipLevel=PVRTEX_ALLMIPLEVELS, bool bAllSurfaces=true, bool bAllFaces=true);*/
#endif
