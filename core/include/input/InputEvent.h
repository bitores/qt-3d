#ifndef _INPUT_EVENT_H_
#define _INPUT_EVENT_H_
#include "utils/include/prerequisites.h"
#include "preinput.h"

#include "Event.h"

/**
 * The Class MTInputEvent. The base class for all input events.
 * 
 * @author Christopher Ruff
 */
class IInputProcessor;
class InputEvent: public Event 
{
protected:
	/** The target component. */
	GameObject *mTarget;
    GameObject *mCurrentTarget;
    
    short mEventPhase;
	bool mPropatationStopped;
	bool mBubbles;
    int mEventType ; // is a gesture event ?
    

public:
	static const short CAPTURING_PHASE 	= 1; // The current event phase is the capturing phase.
	static const short AT_TARGET 		= 2; 		//  The event is currently being evaluated at the target EventTarget.
	static const short BUBBLING_PHASE 	= 3;//  The current event phase is the bubbling phase.

    static const int GESTURE_EVENT = 1;
    static const int CURSOR_EVENT = 2;
	
public:
	/**
	 * Instantiates a new mT input event.
	 * 
	 * @param source the source
	 */
	InputEvent(Object *source, int evtType) {
//        this(source, 0);
        mSource = source;
        mTarget = 0;
        mPropatationStopped = false;
		mBubbles = true; 
		mEventPhase = CAPTURING_PHASE; //default?
		mEventType = evtType;
	}
	
	InputEvent(Object *source, GameObject *target) {
//		this(source, target, true);
        mSource = source;
        mTarget = target;
        mPropatationStopped = false;
        mBubbles = true; 
        mEventPhase = CAPTURING_PHASE; //default?
	}
	
	/**
	 * Instantiates a new mT input event.
	 * 
	 * @param source the source
	 * @param target the target component
	 */
	InputEvent(Object *source, GameObject *target, bool bubbles) {
	    mSource = source;
        mTarget = target;
        mPropatationStopped = false;
        mBubbles = bubbles; 
        mEventPhase = CAPTURING_PHASE; //default?
	}

	/**
	 * Gets the target of this input event.
	 * <br><strong>NOTE:</strong> Not every event has a target component! To check this
	 * we can call <code>event.hasTarget()</code>.
	 * 
	 * @return the target component
	 * @deprecated use getTarget() instead
	 * @see #getTarget()
	 */
	GameObject* getTargetComponent() {
		return mTarget;
	}
	

	/**
	 * Gets the target of this input event.
	 * <br><strong>NOTE:</strong> Not every event has a target component! To check this
	 * we can call <code>event.hasTarget()</code>.
	 * 
	 * @return the target component
	 */
	GameObject* getTarget() {
		return mTarget;
	}

	/**
	 * Sets the target component of this input event. 
	 * <br>NOTE: This is supposed to be called internally by
	 * MT4j and not by users.
	 * 
	 * @param targetComponent the new target component
	 */
	void setTarget(GameObject *targetComponent) {
		mTarget = targetComponent;
	}
	
	/**
	 * Checks if this input event has a target component.
	 * 
	 * @return true, if successful
	 */
	bool hasTarget(){
		return mTarget != 0;
	}
	
	/**
	 * This method is invoked right before the event is fired.
	 * This can be used to do event specific actions if needed before firing.
	 * <br>NOTE: this is called internally and should not be called by users!
	 */
	virtual void onFired(){	}
	
	/**
     * The <code>setEventPhase</code> method is used by the DOM implementation 
     * to change the value of a <code>eventPhase</code> attribute on the 
     * <code>Event</code> interface.
     * @param phase Specifies the <code>eventPhase</code> attribute on the 
     *   <code>Event</code> interface.
     */
    void setEventPhase(short phase){
    	//TODO check if bubbles = true if someone wants to set the pase to BUBBLING_PHASE?
    	mEventPhase = phase;
    }
    
    short getEventPhase(){
    	return mEventPhase; 
    }
    
    
    void stopPropagation(){
    	mPropatationStopped = true;
    }
    
    bool isPropagationStopped(){
    	return mPropatationStopped;
    }
    
    bool getBubbles(){
    	return mBubbles;
    }
    

	/**
     * The <code>setCurrentTarget</code> method is used by the DOM 
     * implementation to change the value of a <code>currentTarget</code> 
     * attribute on the <code>Event</code> interface.
     * @param target Specifies the <code>currentTarget</code> attribute on 
     *   the <code>Event</code> interface.
     */
    void setCurrentTarget(GameObject *target){
    	mCurrentTarget = target;
    }
    
    GameObject* getCurrentTarget(){
    	return mCurrentTarget;
    }

    void setEventType(int evtType) {
        mEventType = evtType;
    }
	int getEventType() {
        return mEventType;
    }
};

#endif /* _INPUT_EVENT_H_ */

