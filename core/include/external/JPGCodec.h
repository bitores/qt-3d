#ifndef __JPGCodec_h__
#define __JPGCodec_h__
#include "asset/ImageCodec.h"

class JPGCodec : public ImageCodec
{
private:
	String mType;
public:
	JPGCodec();
	~JPGCodec();

    /// @copydoc Codec::decode
    DecodeResult decode(DataStreamPtr& input) const;

	virtual String getType() const;
};
#endif
