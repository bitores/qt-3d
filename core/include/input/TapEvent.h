#ifndef _TapEvent_h_
#define _TapEvent_h_
#include "utils/include/prerequisites.h"
#include "preinput.h"
#include "utils/include/Vector3.h"
#include "GestureEvent.h"

class TapEvent:public GestureEvent {
	
	/** The cursor. */
	InputCursor *cursor;
	
	/** The click point. */
	Vector3 clickPoint;
	
	/** The click id. */
	int clickID;
    
public:	
//	@Deprecated
	/** The Constant BUTTON_DOWN. */
	static const int BUTTON_DOWN = 3;
	
//	@Deprecated
	/** The Constant BUTTON_UP. */
	static const int BUTTON_UP	= 4;
	
//	@Deprecated
	/** The Constant BUTTON_CLICKED. */
	static const int BUTTON_CLICKED = 5;
	
//	@Deprecated
	/** The Constant BUTTON_DOUBLE_CLICKED. */
	static const int BUTTON_DOUBLE_CLICKED = 6;
	
	/** The Constant TAP_DOWN. */
	static const int TAP_DOWN = 3;
	
	/** The Constant TAP_UP. */
	static const int TAP_UP	= 4;
	
	/** The Constant TAPPED. */
	static const int TAPPED = 5;
	
	/** The Constant DOUBLE_TAPPED. */
	static const int DOUBLE_TAPPED = 6;
	

	/**
	 * Instantiates a new click event.
	 * 
	 * @param source the source
	 * @param id the id
	 * @param targetComponent the target component
	 * @param cursor the cursor
	 * @param clickPoint the click point
	 * @param clickID the click id
	 */
	TapEvent(IInputProcessor *source, int id, GameObject *targetComponent, InputCursor *cur, Vector3 Point, int ID)
	    :GestureEvent(source, id, targetComponent) {
		cursor = cur;
		clickPoint = Point;
		clickID = ID;
	}

	/**
	 * Gets the click point.
	 * 
	 * @return the click point
	 */
	Vector3 getLocationOnScreen() {
		return clickPoint;
	}

	/**
	 * Gets the cursor.
	 * 
	 * @return the cursor
	 */
	InputCursor* getCursor() {
		return cursor;
	}

	/**
	 * Gets the click id.
	 * 
	 * @return the click id
	 */
	int getTapID() {
		return clickID;
	}
	
	/**
	 * Checks if is tapped.
	 * 
	 * @return true, if is tapped
	 */
	bool isTapped(){
		return getTapID() == TAPPED;
	}
	
	/**
	 * Checks if is tap down.
	 * 
	 * @return true, if is tap down
	 */
	bool isTapDown(){
		return getTapID() == TAP_DOWN;
	}
	
	/**
	 * Checks if is tap canceled.
	 * 
	 * @return true, if is tap canceled
	 */
	bool isTapCanceled(){
		return getTapID() == TAP_UP;
	}
	
	/**
	 * Checks if is double tap.
	 * 
	 * @return true, if is double tap
	 */
	bool isDoubleTap(){
		return getTapID() == DOUBLE_TAPPED;
	}
	

};


#endif /* _TapEvent_h_ */
