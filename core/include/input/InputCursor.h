#ifndef _INPUT_CURSOR_H_
#define _INPUT_CURSOR_H_
#include "utils/include/prerequisites.h"
#include "preinput.h"

#include "utils/include/Vector3.h"

template <class T> struct less_priority
{
    bool operator() (const T& x, const T& y) const 
    {return x->getLockPriority() < y->getLockPriority();}
};

typedef std::list<AbstractCursorInputEvt*> EventList;

class InputCursor{

	static const int EVENT_HISTORY_DEPTH = 99;
	
	/** The events. */
	EventList events;
	
//	/** The current id. */
//	static long currentID;
	
	/** The ID. */
	long ID;

    typedef HashMap<AbstractCursorProcessor*, float, less_priority<AbstractCursorProcessor*> > ProcessorToPriorityMap;
//	TreeMap<AbstractCursorProcessor, Float> lockingProcessorsToPriority;
    ProcessorToPriorityMap lockingProcessorsToPriority;
//	
//	TreeMap<AbstractCursorProcessor, Float> registeredProcessorsToPriority;
    ProcessorToPriorityMap registeredProcessorsToPriority;
	
public:
	
	/**
	 * Instantiates a new input cursor.
	 */
	InputCursor();

    ~InputCursor();

	
	/**
	 * Gets the priority by which this cursor is locked.
	 * 
	 * @return the current lock priority
	 */
	float getCurrentLockPriority();
	

	
	bool canLock(AbstractCursorProcessor *ia);
	
	
	/**
	 * Locks this cursor with the specified processor if the processors lock priority
	 * is higher or equal than the current lock priority of this cursor.
	 * 
	 * @param ia the AbstractCursorProcessor
	 * 
	 * @return true if sucessfully locked
	 */
	bool getLock(AbstractCursorProcessor *ia);
	
	bool isLockedBy(AbstractCursorProcessor *cp);
	
	//only do this when previous highest priority strictly < the new priority!
	void cursorLockedByHigherPriorityGesture(AbstractCursorProcessor *ia, float gesturePriority);
	
	
	/**
	 * Input processors should call this when new input has started to be
	 * able to use the cursor locking mechanisms.
	 * 
	 * @param ia the ia
	 */
	void registerForLocking(AbstractCursorProcessor *ia);
	
	/**
	 * Input processors should call this when input has ended.
	 * 
	 * @param ia the ia
	 */
	void unregisterForLocking(AbstractCursorProcessor *ia){
//		Set<AbstractCursorProcessor> keys = registeredProcessorsToPriority.keySet();
//		for (Iterator<AbstractCursorProcessor> iterator = keys.iterator(); iterator.hasNext();) {
//			AbstractCursorProcessor inputAnalyzer = iterator.next();
//			if (inputAnalyzer.equals(ia)){
//				iterator.remove();
//			}
//		}
        for(ProcessorToPriorityMap::iterator it = registeredProcessorsToPriority.begin();
            it != registeredProcessorsToPriority.end(); it ++) {
            if(it->first == ia) {
                registeredProcessorsToPriority.erase(it);
                break;
            }
        }
	}
	
	
	
	/**
	 * Unlocks this cursor from the specified processor.
	 * If the priority by which this cursor is locked changes by that, 
	 * the <code>cursorUnlocked</code> method is invoked on processors 
	 * with a lower priority who by that get a chance to lock this cursor again.
	 * 
	 * @param ia the AbstractCursorProcessor
	 */
	void unlock(AbstractCursorProcessor *ia);

	

	/**
	 * Adds the event.
	 * 
	 * @param te the te
	 */
	void addEvent(AbstractCursorInputEvt *te);

	
	/**
	 * Contains event.
	 * 
	 * @param te the te
	 * 
	 * @return true, if successful
	 */
	bool containsEvent(AbstractCursorInputEvt *te){
//		return this.events.contains(te);
        for(EventList::iterator it = events.begin(); it != events.end(); it ++) {
            if(*it == te) {
                return true;
            }
        }
        return false;
	}
	
private:
	/**
	 * Generate new id.
	 * 
	 * @return the long
	 */
//	synchronized private long generateNewID(){
    long generateNewID();
	
public:	
//	/**
//	 * Gets the events.
//	 * 
//	 * @return the events
//	 */
//	public MTConcretePositionEvt[] getEvents(){
//		return this.events.toArray(new MTConcretePositionEvt[this.events.size()]);
//	}
	
