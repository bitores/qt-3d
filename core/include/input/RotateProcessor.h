#ifndef _RotateProcessor_h_
#define _RotateProcessor_h_
#include "utils/include/prerequisites.h"
#include "preinput.h"
#include "AbstractCursorProcessor.h"
#include "utils/include/Vector3.h"
#include "utils/include/Plane.h"



/**
 * The Class RotationContext.
 */
class RotationContext {

    Root *mRoot;
    
	/** The pin finger start. */
	Vector3 pinFingerStart;

	/** The pin finger last. */
	Vector3 pinFingerLast;

	/** The pin finger new. */
	Vector3 pinFingerNew;

	/** The rotate finger start. */
	Vector3 rotateFingerStart;

	/** The rotate finger last. */
	Vector3 rotateFingerLast;

	/** The rotate finger new. */
	Vector3 rotateFingerNew;

	/** The last rotation vect. */
	Vector3 lastRotationVect;

	/** The object. */
	GameObject *object;

	/** The rotation point. */
	Vector3 rotationPoint;

	/** The pin finger cursor. */
	InputCursor *pinFingerCursor; 

	/** The rotate finger cursor. */
	InputCursor *rotateFingerCursor; 

    /** The drag plane normal. */
//	Vector3 dragPlaneNormal;
    Plane plane;
    
	bool gestureAborted;

    bool inited;
public:
    RotationContext() {
        mRoot = 0;
        object = 0;
        inited = false;
        gestureAborted = false;
    }
	/**
	 * Instantiates a new rotation context.
	 * 
	 * @param pinFingerCursor the pin finger cursor
	 * @param rotateFingerCursor the rotate finger cursor
	 * @param object the object
	 */
	RotationContext(Root *root, InputCursor *_pinFingerCursor, InputCursor *_rotateFingerCursor, GameObject *_object){
		init(root, _pinFingerCursor, _rotateFingerCursor, _object);
	}

    void init(Root *root, InputCursor *_pinFingerCursor, InputCursor *_rotateFingerCursor, GameObject *_object);
    void uninit();
	/**
	 * Update and get rotation angle.
	 * 
	 * @param moveCursor the move cursor
	 * 
	 * @return the float
	 */
	float updateAndGetRotationAngle(InputCursor *moveCursor);

private:

	/**
	 * Update rotate finger.
	 */
	void updateRotateFinger();


	/**
	 * Update pin finger.
	 */
	void updatePinFinger();

public:

	/**
	 * Gets the rotation point.
	 * 
	 * @return the rotation point
	 */
	Vector3 getRotationPoint() {
		return rotationPoint;
	}

	/**
	 * Gets the pin finger cursor.
	 * 
	 * @return the pin finger cursor
	 */
	InputCursor* getPinFingerCursor() {
		return pinFingerCursor;
	}

	/**
	 * Gets the rotate finger cursor.
	 * 
	 * @return the rotate finger cursor
	 */
	InputCursor* getRotateFingerCursor() {
		return rotateFingerCursor;
	}

	bool isGestureAborted() {
		return gestureAborted;
	}
	
	InputCursor* getFirstCursor(){
		return pinFingerCursor;
	}
	
	InputCursor* getSecondCursor(){
		return rotateFingerCursor;
	}

    bool isInited() {
        return inited;
    }
};

/**
 * The Class RotateProcessor. Rotation multitouch gesture.
 * Fires RotateEvent gesture events.
 * @author Christopher Ruff
 */
class RotateProcessor:public AbstractCursorProcessor {

	/** The applet. */
    Root *mRoot;
    
	/** The rc. */
	RotationContext rc;
	
public:
    static const String NAME;

    RotateProcessor() {
        init(0, false);
    }
    
	RotateProcessor(Root *root){
       init(root, false);
	}

	/**
	 * Instantiates a new rotate processor.
	 * 
	 * @param graphicsContext the graphics context
	 */
    RotateProcessor(Root *root, bool stopPropagation){
		init(root,stopPropagation);
		
	}
	void init(Root *root, bool _stopEventPropagation)
    {
        mRoot = root;
        setLockPriority(2);
		setDebug(false);
        AbstractCursorProcessor::init(_stopEventPropagation);
    }
    
	void cursorStarted(InputCursor *newCursor, AbstractCursorInputEvt &positionEvent);
	void cursorUpdated(InputCursor *m, AbstractCursorInputEvt &positionEvent);
	void cursorEnded(InputCursor *c, AbstractCursorInputEvt &positionEvent);
	void endGesture(InputCursor *leftOverCursor, AbstractCursorInputEvt &positionEvent, InputCursor *firstCursor, InputCursor *secondCursor);
	void cursorLocked(InputCursor *c, IInputProcessor *lockingAnalyzer);
	void cursorUnlocked(InputCursor *c);
	
	String getName() {
		return "Rotate Processor";
	}

};


#endif 
