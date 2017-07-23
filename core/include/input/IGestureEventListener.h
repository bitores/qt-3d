#ifndef _Gesture_Event_Listener_H_
#define _Gesture_Event_Listener_H_
#include "utils/include/prerequisites.h"
#include "preinput.h"

//#include "GestureEvent.h"

class IGestureEventListener 
{

public:	
    IGestureEventListener() {};
    ~IGestureEventListener() {};
	/**
	 * Process gesture event.
	 * 
	 * @param ge the ge
	 * @return TODO
	 * 
	 * @return true, if successful
	 */
	virtual bool processGestureEvent(GestureEvent &ge) = 0;

};


#endif /* _Gesture_Event_Listener_H_ */
