#ifndef _GESTURE_EVENT_H_
#define _GESTURE_EVENT_H_
#include "utils/include/prerequisites.h"
#include "preinput.h"

#include "InputEvent.h"
//#include "IInputProcessor.h"

class GestureEvent:public InputEvent {
	
	/** The id. */
	int mId;

public:	
	/**
	 The Constant GESTURE_DETECTED.
	@deprecated use GESTURE_STARTED instead */
	static const int GESTURE_DETECTED 	= 0;
	
	/** The Constant GESTURE_STARTED. */
	static const int GESTURE_STARTED 	= 0;
	
	/** The Constant GESTURE_UPDATED. */
	static const int GESTURE_UPDATED 	= 1;
	
	/** The Constant GESTURE_ENDED. */
	static const int GESTURE_ENDED		= 2;
	
	
	/** The Constant GESTURE_CANCELED. 
	 * Used when the gesture/input processing is aborted.
	 * It is not guaranteed atm that GESTURE_ENDED will be called in the future.
	 * */
	static const int GESTURE_CANCELED	= 3;
	
	
	/** The Constant GESTURE_RESUMED. 
	 * Used when a gesture is resumed because it has the highest priority again for example.
	 * */
	static const int GESTURE_RESUMED		= 4;
	
	/**
	 * Instantiates a new gesture event.
	 * 
	 * @param source the source
	 * @param id the id
	 * @param targetComponent the target component
	 */
	GestureEvent(IInputProcessor *source, int id, GameObject *targetComponent):InputEvent((Object*)source, targetComponent, false){
		mId = id;
		setCurrentTarget(targetComponent); //test ..
	}

	IInputProcessor* getSource() {
		return (IInputProcessor*)mSource;
	}


	/**
	 * Gets the id.
	 * <br>Can be a value of:
	 * <ul>
	 * <li>GESTURE_DETECTED
	 * <li>GESTURE_UPDATED
	 * <li>GESTURE_ENDED
	 * </ul>
	 * 
	 * @return the id
	 */
	int getId() {
		return mId;
	}


	/**
	 * Sets the id.
	 * 
	 * @param id the new id
	 */
	void setId(int id) {
		mId = id;
	}


};


#endif /* _GESTURE_EVENT_H_ */
