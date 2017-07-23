#ifndef _INPUT_SOURCE_LISTENER_H_
#define _INPUT_SOURCE_LISTENER_H_
#include "utils/include/prerequisites.h"
#include "preinput.h"

//#include "InputEvent.h"

class  IInputSourceListener {
	
public:	
	/**
	 * Process input event.
	 * 
	 * @param inputEvent the input event
	 * 
	 * @return true, if successful
	 */
	virtual bool processInputEvent(InputEvent &inputEvent) { return false; }
	
	
//	/**
//	 * Process the input event.
//	 * 
//	 * @param inputEvent the input event
//	 */
//	public void processInputEvent(MTInputEvent inputEvent);
	
	virtual bool isDisabled() { return false; }
	
//	/**
//	 * Gets the listen event type.
//	 * 
//	 * @return the listen event type
//	 */
//	abstract public Class<? extends MTInputEvent> getListenEventType();
	
};

#endif /* _INPUT_SOURCE_LISTENER_H_ */
