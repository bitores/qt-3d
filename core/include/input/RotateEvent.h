#ifndef _RotateEvent_h_
#define _RotateEvent_h_
#include "utils/include/prerequisites.h"
#include "preinput.h"
#include "utils/include/Vector3.h"
#include "utils/include/mathlib.h"
#include "GestureEvent.h"



/**
 * The Class RotateEvent.
 * @author Christopher Ruff
 */
class RotateEvent:public GestureEvent {
	
	/** The first finger motion. */
	InputCursor *firstFingerMotion;
	
	/** The second finger motion. */
	InputCursor *secondFingerMotion;
	
	/** The rotation point. */
	Vector3 rotationPoint;
	
	/** The translation vector. */
	Vector3 translationVector;
	
	/** The rotation degrees. */
//	float rotationDegrees;
    Radian rotationRadian;
	
public:
    RotateEvent():GestureEvent(0, 0, 0) {
        firstFingerMotion = 0;
		secondFingerMotion = 0;
		rotationRadian = 0.0f;
    }
	/**
	 * Instantiates a new rotate event.
	 * 
	 * @param source the source
	 * @param id the id
	 * @param targetComponent the target component
	 * @param firstFingerMotion the first finger motion
	 * @param secondFingerMotion the second finger motion
	 * @param translationVector the translation vector
	 * @param rotationPoint the rotation point
	 * @param rotationDegrees the rotation degrees
	 */
	RotateEvent(IInputProcessor *source, int id, GameObject *targetComponent, 
    	InputCursor *_firstFingerMotion, InputCursor *_secondFingerMotion, 
    	Vector3 _translationVector, Vector3 _rotationPoint, float _rotationRadian):GestureEvent(source, id, targetComponent) {
		firstFingerMotion = _firstFingerMotion;
		secondFingerMotion = _secondFingerMotion;
		translationVector = _translationVector;
		rotationPoint = _rotationPoint;
		rotationRadian = _rotationRadian;
	}

	/**
	 * Gets the first finger motion.
	 * 
	 * @return the first finger motion
	 */
	InputCursor* getFirstCursor() {
		return firstFingerMotion;
	}

	/**
	 * Gets the rotation point.
	 * 
	 * @return the rotation point
	 */
	Vector3 getRotationPoint() {
		return rotationPoint;
	}

	/**
	 * Gets the second finger motion.
	 * 
	 * @return the second finger motion
	 */
	InputCursor* getSecondCursor() {
		return secondFingerMotion;
	}

	/**
	 * Gets the translation vector.
	 * 
	 * @return the translation vector
	 */
	Vector3 getTranslationVector() {
		return translationVector;
	}

	/**
	 * Gets the rotation degrees.
	 * 
	 * @return the rotation degrees
	 */
//	float getRotationDegrees() {
//		return rotationDegrees;
//	}
    Radian getRotationRadian() {
        return rotationRadian;
	}

	/**
	 * Sets the first finger motion.
	 * 
	 * @param firstFingerMotion the new first finger motion
	 */
	void setFirstCursor(InputCursor *_firstFingerMotion) {
		firstFingerMotion = _firstFingerMotion;
	}

	/**
	 * Sets the rotation degrees.
	 * 
	 * @param rotationDegrees the new rotation degrees
	 */
//	void setRotationDegrees(float _rotationDegrees) {
//		rotationDegrees = _rotationDegrees;
//	}
    void setRotationRadian(Radian r) {
        rotationRadian = r;
	}

	/**
	 * Sets the rotation point.
	 * 
	 * @param rotationPoint the new rotation point
	 */
	void setRotationPoint(Vector3 _rotationPoint) {
		rotationPoint = _rotationPoint;
	}

	/**
	 * Sets the second finger motion.
	 * 
	 * @param secondFingerMotion the new second finger motion
	 */
	void setSecondCursor(InputCursor *_secondFingerMotion) {
		secondFingerMotion = _secondFingerMotion;
	}

	/**
	 * Sets the translation vector.
	 * 
	 * @param translationVector the new translation vector
	 */
	void setTranslationVector(Vector3 _translationVector) {
		translationVector = _translationVector;
	}
};


#endif /* _RotateEvent_h_ */

