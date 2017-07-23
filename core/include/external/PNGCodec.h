#ifndef __PNGCodec_h__
#define __PNGCodec_h__
#include "asset/ImageCodec.h"

class PNGCodec : public ImageCodec
{
private:
	String mType;
public:
	PNGCodec();
	~PNGCodec();

    /// @copydoc Codec::decode
    DecodeResult decode(DataStreamPtr& input) const;

	virtual String getType() const;
};
#endif
