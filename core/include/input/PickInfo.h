#ifndef _PICK_INFO_H_
#define _PICK_INFO_H_
#include "utils/include/prerequisites.h"
#include "preinput.h"

#include "utils/include/Ray.h"

class PickInfo {  
	
	/** The screen x coordinate. */
	float screenXCoordinate;
	
	/** The screen y coordinate. */
	float screenYCoordinate;
	
	/** The original pick ray. */
	Ray originalPickRay;
    
public:

	/**
	 * Instantiates a new pick info. Used for the pick() method of
	 * the MTComponent class.
	 * This class is used to check what
	 * 
	 * @param screenXCoordinate the screen x coordinate
	 * @param screenYCoordinate the screen y coordinate
	 * @param originalPickRay the original pick ray
	 */
	PickInfo(float screenX, float screenY, Ray &PickRay) {
		screenXCoordinate = screenX;
		screenYCoordinate = screenY;
		originalPickRay = PickRay;
	}

	/**
	 * Gets the pick ray.
	 * 
	 * @return the pick ray
	 */
	Ray& getPickRay() {
		return originalPickRay;
	}

	/**
	 * Gets the screen x coordinate.
	 * 
	 * @return the screen x coordinate
	 */
	float getScreenXCoordinate() {
		return screenXCoordinate;
	}

	/**
	 * Gets the screen y coordinate.
	 * 
	 * @return the screen y coordinate
	 */
	float getScreenYCoordinate() {
		return screenYCoordinate;
	}
	
	

};



#endif /* _PICK_INFO_H_*/
