#ifndef _ScaleEvent_h_
#define _ScaleEvent_h_
#include "utils/include/prerequisites.h"
#include "preinput.h"
#include "utils/include/Vector3.h"
#include "GestureEvent.h"

class ScaleEvent:public GestureEvent{
	
	/** The scale factor x. */
	float scaleFactorX;
	
	/** The scale factor y. */
	float scaleFactorY;
	
	/** The scale factor z. */
	float scaleFactorZ;
	
	/** The first  cursor. */
	InputCursor *firstCursor;
	
	/** The second  cursor. */
	InputCursor *secondCursor;
	
	/** The scaling point. */
	Vector3 scalingPoint;
    Vector3 localscalingPoint;
	
public:	
    ScaleEvent():GestureEvent(0, 0, 0) {
        firstCursor = 0;
		secondCursor = 0;
		scaleFactorX = 1;
		scaleFactorY = 1;
		scaleFactorZ = 1;
    }
	/**
	 * Instantiates a new scale event.
	 * 
	 * @param source the source
	 * @param id the id
	 * @param scalingObject the scaling object
	 * @param firstCursor the first  cursor
	 * @param secondCursor the second  cursor
	 * @param scaleFactorX the scale factor x
	 * @param scaleFactorY the scale factor y
	 * @param scaleFactorZ the scale factor z
	 * @param scalingPoint the scaling point
	 */
	ScaleEvent(IInputProcessor *source, int id, GameObject *scalingObject, InputCursor *_firstCursor, InputCursor *_secondCursor,
	    float _scaleFactorX, float _scaleFactorY, float _scaleFactorZ, Vector3 _scalingPoint, Vector3 _localscalingPoint):GestureEvent(source, id, scalingObject) {
		
		firstCursor = _firstCursor;
		secondCursor = _secondCursor;
		scaleFactorX = _scaleFactorX;
		scaleFactorY = _scaleFactorY;
		scaleFactorZ = _scaleFactorZ;
		scalingPoint = _scalingPoint;
        localscalingPoint= _localscalingPoint;
	}

	/**
	 * Gets the scale factor x.
	 * 
	 * @return the scale factor x
	 */
	float getScaleFactorX() {
		return scaleFactorX;
	}

	/**
	 * Gets the scale factor y.
	 * 
	 * @return the scale factor y
	 */
	float getScaleFactorY() {
		return scaleFactorY;
	}

	/**
	 * Gets the scale factor z.
	 * 
	 * @return the scale factor z
	 */
	float getScaleFactorZ() {
		return scaleFactorZ;
	}

	/**
	 * Gets the scaling point.
	 * 
	 * @return the scaling point
	 */
	Vector3 getScalingPoint() {
		return scalingPoint;
	}

    Vector3 getLocalScalingPoint() {
        return localscalingPoint;
    }

	/**
	 * Gets the first  cursor.
	 * 
	 * @return the first  cursor
	 */
	InputCursor* getFirstCursor() {
		return firstCursor;
	}

	/**
	 * Gets the second  cursor.
	 * 
	 * @return the second  cursor
	 */
	InputCursor* getSecondCursor() {
		return secondCursor;
	}
	
	/* (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
//	public String toString(){
//		return super.toString() + " - " + " Scaleobject:" + this.getTarget().getName() + " X-Scalefactor: " + scaleFactorX + " Y-Scalefactor:" + scaleFactorY + " Z-Scalefactor:" + scaleFactorZ + " Scalingpoint:" + scalingPoint;
//	}

	/**
	 * Sets the first  cursor.
	 * 
	 * @param firstCursor the new first  cursor
	 */
	void setFirstCursor(InputCursor *_firstCursor) {
		firstCursor = _firstCursor;
	}

	/**
	 * Sets the scale factor x.
	 * 
	 * @param scaleFactorX the new scale factor x
	 */
	void setScaleFactorX(float _scaleFactorX) {
		scaleFactorX = _scaleFactorX;
	}

	/**
	 * Sets the scale factor y.
	 * 
	 * @param scaleFactorY the new scale factor y
	 */
	void setScaleFactorY(float _scaleFactorY) {
		scaleFactorY = _scaleFactorY;
	}

	/**
	 * Sets the scale factor z.
	 * 
	 * @param scaleFactorZ the new scale factor z
	 */
	void setScaleFactorZ(float _scaleFactorZ) {
		scaleFactorZ = _scaleFactorZ;
	}

	/**
	 * Sets the scaling point.
	 * 
	 * @param scalingPoint the new scaling point
	 */
	void setScalingPoint(Vector3 _scalingPoint) {
		scalingPoint = _scalingPoint;
	}

	/**
	 * Sets the second  cursor.
	 * 
	 * @param secondCursor the new second  cursor
	 */
	void setSecondCursor(InputCursor *_secondCursor) {
		secondCursor = _secondCursor;
	}
	
};



#endif /* _ScaleEvent_h_ */
