#ifndef _EVENT_H_
#define _EVENT_H_
#include "utils/include/prerequisites.h"
#include "preinput.h"
#include "base/Object.h"
#include "utils/include/Timer.h"
/**
 * The Class MTEvent. The base class for most events used in mt4j framework.
 * @author Christopher Ruff
 */
class Event 
{

protected:

	/** The source. */
	Object *mSource;

//    static Timer mTimer;
	/** The creation time stamp. */
	unsigned long timeStamp;
	
//	/** The consumed. */
//	boolean consumed;

public:
    Event() {};
	/**
	 * Instantiates a new mT event.
	 * 
	 * @param source the source
	 */
	Event(Object *source) {
//		consumed = false;
		mSource = source;
		timeStamp = Timer::currentTimeMillis();
	}

	/**
	 * Gets the source.
	 * 
	 * @return the source
	 */
	Object *getSource() {
		return mSource;
	}
	
	/**
	 * Gets the when.
	 * 
	 * @return the when
	 */
	unsigned long getTimeStamp(){
		return timeStamp;
	}

//	/**
//	 * Checks if is consumed.
//	 * 
//	 * @return true, if is consumed
//	 */
//	public boolean isConsumed() {
//		return consumed;
//	}
//
//	/**
//	 * Sets the consumed.
//	 * 
//	 * @param consumed the new consumed
//	 */
//	public void setConsumed(boolean consumed) {
//		this.consumed = consumed;
//	}

	
};

#endif /* _EVENT_H_ */