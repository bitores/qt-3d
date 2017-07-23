/******************************************************************************

 @File         PVRTModelPOD.h

 @Title        PVRTModelPOD

 @Version   

 @Copyright    Copyright (c) Imagination Technologies Limited.

 @Platform     ANSI compatible

 @Description  Code to load POD files - models exported from MAX.

******************************************************************************/
#ifndef _PVRTMODELPOD_H_
#define _PVRTMODELPOD_H_

//#include "PVRTVector.h"
//#include "PVRTError.h"
#include"PVRTError.h"
#include"PVRTGlobal.h"
#include"PVRTFixedPoint.h"
//#include "PVRTVertex.h"
//#include "PVRTBoneBatch.h"
//#include "PVRTResourceFile.h"

/****************************************************************************
** Defines
****************************************************************************/
#define PVRTMODELPOD_VERSION	("AB.POD.2.0") /*!< POD file version string */

// PVRTMODELPOD Scene Flags
#define PVRTMODELPODSF_FIXED	(0x00000001)   /*!< PVRTMODELPOD Fixed-point 16.16 data (otherwise float) flag */

#define PVRTMODELPOD_TAG_MASK			(0x80000000)
#define PVRTMODELPOD_TAG_START			(0x00000000)
#define PVRTMODELPOD_TAG_END			(0x80000000)


//Define 
/****************************************************************************
** Enumerations
****************************************************************************/
/*!****************************************************************************
 @Struct      EPODLightType
 @Brief       Enum for the POD format light types
******************************************************************************/
enum EPODLightType
{
	ePODPoint=0,	 /*!< Point light */
	ePODDirectional, /*!< Directional light */
	ePODSpot,		 /*!< Spot light */
	eNumPODLightTypes
};

/*!****************************************************************************
 @Struct      EPODPrimitiveType
 @Brief       Enum for the POD format primitive types
******************************************************************************/
enum EPODPrimitiveType
{
	ePODTriangles=0, /*!< Triangles */
	eNumPODPrimitiveTypes
};

/*!****************************************************************************
 @Struct      EPODAnimationData
 @Brief       Enum for the POD format animation types
******************************************************************************/
enum EPODAnimationData
{
	ePODHasPositionAni	= 0x01,	/*!< Position animation */
	ePODHasRotationAni	= 0x02, /*!< Rotation animation */
	ePODHasScaleAni		= 0x04, /*!< Scale animation */
	ePODHasMatrixAni	= 0x08  /*!< Matrix animation */
};

/*!****************************************************************************
 @Struct      EPODMaterialFlags
 @Brief       Enum for the material flag options
******************************************************************************/
enum EPODMaterialFlag
{
	ePODEnableBlending	= 0x01	/*!< Enable blending for this material */
};

/*!****************************************************************************
 @Struct      EPODBlendFunc
 @Brief       Enum for the POD format blend functions
******************************************************************************/
enum EPODBlendFunc
{
	ePODBlendFunc_ZERO=0,
	ePODBlendFunc_ONE,
	ePODBlendFunc_BLEND_FACTOR,
	ePODBlendFunc_ONE_MINUS_BLEND_FACTOR,

	ePODBlendFunc_SRC_COLOR = 0x0300,
	ePODBlendFunc_ONE_MINUS_SRC_COLOR,
	ePODBlendFunc_SRC_ALPHA,
	ePODBlendFunc_ONE_MINUS_SRC_ALPHA,
	ePODBlendFunc_DST_ALPHA,
	ePODBlendFunc_ONE_MINUS_DST_ALPHA,
	ePODBlendFunc_DST_COLOR,
	ePODBlendFunc_ONE_MINUS_DST_COLOR,
	ePODBlendFunc_SRC_ALPHA_SATURATE,

	ePODBlendFunc_CONSTANT_COLOR = 0x8001,
	ePODBlendFunc_ONE_MINUS_CONSTANT_COLOR,
	ePODBlendFunc_CONSTANT_ALPHA,
	ePODBlendFunc_ONE_MINUS_CONSTANT_ALPHA
};

