#ifndef _ABSTRACT_CURSOR_INPUT_EVENT_H_
#define _ABSTRACT_CURSOR_INPUT_EVENT_H_
#include "utils/include/prerequisites.h"
#include "preinput.h"

#include "InputEvent.h"
//#include "utils/include/Vector3.h"

class InputCursor;
class AbstractInputSource;
class AbstractCursorInputEvt:public InputEvent 
{

    /** The position x. */
	float mpositionX;
	
	/** The position y. */
	float mpositionY;
	
	/** The id. */
	int mId;
	
	/** The associated cursor. */
	InputCursor *mAssociatedCursor;
//	public enum InputState{
//		INPUT_DETECTED,
//		INPUT_UPDATED,
//		INPUT_ENDED
//	}
	
	/** The Constant INPUT_DETECTED. 
	 * @deprecated use INPUT_STARTED instead 
	 * */
public:
    static const int INPUT_DETECTED = 0;
	
	static const int INPUT_STARTED = 0;
	
	static const int INPUT_UPDATED = 1;
	
	static const int INPUT_ENDED = 2;

	
	
	/**
	 * Instantiates a new touch event.
	 * 
	 * @param source the source
	 * @param positionX the position x
	 * @param positionY the position y
	 * @param id the id
	 * @param c the m
	 */
	AbstractCursorInputEvt(AbstractInputSource *source, 
	        float positionX, float positionY, int id, InputCursor *c):InputEvent((Object*)source, InputEvent::CURSOR_EVENT)
	{
		mId = id;
		
		mpositionX = positionX;
		mpositionY = positionY;
		
		mAssociatedCursor = c;
	}
	
	/**
	 * Instantiates a new touch event.
	 * 
	 * @param source the source
	 * @param positionX the position x
	 * @param positionY the position y
	 * @param id the id
	 * @param m the m
	 * @param target the target
	 */
	AbstractCursorInputEvt(AbstractInputSource *source, GameObject *target, 
	        float positionX, float positionY, int id, InputCursor *c):InputEvent((Object*)source, target)
	{
		mId = id;
		
		mpositionX = positionX;
		mpositionY = positionY;
		
		mAssociatedCursor = c;
	}
	
	
	void setId(int id){
		mId = id;
	}
	

	
	/**
	 * Gets the cursor.
	 * 
	 * @return the cursor
	 */
	InputCursor* getCursor() {
		return mAssociatedCursor;
	}


	void setCursor(InputCursor *associatedcursor) {
		mAssociatedCursor = associatedcursor;
	}
		

	/**
	 * This method should be called before firing this event to the global input processors.
	 * Here, the event is added to its cursor.
	 */
	void onFired();

	
	/**
	 * Gets the position x.
	 * 
	 * @return the position x
	 * @deprecated use getScreenX()
	 */
	float getPosX() {
		return mpositionX;
	}

	
	/**
	 * Gets the position y.
	 * 
	 * @return the position y
	 * @deprecated use getScreenY()
	 */
	float getPosY() {
		return mpositionY;
	}
	
	float getX(){
		return mpositionX;
	}
	
	float getY(){
		return mpositionY;
	}
	
	
	/**
	 * Gets the position.
	 *
	 * @return the position
	 */
	Vector3 getPosition();
	
	
	void setScreenX(float positionX) {
		mpositionX = positionX;
	}

	void setScreenY(float positionY) {
		mpositionY = positionY;
	}

	/**
	 * Gets the id.
	 * 
	 * @return the id
	 */
	int getId() {
		return mId;
	}


	/* (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
//	public String toString(){
//		return super.toString() + "; " + " PosX: " + positionX + " PosY: " + positionY + " InputSource: " + this.getSource(); 
//	}
	
	

//	@Override
//	abstract public Object clone() throws CloneNotSupportedException;
	
	
	
	/*
	abstract public Inputcursor<? extends AbstractCursorInputEvt> getcursor();

	
	abstract public float getPositionX();

	abstract public float getPositionY();
	
	abstract public boolean isAddedTocursor();
	
	abstract public void setAddedTocursor(boolean addedTocursor);
	*/
};


#endif /* _ABSTRACT_CURSOR_INPUT_EVENT_H_ */
