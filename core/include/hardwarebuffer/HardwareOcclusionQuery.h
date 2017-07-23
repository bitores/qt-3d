#ifndef _HardwareOcclusionQuery__
#define _HardwareOcclusionQuery__

// Precompiler options
#include "utils/include/prerequisites.h"


/** \addtogroup Core
*  @{
*/
/** \addtogroup RenderSystem
*  @{
*/
/**
  * This is a abstract class that that provides the interface for the query class for 
  * hardware occlusion.
  *
  * @author Lee Sandberg
  * Updated on 13/8/2005 by Tuan Kuranes email: tuan.kuranes@free.fr
  */
class HardwareOcclusionQuery/* : public RenderSysAlloc*/
{
//----------------------------------------------------------------------
// Public methods
//--
public:
	/**
	  * Object public member functions
	  */

	/**
	  * Default object constructor
	  * 
	  */
	HardwareOcclusionQuery();

	/**
	  * Object destructor
	  */
	virtual ~HardwareOcclusionQuery();

	/**
	  * Starts the hardware occlusion query
	  * @remarks	Simple usage: Create one or more OcclusionQuery object one per outstanding query or one per tested object 
	  *				OcclusionQuery* mOcclusionQuery;
	  *				createOcclusionQuery( &mOcclusionQuery );
	  *				In the rendering loop:
	  *				Draw all occluders
	  *				mOcclusionQuery->startOcclusionQuery();
	  *				Draw the polygons to be tested
	  *				mOcclusionQuery->endOcclusionQuery();
	  *
	  *				Results must be pulled using:
	  *				UINT	mNumberOfPixelsVisable;
	  *				pullOcclusionQuery( &mNumberOfPixelsVisable );
	  *			
	  */
	virtual void beginOcclusionQuery() = 0;

	/**
	  * Ends the hardware occlusion test
	  */
	virtual void endOcclusionQuery() = 0;

	/**
      * Pulls the hardware occlusion query.
	  * @note Waits until the query result is available; use isStillOutstanding
	  *		if just want to test if the result is available.
      * @retval NumOfFragments will get the resulting number of fragments.
      * @return True if success or false if not.
      */
	virtual bool pullOcclusionQuery(unsigned int* NumOfFragments) = 0;

	/**
	  * Let's you get the last pixel count with out doing the hardware occlusion test
	  * @return The last fragment count from the last test.
	  * Remarks This function won't give you new values, just the old value.
	  */
	unsigned int getLastQuerysPixelcount() const { return mPixelCount; }

	/**
	  * Lets you know when query is done, or still be processed by the Hardware
	  * @return true if query isn't finished.
	  */
	 virtual bool isStillOutstanding(void) = 0; 


    //----------------------------------------------------------------------
    // protected members
    //--
    protected :
        /// Number of visible pixels determined by last query
        unsigned int mPixelCount;
        /// Has the query returned a result yet?
		bool		 mIsQueryResultStillOutstanding;
};

/** @} */
/** @} */
#endif

