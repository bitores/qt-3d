#ifndef _ABSTRACT_GLOBAL_INPUT_PROCESSOR_H_
#define _ABSTRACT_GLOBAL_INPUT_PROCESSOR_H_
#include "utils/include/prerequisites.h"
#include "preinput.h"

#include "IInputProcessor.h"
#include "IInputSourceListener.h"
//#include "IInputEventListener.h"
//#include "InputEvent.h"

class AbstractGlobalInputProcessor:public IInputSourceListener, public IInputProcessor {

	/** if disabled. */
	bool disabled;
	
	std::vector<IInputEventListener*> mInputListeners;
	
	/**
	 * Instantiates a new abstract input processor.
	 */
public:
	AbstractGlobalInputProcessor() {
		disabled 	= false;
	} 

	
	
	/* (non-Javadoc)
	 * @see org.mt4j.input.inputSources.IinputSourceListener#processInputEvent(org.mt4j.input.test.MTInputEvent)
	 */
	bool processInputEvent(InputEvent &inputEvent){
		processInputEvtImpl(inputEvent);
		return true;
	}

	
	/**
	 * Process input evt implementation.
	 * 
	 * @param inputEvent the input event
	 */
	virtual void processInputEvtImpl(InputEvent &inputEvent) = 0;
	
	
	/**
	 * Checks if is disabled.
	 * 
	 * @return true, if is disabled
	 */
	bool isDisabled() {
		return disabled;
	}

	/**
	 * Sets the disabled.
	 * 
	 * @param disabled the new disabled
	 */
	void setDisabled(bool state) {
		disabled = state;
	}


	/**
	 * Adds the processor listener.
	 * 
	 * @param listener the listener
	 */
	void addProcessorListener(IInputEventListener *listener);
	
	/**
	 * Removes the processor listener.
	 * 
	 * @param listener the listener
	 */
	void removeProcessorListener(IInputEventListener *listener);
	
	/**
	 * Gets the processor listeners.
	 * 
	 * @return the processor listeners
	 */
//	public synchronized IMTInputEventListener[] getProcessorListeners(){
//		return inputListeners.toArray(new IMTInputEventListener[this.inputListeners.size()]);
//	}
	
	/**
	 * Fire gesture event.
	 *
	 * @param ie the ie
	 */
	void fireInputEvent(InputEvent &ie);
	
	////
	/**
	 * Gets the intersection point of a cursor and a specified component.
	 * Can return null if the cursor doesent intersect the component.
	 *
	 * @param app the app
	 * @param c the c
	 * @return the intersection
	 */
//	public Vector3D getIntersection(PApplet app, InputCursor c){
//		return GestureUtils.getIntersection(app, c.getTarget(), c);
//	}
	
	/**
	 * Gets the intersection point of a cursor and a specified component.
	 * Can return null if the cursor doesent intersect the component.
	 *
	 * @param app the app
	 * @param component the component
	 * @param c the c
	 * @return the intersection
	 */
//	public Vector3D getIntersection(PApplet app, IMTComponent3D component, InputCursor c){
//		return GestureUtils.getIntersection(app, component, c);
//	}
	
//	public Vector3D getPlaneIntersection(PApplet app, Vector3D planeNormal, Vector3D pointInPlane, InputCursor c){
//		return GestureUtils.getPlaneIntersection(app, planeNormal, pointInPlane, c);
//	}
	///////////
	

	
};

#endif /* _ABSTRACT_GLOBAL_INPUT_PROCESSOR_H_ */
