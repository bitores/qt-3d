#ifndef _INPUT_PROCESSOR_H_
#define _INPUT_PROCESSOR_H_
#include "utils/include/prerequisites.h"
#include "preinput.h"

#include "base/Object.h"
//#include "InputEvent.h"


class  IInputProcessor:public Object {
public:
//	/**
//	 * Gets the motion locking priority.
//	 * 
//	 * @return the locking priority
//	 */
//	public int getLockPriority();
	
	
//	/**
//	 * Process input evt implementation.
//	 * 
//	 * @param inputEvent the input event
//	 */
//	abstract public void processInputEvtImpl(MTInputEvent inputEvent);
	
	/**
	 * Process input evt.
	 * 
	 * @param inputEvent the input event
	 */
	virtual bool processInputEvent(InputEvent &inputEvent) = 0;;
	
	
	/**
	 * Checks if is disabled.
	 * 
	 * @return true, if is disabled
	 */
	bool isDisabled();

	/**
	 * Sets the disabled.
	 * 
	 * @param disabled the new disabled
	 */
	void setDisabled(bool disabled);


};


#endif /* INPUT_PROCESSOR_H_ */
