#ifndef __GLES2HARDWAREOCCLUSIONQUERY_H__
#define __GLES2HARDWAREOCCLUSIONQUERY_H__

#include "GLES2Prerequisites.h"
#include "hardwarebuffer/HardwareOcclusionQuery.h"
//#include "OgreGLES2ManagedResource.h"


// If you use multiple rendering passes you can test only the first pass and all other passes don't have to be rendered 
// if the first pass result has too few pixels visible.

// Be sure to render all occluder first and whats out so the RenderQue don't switch places on 
// the occluding objects and the tested objects because it thinks it's more effective..

class GLES2HardwareOcclusionQuery : public HardwareOcclusionQuery /*MANAGED_RESOURCE*/
{
//----------------------------------------------------------------------
// Public methods
//--
public:
	/**
	  * Default object constructor
	  * 
	  */
	GLES2HardwareOcclusionQuery();
	/**
	  * Object destructor
	  */
	~GLES2HardwareOcclusionQuery();

	//------------------------------------------------------------------
	// Occlusion query functions (see base class documentation for this)
	//--
	void beginOcclusionQuery();
	void endOcclusionQuery();
	bool pullOcclusionQuery( unsigned int* NumOfFragments); 
	bool isStillOutstanding(void);


//----------------------------------------------------------------------
// private members
//--
private:

    GLuint mQueryID;
    
    void createQuery();
    
    void destroyQuery();
    
#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
protected:
    
    /** See AndroidResource. */
    virtual void notifyOnContextLost();
    
    /** See AndroidResource. */
    virtual void notifyOnContextReset();
#endif
    
};

#endif 