/*!****************************************************************************
 @Struct      EPODBlendOp
 @Brief       Enum for the POD format blend operation
******************************************************************************/
enum EPODBlendOp
{
	ePODBlendOp_ADD = 0x8006,
	ePODBlendOp_MIN,
	ePODBlendOp_MAX,
	ePODBlendOp_SUBTRACT = 0x800A,
	ePODBlendOp_REVERSE_SUBTRACT
};


/*!****************************************************************************
 @Struct      EPODFileName
 @Brief       Enum for the binary pod blocks
******************************************************************************/
enum EPODFileName
{
	ePODFileVersion				= 1000,
	ePODFileScene,
	ePODFileExpOpt,
	ePODFileHistory,
	ePODFileEndiannessMisMatch  = -402456576,

	ePODFileColourBackground	= 2000,
	ePODFileColourAmbient,
	ePODFileNumCamera,
	ePODFileNumLight,
	ePODFileNumMesh,
	ePODFileNumNode,
	ePODFileNumMeshNode,
	ePODFileNumTexture,
	ePODFileNumMaterial,
	ePODFileNumFrame,
	ePODFileCamera,		// Will come multiple times
	ePODFileLight,		// Will come multiple times
	ePODFileMesh,		// Will come multiple times
	ePODFileNode,		// Will come multiple times
	ePODFileTexture,	// Will come multiple times
	ePODFileMaterial,	// Will come multiple times
	ePODFileFlags,
	ePODFileFPS,
	ePODFileUserData,

	ePODFileMatName				= 3000,
	ePODFileMatIdxTexDiffuse,
	ePODFileMatOpacity,
	ePODFileMatAmbient,
	ePODFileMatDiffuse,
	ePODFileMatSpecular,
	ePODFileMatShininess,
	ePODFileMatEffectFile,
	ePODFileMatEffectName,
	ePODFileMatIdxTexAmbient,
	ePODFileMatIdxTexSpecularColour,
	ePODFileMatIdxTexSpecularLevel,
	ePODFileMatIdxTexBump,
	ePODFileMatIdxTexEmissive,
	ePODFileMatIdxTexGlossiness,
	ePODFileMatIdxTexOpacity,
	ePODFileMatIdxTexReflection,
	ePODFileMatIdxTexRefraction,
	ePODFileMatBlendSrcRGB,
	ePODFileMatBlendSrcA,
	ePODFileMatBlendDstRGB,
	ePODFileMatBlendDstA,
	ePODFileMatBlendOpRGB,
	ePODFileMatBlendOpA,
	ePODFileMatBlendColour,
	ePODFileMatBlendFactor,
	ePODFileMatFlags,
	ePODFileMatUserData,

	ePODFileTexName				= 4000,

	ePODFileNodeIdx				= 5000,
	ePODFileNodeName,
	ePODFileNodeIdxMat,
	ePODFileNodeIdxParent,
	ePODFileNodePos,
	ePODFileNodeRot,
	ePODFileNodeScale,
	ePODFileNodeAnimPos,
	ePODFileNodeAnimRot,
	ePODFileNodeAnimScale,
	ePODFileNodeMatrix,
	ePODFileNodeAnimMatrix,
	ePODFileNodeAnimFlags,
	ePODFileNodeAnimPosIdx,
	ePODFileNodeAnimRotIdx,
	ePODFileNodeAnimScaleIdx,
	ePODFileNodeAnimMatrixIdx,
	ePODFileNodeUserData,

	ePODFileMeshNumVtx			= 6000,
	ePODFileMeshNumFaces,
	ePODFileMeshNumUVW,
	ePODFileMeshFaces,
	ePODFileMeshStripLength,
	ePODFileMeshNumStrips,
	ePODFileMeshVtx,
	ePODFileMeshNor,
	ePODFileMeshTan,
	ePODFileMeshBin,
	ePODFileMeshUVW,			// Will come multiple times
	ePODFileMeshVtxCol,
	ePODFileMeshBoneIdx,
	ePODFileMeshBoneWeight,
	ePODFileMeshInterleaved,
	ePODFileMeshBoneBatches,
	ePODFileMeshBoneBatchBoneCnts,
	ePODFileMeshBoneBatchOffsets,
	ePODFileMeshBoneBatchBoneMax,
	ePODFileMeshBoneBatchCnt,
	ePODFileMeshUnpackMatrix,
	ePODFileMeshName,
	ePODFileMeshBounds,

