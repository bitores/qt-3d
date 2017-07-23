#ifndef __TGAParser_h__
#define __TGAParser_h__
//#include "parser/IAssetParser.h"

class Image;
class MemoryFile;

class TGAParser/* : public IAssetParser*/
{
private:
	typedef struct
	{
		unsigned char Header[12];							// TGA File Header
	} TGAHeader;

	typedef struct
	{
		unsigned char	header[6];								// First 6 Useful Bytes From The Header
		unsigned int	bytesPerPixel;							// Holds Number Of Bytes Per Pixel Used In The TGA File
		unsigned int	imageSize;								// Used To Store The Image Size When Setting Aside Ram
		unsigned int	temp;									// Temporary Variable
		unsigned int	type;	
		unsigned int	Height;									//Height of Image
		unsigned int	Width;									//Width ofImage
		unsigned int	Bpp;									// Bits Per Pixel
	} TGA;

	TGAHeader mTGAHeader;									// TGA header

	//unsigned char uTGAcompare[12];	// Uncompressed TGA Header = {0,0,2, 0,0,0,0,0,0,0,0,0}
	//unsigned char cTGAcompare[12];	// Compressed TGA Header = {0,0,10,0,0,0,0,0,0,0,0,0}

//	Image * LoadUncompressedTGA(MemoryFile *mIOServer);	// Load an Uncompressed file
//	Image * LoadCompressedTGA(MemoryFile *mIOServer);		// Load a Compressed file
//
//	IAsset* parseZipFile(const char* zipDir, const char* filePath);
//	IAsset* parseFile(const char* assetPath);
public:
	TGAParser();
	~TGAParser();
//	IAsset* parse(AssetInfo* pAssetInfo);
};
#endif
