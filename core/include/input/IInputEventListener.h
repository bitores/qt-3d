#ifndef _INPUT_EVENT_LISTENER_H_
#define _INPUT_EVENT_LISTENER_H_
#include "utils/include/prerequisites.h"
#include "preinput.h"

//#include "InputEvent.h"

class IInputEventListener {

public:
    IInputEventListener() {};
    ~IInputEventListener() {};
	/**
	 * Process input event.
	 * 
	 * @param inEvt the in evt
	 * 
	 * @return true, if successful
	 */
	virtual bool processInputEvent(InputEvent &inEvt) = 0;
	

//	/**
//	 * Process input event.
//	 * 
//	 * @param inEvt the in evt
//	 */
//	public void processInputEvent(MTInputEvent inEvt);

};

#endif /* _INPUT_EVENT_LISTENER_H_ */