	ePODFileLightIdxTgt			= 7000,
	ePODFileLightColour,
	ePODFileLightType,
	ePODFileLightConstantAttenuation,
	ePODFileLightLinearAttenuation,
	ePODFileLightQuadraticAttenuation,
	ePODFileLightFalloffAngle,
	ePODFileLightFalloffExponent,

	ePODFileCamIdxTgt			= 8000,
	ePODFileCamFOV,
	ePODFileCamFar,
	ePODFileCamNear,
	ePODFileCamAnimFOV,

	ePODFileDataType			= 9000,
	ePODFileN,
	ePODFileStride,
	ePODFileData,

	ePODFileKeyFrame      =10000,
    ePODFileKeyFrameNum,
	ePODFileKeyFrameName,
	ePODFileKeyFrameData
};

/****************************************************************************
** Structures
****************************************************************************/
/*!****************************************************************************
 @Class      CPODData
 @Brief      A class for representing POD data
******************************************************************************/
class CPODData {
public:
	/*!***************************************************************************
	@Function			Reset
	@Description		Resets the POD Data to NULL
	*****************************************************************************/
	void Reset();

public:
	EPVRTDataType	eType;		/*!< Type of data stored */
	PVRTuint32		n;			/*!< Number of values per vertex */
	PVRTuint32		nStride;	/*!< Distance in bytes from one array entry to the next */
	PVRTuint8		*pData;		/*!< Actual data (array of values); if mesh is interleaved, this is an OFFSET from pInterleaved */
};

/*!****************************************************************************
 @Struct      SPODCamera
 @Brief       Struct for storing POD camera data
******************************************************************************/

/*!***************************************************************************
@Class CPVRTModelPOD
@Brief A class for loading and storing data from POD files/headers
*****************************************************************************/
template<class T> struct check32BitType;
template<> struct check32BitType<unsigned int> {};
template<> struct check32BitType<int> {};
template<> struct check32BitType<float> {};
template<class T> struct check16BitType;
template<> struct check16BitType<unsigned short> {};
template<> struct check16BitType<short> {};

class CSource
{
public:
	/*!***************************************************************************
	@Function			~CSource
	@Description		Destructor
	*****************************************************************************/
	virtual ~CSource() {};
	virtual bool Read(void* lpBuffer, const unsigned int dwNumberOfBytesToRead) = 0;
	virtual bool Skip(const unsigned int nBytes) = 0;

	template <typename T>
	bool Read(T &n)
	{
		return Read(&n, sizeof(T));
	}

	template <typename T>
	bool Read32(T &n)
	{
		unsigned char ub[4];

		if(Read(&ub, 4))
		{
			unsigned int *pn = (unsigned int*) &n;
			*pn = (unsigned int) ((ub[3] << 24) | (ub[2] << 16) | (ub[1] << 8) | ub[0]);
			return true;
		}

		return false;
	}

	template <typename T>
	bool Read16(T &n)
	{
		unsigned char ub[2];

		if(Read(&ub, 2))
		{
			unsigned short *pn = (unsigned short*) &n;
			*pn = (unsigned short) ((ub[1] << 8) | ub[0]);
			return true;
		}

		return false;
	}

	bool ReadMarker(unsigned int &nName, unsigned int &nLen);

	template <typename T>
	bool ReadAfterAlloc(T* &lpBuffer, const unsigned int dwNumberOfBytesToRead)
	{
		if(!SafeAlloc(lpBuffer, dwNumberOfBytesToRead))
			return false;
		return Read(lpBuffer, dwNumberOfBytesToRead);
	}

