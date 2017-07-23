#ifndef _TapProcessor_h_
#define _TapProcessor_h_
#include "utils/include/prerequisites.h"
#include "preinput.h"
#include "AbstractCursorProcessor.h"
#include "utils/include/Vector3.h"


class TapProcessor:public AbstractCursorProcessor 
{
	
	/** The applet. */
//	private PApplet applet;
    Root *mRoot;
	
	/** The max finger up dist. */
	float maxFingerUpDist;
	
	/** The button down screen pos. */
	Vector3 buttonDownScreenPos;
	
	/** The enable double tap. */
	bool enableDoubleTap;
	
	/** The time last tap. */
	long timeLastTap;
	
	/** The double tap time. */
	int doubleTapTime;
    
public:
    static const String NAME;
    TapProcessor():AbstractCursorProcessor(false) {
        init(0, 18.0f);
    }
	/**
	 * Instantiates a new tap processor.
	 * 
	 * @param pa the pa
	 */
	TapProcessor(Root *root):AbstractCursorProcessor(false){
//		this(pa, 18.0f);
        init(root, 18.0f);
	}
	
	/**
	 * Instantiates a new tap processor.
	 * 
	 * @param pa the pa
	 * @param maxFingerUpDistance the max finger up distance
	 */
	TapProcessor(Root *root, float maxFingerUpDistance):AbstractCursorProcessor(false) {
//		this(pa, maxFingerUpDistance, false, 300); 
        init(root, maxFingerUpDistance, false, 300);
	}
	
	/**
	 * Instantiates a new tap processor.
	 * 
	 * @param pa the pa
	 * @param maxFingerUpDistance the max finger up distance
	 * @param enableDoubleTap the enable double tap
	 */
	TapProcessor(Root *root, float maxFingerUpDistance, bool enableDoubleTap):AbstractCursorProcessor(false){
//		this(pa, maxFingerUpDistance, enableDoubleTap, 300);
        init(root, maxFingerUpDistance, enableDoubleTap, 300);
	}
	
	/**
	 * Instantiates a new tap processor.
	 * 
	 * @param pa the pa
	 * @param maxFingerUpDistance the max finger up distance
	 * @param enableDoubleTap the enable double tap
	 * @param doubleTapTime the double tap time
	 */
	TapProcessor(Root *root, float maxFingerUpDistance, bool enableDoubleTap, int doubleTapTime):AbstractCursorProcessor(false){
//		this(pa, maxFingerUpDistance, enableDoubleTap, doubleTapTime, false);
        init(root, maxFingerUpDistance, enableDoubleTap, doubleTapTime);
	}

	/**
	 * Instantiates a new tap processor.
	 *
	 * @param pa the pa
	 * @param maxFingerUpDistance the max finger up distance
	 * @param enableDoubleTap the enable double tap
	 * @param doubleTapTime the double tap time
	 * @param stopEventPropagation the stop event propagation
	 */
	TapProcessor(Root *root, float maxFingerUpDistance, bool enableDoubleTap, int doubleTapTime, bool stopEventPropagation):AbstractCursorProcessor(stopEventPropagation){
//		super(stopEventPropagation);
//		this.applet = pa;
//		this.maxFingerUpDist = maxFingerUpDistance;
//		this.setLockPriority(1);
//		this.setDebug(false);
//		
//		this.enableDoubleTap = enableDoubleTap;
//		this.doubleTapTime = doubleTapTime;
//		this.timeLastTap = -1;
        init(root, maxFingerUpDistance, enableDoubleTap, doubleTapTime);
		//System.out.println("Double click default time:" + Toolkit.getDefaultToolkit().getDesktopProperty("awt.multiClickInterval"));
	}

    void init(Root *root, float maxFingerUpDistance) {
        init(root, maxFingerUpDistance, false, 300);
    }
    void init(Root *root, float maxFingerUpDistance, bool DoubleTap, int doubleTime) {
        mRoot = root;
		maxFingerUpDist = maxFingerUpDistance;
		setLockPriority(1);
		setDebug(false);
		
		enableDoubleTap = DoubleTap;
		doubleTapTime = doubleTime;
		timeLastTap = -1;
    }
        

