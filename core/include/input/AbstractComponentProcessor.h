#ifndef _ABSTRACT_COMPONENT_PROCESSOR_H_
#define _ABSTRACT_COMPONENT_PROCESSOR_H_
#include "utils/include/prerequisites.h"
#include "preinput.h"

#include "IInputEventListener.h"
#include "IInputProcessor.h"
//#include "IGestureEventListener.h"

class AbstractComponentProcessor:public IInputEventListener, public IInputProcessor//,  Comparable<AbstractComponentProcessor> {
{
	
	/** if disabled. */
	bool disabled;

	/** The input listeners. */
	std::list<IGestureEventListener*> mInputListeners;

	/** The debug. */
	bool debug;
	
	bool stopPropagation;

    bool bubbledEventsEnabled;

	
public:
	/**
	 * Instantiates a new abstract component input processor.
	 */
	AbstractComponentProcessor() {
//	    this(false);
		disabled = false;
		debug = false;
		stopPropagation = false;
		bubbledEventsEnabled = false;
	}

	/**
	 * Instantiates a new abstract component processor.
	 *
	 * @param stopPropagation indicates whether to stop event bubbling
	 */
	AbstractComponentProcessor(bool _stopPropagation){
		disabled = false;
		debug = false;
		stopPropagation = _stopPropagation;
		bubbledEventsEnabled = false;
	}
    void init(bool _stopPropagation)
    {
        stopPropagation = _stopPropagation;
    }

	/* (non-Javadoc)
	 * @see org.mt4j.input.IMTInputEventListener#processInputEvent(org.mt4j.input.inputData.MTInputEvent)
	 */
	bool processInputEvent(InputEvent &inEvt);
	
	
	/**
	 * Pre process. Called before {@link #processInputEvent(MTInputEvent)} is called.
	 *
	 * @param inEvt the in evt
	 */
	void preProcess(InputEvent &inEvt);
	
	
		//FIXME test
	
	bool isBubbledEventsEnabled() {
		return bubbledEventsEnabled;
	}
	void setBubbledEventsEnabled(bool enableForBubbledEvents) {
		bubbledEventsEnabled = enableForBubbledEvents;
	}
	////
	
protected:
    /**
	 * Process input evt implementation.
	 * 
	 * @param inputEvent the input event
	 */
	virtual void processInputEvtImpl(InputEvent &inputEvent) = 0;
	
	virtual void preProcessImpl(InputEvent &inputEvent) = 0;
	
	
public:	
	/**
	 * Checks if this input processor is interested in the specified
	 * MTInputEvent instance.
	 * If we want to create custom input processors we override this method
	 * and return true only for the kind of events we want to recieve.
	 * 
	 * @param inputEvt the input evt
	 * 
	 * @return true, if is interested in
	 */
	virtual bool isInterestedIn(InputEvent &inputEvt) { return false; }
	
	
	/**
	 * Gets the name.
	 * 
	 * @return the name
	 */
	virtual String getName() { return "unnamed"; }
	
	
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
//	public synchronized void addGestureListener(IGestureEventListener listener){
    void addGestureListener(IGestureEventListener *listener){
//		if (!inputListeners.contains(listener)){
//			inputListeners.add(listener);
//		}
        for(std::list<IGestureEventListener*>::iterator it = mInputListeners.begin();
            it != mInputListeners.end(); it ++) {
            if(*it == listener)
                return; // already added
        }
        mInputListeners.push_back(listener);
	}
	
	/**
	 * Removes the processor listener.
	 * 
	 * @param listener the listener
	 */
//	public synchronized void removeGestureListener(IGestureEventListener listener){
    void removeGestureListener(IGestureEventListener *listener){
//		if (inputListeners.contains(listener)){
//			inputListeners.remove(listener);
//		}
        for(std::list<IGestureEventListener*>::iterator it = mInputListeners.begin();
            it != mInputListeners.end(); it ++) {
            if(*it == listener) {
                mInputListeners.erase(it);
                break;
            }
        }
	}
	
	/**
	 * Gets the processor listeners.
	 * 
	 * @return the processor listeners
	 */
//	public synchronized IGestureEventListener[] getGestureListeners(){
//		return inputListeners.toArray(new IGestureEventListener[this.inputListeners.size()]);
//	}

protected:
	/**
	 * Fire gesture event.
	 * 
	 * @param ge the ge
	 */
	void fireGestureEvent(GestureEvent &ge);

public:
	/**
	 * Sets the debug.
	 * 
	 * @param debug the new debug
	 */
	void setDebug(bool dbg) {
		debug = dbg;
	}
	
	
	
//	int compareTo(AbstractComponentProcessor o) {
//		return -1;
//	}
//    bool compare_nocase (const std::string& first, const std::string& second)
//    {
//      unsigned int i=0;
//      while ( (i<first.length()) && (i<second.length()) )
//      {
//        if (tolower(first[i])<tolower(second[i])) return true;
//        else if (tolower(first[i])>tolower(second[i])) return false;
//        ++i;
//      }
//      return ( first.length() < second.length() );
//    }

	
	bool isStopPropagation() {
		return stopPropagation;
	}

	void setStopPropagation(bool stoppropagation) {
		stopPropagation = stoppropagation;
	}
};


#endif
