#ifndef _AbstractInputSource_H_
#define _AbstractInputSource_H_

#include "utils/include/prerequisites.h"
#include "preinput.h"

//#include "IInputSourceListener.h"
//#include "InputEvent.h"
//#include "InputCursor.h"
/**
 * An abstract superclass for the abstraction of input sources.
 * Input source listener can listen to events from the inputsource.
 * 
 * @author Christopher Ruff
 */
class AbstractInputSource 
{

protected:
    Root *mRoot;
    
	/** The input listeners. */
	std::vector<IInputSourceListener*> mInputListeners;
	
	std::vector<IInputSourceListener*> mInputProcessorsToFireTo;

    HashMap<long, long> idToCursorID;
    HashMap<long, InputCursor*> ActiveCursorPool;

public:
	/**
	 * Instantiates a new abstract input source.
	 *
	 * @param mtApp the mt app
	 */
	AbstractInputSource(Root *root);
	
	/**
	 * Flushes the events.
	 * <p>NOTE: not threadsafe! Has to be called in the opengl thread if in opengl mode!
	 */
//	void fireEvents()
//	{
//        inputProcessorsToFireTo.clear();
//        for (IinputSourceListener listener : inputListeners){  
//            if (!listener.isDisabled()){
//                inputProcessorsToFireTo.add(listener);
//            }
//        }
//			
//        this.fireInputEvent(te);
//	}

#define ACTION_DOWN           0
#define ACTION_POINTER_DOWN   5
#define ACTION_UP             1
#define ACTION_POINTER_UP     6
#define ACTION_OUTSIDE        4
#define ACTION_CANCEL         3
#define ACTION_MOVE           2
    void processInputEvent(int action, int id, float x, float y);
	
	/**
	 * Fire input event.
	 * <br><b>Note:</b> This method should NOT be called directly.
	 * Use the <code>queueInputEvent</code> and flushEvents() methods instead!
	 * 
	 * @param inputEvt the input evt
	 */
	void fireInputEvent(InputEvent &inputEvt);
	
	
	/**
	 * Adds the input listener.
	 * @param listener the listener
	 */
	void addInputListener(IInputSourceListener *listener);
	
	
	/**
	 * Removes the input listener.
	 * @param listener the listener
	 */
	 void removeInputListener(IInputSourceListener *listener);
};

#endif /* _AbstractInputSource_H_ */