	template <typename T>
	bool ReadAfterAlloc32(T* &lpBuffer, const unsigned int dwNumberOfBytesToRead)
	{
		check32BitType<T>();
		if(!SafeAlloc(lpBuffer, dwNumberOfBytesToRead/4))
			return false;
		return ReadArray32((unsigned int*) lpBuffer, dwNumberOfBytesToRead / 4);
	}

	template <typename T>
	bool ReadArray32(T* pn, const unsigned int i32Size)
	{
		check32BitType<T>();
		bool bRet = true;

		for(unsigned int i = 0; i < i32Size; ++i)
			bRet &= Read32(pn[i]);

		return bRet;
	}

	template <typename T>
	bool ReadAfterAlloc16(T* &lpBuffer, const unsigned int dwNumberOfBytesToRead)
	{
		check16BitType<T>();
		if(!SafeAlloc(lpBuffer, dwNumberOfBytesToRead/2 ))
			return false;
		return ReadArray16((unsigned short*) lpBuffer, dwNumberOfBytesToRead / 2);
	}

	bool ReadArray16(unsigned short* pn, unsigned int i32Size)
	{
		bool bRet = true;

		for(unsigned int i = 0; i < i32Size; ++i)
			bRet &= Read16(pn[i]);

		return bRet;
	}
};

class CSourceStream : public CSource
{
protected:
	const char* m_pFile;
	size_t bufferSize;
	size_t m_BytesReadCount;
	size_t fileSize;
	const char* m_pData;

public:
	/*!***************************************************************************
	@Function			CSourceStream
	@Description		Constructor
	*****************************************************************************/
	CSourceStream() : m_pFile(0),bufferSize(0), m_BytesReadCount(0) ,fileSize(0) ,m_pData(0) {}

	/*!***************************************************************************
	@Function			~CSourceStream

	@Description		Destructor
	*****************************************************************************/
	virtual ~CSourceStream();

	bool Init(const char * const pData, const size_t i32Size,bool isOpen=true);

	virtual bool Read(void* lpBuffer, const unsigned int dwNumberOfBytesToRead);
	virtual bool Skip(const unsigned int nBytes);
};

/****************************************************************************
** Declarations
****************************************************************************/

/*!***************************************************************************
 @Function		PVRTModelPODDataTypeSize
 @Input			type		Type to get the size of
 @Return		Size of the data element
 @Description	Returns the size of each data element.
*****************************************************************************/
PVRTuint32 PVRTModelPODDataTypeSize(const EPVRTDataType type);

/*!***************************************************************************
 @Function		PVRTModelPODDataTypeComponentCount
 @Input			type		Type to get the number of components from
 @Return		number of components in the data element
 @Description	Returns the number of components in a data element.
*****************************************************************************/
PVRTuint32 PVRTModelPODDataTypeComponentCount(const EPVRTDataType type);

/*!***************************************************************************
 @Function		PVRTModelPODDataStride
 @Input			data		Data elements
 @Return		Size of the vector elements
 @Description	Returns the size of the vector of data elements.
*****************************************************************************/
PVRTuint32 PVRTModelPODDataStride(const CPODData &data);

/*!***************************************************************************
 @Function			PVRTModelPODGetAnimArraySize
 @Input				pAnimDataIdx
 @Input				ui32Frames
 @Input				ui32Components
 @Return			Size of the animation array
 @Description		Calculates the size of an animation array
*****************************************************************************/
PVRTuint32 PVRTModelPODGetAnimArraySize(PVRTuint32 *pAnimDataIdx, PVRTuint32 ui32Frames, PVRTuint32 ui32Components);

template <typename T>
bool SafeAlloc(T* &ptr, size_t cnt)
{
	_ASSERT(!ptr);
	if(cnt)
	{
		ptr = (T*)calloc(cnt, sizeof(T));
		_ASSERT(ptr);
		if(!ptr)
			return false;
	}
	return true;
}

bool ReadIndexData(
	unsigned short *	indexPtr,
	CSource				&src,
	const unsigned int	nSpec);

#endif /* _PVRTMODELPOD_H_ */

/*****************************************************************************
 End of file (PVRTModelPOD.h)
*****************************************************************************/