	/**
	 * Gets the events.
	 * 
	 * @return the events
	 */
	EventList getEvents(){
		return events;
	}
	
	
	/**
	 * Gets the events.
	 * 
	 * @param millisAgo the millis ago
	 * 
	 * @return the events
	 */
	EventList getEvents(int millisAgo);
	
	
	/**
	 * Gets the last event.
	 * 
	 * @return the last event
	 */
	AbstractCursorInputEvt* getCurrentEvent(){
		if(events.size() == 0){ 
			return 0;
		}else{
			return events.back();
		}
	}
	
	/**
	 * Gets the evt before last event.
	 * 
	 * @return the evt before last event
	 */
	AbstractCursorInputEvt* getPreviousEvent(){
		if(events.size() < 2){
			return 0;
		}else{
		    EventList::reverse_iterator rit = events.rbegin();
            rit ++;
            return (*rit);
		}
	}
	
	/**
	 * Gets the current events position x.
	 * 
	 * @return the current events position x
	 */
	float getCurrentEvtPosX();
	
	/**
	 * Gets the current events position y.
	 * 
	 * @return the current events position y
	 */
	float getCurrentEvtPosY();
	
	
	/**
	 * Gets the position.
	 * @return the position
	 */
	Vector3 getPosition();
	
	
	/**
	 * Gets the target component of this cursor. (The component the cursor started on) 
	 * or null if it has no target or the cursor has no input events yet.
	 *
	 * @return the target
	 */
	GameObject* getTarget();
	
	GameObject* getCurrentTarget();
	
	/**
	 * Gets the start position x.
	 * 
	 * @return the start position x
	 */
	float getStartPosX();
	
	/**
	 * Gets the start position y.
	 * 
	 * @return the start position y
	 */
	float getStartPosY();
	
	
	/**
	 * Gets the start position.
	 * @return the start position
	 */
	Vector3 getStartPosition();
	
	/**
	 * Gets the previous event of.
	 * 
	 * @param te the te
	 * 
	 * @return the previous event of
	 */
	AbstractCursorInputEvt* getPreviousEventOf(AbstractCursorInputEvt *te){
		EventList allEvents = getEvents();
		AbstractCursorInputEvt *returnEvent = 0;
		
//		for (int i = 0; i < allEvents.size(); i++) {
//			AbstractCursorInputEvt event = allEvents.get(i);
//			
//			if (event.equals(te) 
//				&& (allEvents.size() >= 2) 
//				&& i-1 > 0
//				&& allEvents.get(i-1) != 0) 
//			{
//				returnEvent = allEvents.get(i-1);
//			}
//		}
		int i = 0;
        for(EventList::iterator it = events.begin(); it != events.end(); it ++, i ++) {
            if((*it == te) && (events.size() >= 2) && (i -1 > 0)) {
                returnEvent = (*it);
            }
        }
		return returnEvent;
	}
	
	
	/**
	 * Gets the first event.
	 * 
	 * @return the first event
	 */
	AbstractCursorInputEvt* getFirstEvent(){
		if(events.size() == 0){
			return 0;
		}else{
			return events.front();
		}
	}
	
	/**
	 * Gets the event count.
	 * 
	 * @return the event count
	 */
	int getEventCount(){
		return events.size();
	}
	
	/**
	 * Gets the id.
	 * 
	 * @return the id
	 */
	long getId() {
		return ID;
	}
	
	/* (non-Javadoc)
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
#if 0
	bool equals(Object obj) {
		if(obj instanceof InputCursor){
			InputCursor compare = (InputCursor)obj;
			return this.getId() == compare.getId(); 
		}else{
			return false;
		}
	}
#endif
	
	/* (non-Javadoc)
	 * @see java.lang.Object#hashCode()
	 */
#if 0
	int hashCode() {
		return (""+this.ID).hashCode();
	}
#endif
	