	/* (non-Javadoc)
	 * @see org.mt4j.input.inputProcessors.componentProcessors.AbstractCursorProcessor#cursorStarted(org.mt4j.input.inputData.InputCursor, org.mt4j.input.inputData.MTFingerInputEvt)
	 */
	void cursorStarted(InputCursor *cursor, AbstractCursorInputEvt &positionEvent);


	/* (non-Javadoc)
	 * @see org.mt4j.input.inputProcessors.componentProcessors.AbstractCursorProcessor#cursorUpdated(org.mt4j.input.inputData.InputCursor, org.mt4j.input.inputData.MTFingerInputEvt)
	 */
	void cursorUpdated(InputCursor *cursor, AbstractCursorInputEvt &positionEvent);
	
	
	/* (non-Javadoc)
	 * @see org.mt4j.input.inputProcessors.componentProcessors.AbstractCursorProcessor#cursorEnded(org.mt4j.input.inputData.InputCursor, org.mt4j.input.inputData.MTFingerInputEvt)
	 */
	void cursorEnded(InputCursor *cursor, AbstractCursorInputEvt &positionEvent);

private:	
	/**
	 * End gesture.
	 *
	 * @param m the m
	 * @param positionEvent the position event
	 */
	void endGesture(InputCursor *cursor, AbstractCursorInputEvt &positionEvent);

public:

	/* (non-Javadoc)
	 * @see org.mt4j.input.inputProcessors.componentProcessors.AbstractCursorProcessor#cursorLocked(org.mt4j.input.inputData.InputCursor, org.mt4j.input.inputProcessors.IInputProcessor)
	 */
	void cursorLocked(InputCursor *cursor, IInputProcessor *lockingProcessor);



	/* (non-Javadoc)
	 * @see org.mt4j.input.inputProcessors.componentProcessors.AbstractCursorProcessor#cursorUnlocked(org.mt4j.input.inputData.InputCursor)
	 */
	void cursorUnlocked(InputCursor *cursor) {
//		logger.debug(this.getName() + " Recieved UNLOCKED signal for cursor ID: " + m.getId());

//		if (getLockedCursors().size() >= 1){ //we dont need the unlocked cursor, gesture still in progress
////			logger.debug(this.getName() + " still in progress - we dont need the unlocked cursor" );
//			return;
//		}
	}

	
	
	/**
	 * Gets the max finger up dist.
	 * 
	 * @return the max finger up dist
	 */
	float getMaxFingerUpDist() {
		return maxFingerUpDist;
	}


	/**
	 * Sets the maximum allowed distance of the position
	 * of the finger_down event and the finger_up event
	 * that fires a click event (in screen pixels).
	 * <br>This ensures that a click event is only raised
	 * if the finger didnt move too far during the click.
	 * 
	 * @param maxFingerUpDist the max finger up dist
	 */
	void setMaxFingerUpDist(float maxDist) {
		maxFingerUpDist = maxDist;
	}
	
	
	
	/* (non-Javadoc)
	 * @see org.mt4j.input.inputProcessors.componentProcessors.AbstractComponentProcessor#getName()
	 */
	String getName() {
		return String("Tap Processor");
	}

	/**
	 * Checks if is enable double tap.
	 * 
	 * @return true, if is enable double tap
	 */
	bool isEnableDoubleTap() {
		return enableDoubleTap;
	}

	/**
	 * Sets the enable double tap.
	 * 
	 * @param enableDoubleTap the new enable double tap
	 */
	void setEnableDoubleTap(bool enable) {
		enableDoubleTap = enable;
	}

	/**
	 * Gets the double tap time.
	 * 
	 * @return the double tap time
	 */
	int getDoubleTapTime() {
		return doubleTapTime;
	}

	/**
	 * Sets the double tap time.
	 * 
	 * @param doubleTapTime the new double tap time
	 */
	void setDoubleTapTime(int TapTime) {
		doubleTapTime = TapTime;
	}
};



#endif /* _TapProcessor_h_ */