	/* (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
#if 0
	String toString() {
		String s=("Cursor id=" +this.ID) + "\n";
		for (int i = 0; i < this.events.size(); i++) {
			s += "\t" + i + ": " + this.events.get(i)+ "\n";
		}
		return s;
	}
#endif


#if 0
	public void printLockSeekingAnalyzerList() {
		Set<AbstractCursorProcessor> claimed = lockingProcessorsToPriority.keySet();
		logger.debug("Lock seeking processors list of cursor: " + this.getId());
        for (AbstractCursorProcessor inputAnalyzer : claimed) {
            logger.debug(inputAnalyzer.getClass() + " " + " Priority: " + inputAnalyzer.getLockPriority());
        }
	}



	public void printInterestedAnalyzersList() {
		Set<AbstractCursorProcessor> watching = registeredProcessorsToPriority.keySet();
		logger.debug("Interested processors list of cursor: " + this.getId());
        for (AbstractCursorProcessor inputAnalyzer : watching) {
            logger.debug(inputAnalyzer.getClass() + " " + " Priority: " + inputAnalyzer.getLockPriority());
        }
	}
#endif


	/*
	//TODO make velocity time based?
	//FIXME EXPERIMENTAL!
	public float getVelocityX(){
		if (this.events.isEmpty() || this.events.size() < 2)
			return 0;
		
		
		AbstractCursorInputEvt posEvt 	= events.get(events.size()-1);
		AbstractCursorInputEvt prev 	= events.get(events.size()-2);
		
		if (prev == null)
			prev = posEvt;
		
		Vector3D pos 		= new Vector3D(posEvt.getPosX(), 	posEvt.getPosY(), 	0);
		Vector3D prevPos 	= new Vector3D(prev.getPosX(), 	prev.getPosY(), 	0);
		
        float invWidth = 1.0f/MT4jSettings.getInstance().getScreenWidth();
        
//		System.out.println("Pos: " + pos);
		float mouseNormX = pos.x * invWidth;
		float mouseVelX = (pos.x - prevPos.x) * invWidth;
		System.out.println("Mouse vel X: " + mouseVelX + " mouseNormX:" + mouseNormX);
		return mouseVelX;
	}
	
	//FIXME EXPERIMENTAL!
	public float getVelocityY(){
		if (this.events.isEmpty() || this.events.size() < 2)
			return 0;
		
		AbstractCursorInputEvt posEvt 	= events.get(events.size()-1);
		AbstractCursorInputEvt prev 	= events.get(events.size()-2);
		
		if (prev == null)
			prev = posEvt;
		
		Vector3D pos 		= new Vector3D(posEvt.getPosX(), posEvt.getPosY(), 	0);
		Vector3D prevPos 	= new Vector3D(prev.getPosX(), 	prev.getPosY(), 	0);
		
        float invHeight = 1.0f/MT4jSettings.getInstance().getScreenHeight();
        
		float mouseNormY = pos.y * invHeight;
		float mouseVelY = (pos.y - prevPos.y) * invHeight;
		System.out.println("Mouse vel Y: " + mouseVelY + " mouseNormY:" + mouseNormY);
		return mouseVelY;
	}
	*/
	
	
	Vector3 getDirection();
	
	
	/**
	 * Calculates and returns the velocity vector. 
	 * The calculation takes the events of the last milliseconds into account.
	 * The calculation is not physically correct but provides a good vector to use as
	 * inertia.
	 * 
	 * @return the velocity vector
	 */
	Vector3 getVelocityVector(){
		return getVelocityVector(120);
	}
	
	/**
	 * Calculates and returns the velocity vector.
	 * The calculation takes the events of the last milliseconds into account.
	 * The calculation is not physically correct but provides a good vector to use as
	 * inertia.
	 * 
	 * @param millisAgo the all events from millis ago are taken into calculation
	 * 
	 * @return the velocity vector
	 */
	Vector3 getVelocityVector(int millisAgo);
	
//    public double getAngleFromStartPoint() {
//        if(this.getEventCount()<=1){
//        	return 0.0;
//        }
//        else{
//        	int lastElemIndex = getEventCount()-1;
//        	CursorEvent[] events = this.getEvents();
//        	double x1 = events[0].getXRel();
//        	double x2 = events[lastElemIndex].getXRel();
//        	double y1 = events[0].getYRel();
//        	double y2 = events[lastElemIndex].getYRel();
//	
//        	Position p1 = events[0].getPosition();
//        	Position p2 = events[lastElemIndex].getPosition();
//        	return AngleUtil.calcAngle(p1,p2);
//        }
//    }
//    
    
    
};


#endif /* _INPUT_CURSOR_H_ */
