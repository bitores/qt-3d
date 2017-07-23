#ifndef _ScaleProcessor_h_
#define _ScaleProcessor_h_
#include "utils/include/prerequisites.h"
#include "preinput.h"
#include "AbstractCursorProcessor.h"
#include "utils/include/Vector3.h"
#include "utils/include/Plane.h"



/**
 * The Class ScaleContext.
 */
class ScaleContext 
{

    Root *mRoot;
    
	/** The first finger cursor. */
	InputCursor *firstFingerCursor; 
	
	/** The second finger cursor. */
	InputCursor *secondFingerCursor; 
	
	/** The object. */
	GameObject *object;
	
	/** The first finger new pos. */
	Vector3 firstFingerNewPos; // global point
	Vector3 firstfingerLocalPos; // local point
	
	/** The second finger new pos. */
	Vector3 secondFingerNewPos; // global point
	Vector3 secondfingerLocalPos;
	
	/** The second finger start pos. */
//	Vector3 secondFingerStartPos;
	
	/** The last scale distance. */
	float lastScaleDistance;
	
	/** The scale plane normal. */
//	Vector3 scalePlaneNormal;
    Plane plane;
	
	/** The first finger start pos. */
//	Vector3 firstFingerStartPos;

	bool gestureAborted;

    bool inited;
	
public:		
    ScaleContext() {
        mRoot = 0;
        object = 0;
        inited = false;
        gestureAborted = false;
    }
	/**
	 * Instantiates a new scale context.
	 * 
	 * @param firstFingerCursor the first finger cursor
	 * @param secondFingerCursor the second finger cursor
	 * @param object the object
	 */
	ScaleContext(Root *root, InputCursor *_firstFingerCursor, InputCursor *_secondFingerCursor, GameObject *_object) {
	    gestureAborted = false;
        mRoot = root;
        firstFingerCursor = _firstFingerCursor;
        secondFingerCursor = _secondFingerCursor;
        object = _object;
		init(root, _firstFingerCursor, _secondFingerCursor, _object);
	}

    void init(Root *root, InputCursor *_firstFingerCursor, InputCursor *_secondFingerCursor, GameObject *_object);
    void uninit();
    
	bool isGestureAborted() {
		return gestureAborted;
	}

	/**
	 * Gets the second finger cursor.
	 * 
	 * @return the second finger cursor
	 */
	InputCursor* getSecondFingerCursor() {
		return secondFingerCursor;
	}

	/**
	 * Gets the first finger cursor.
	 * 
	 * @return the first finger cursor
	 */
	InputCursor* getFirstFingerCursor() {
		return firstFingerCursor;
	}

	
	/**
	 * Gets the updated scale factor.
	 * 
	 * @param m the m
	 * 
	 * @return the updated scale factor
	 */
	float getUpdatedScaleFactor(InputCursor *m);
	

	/**
	 * Gets the first finger new pos.
	 * 
	 * @return the first finger new pos
	 */
	Vector3 getFirstFingerNewPos() {
		return firstFingerNewPos;
	}

    Vector3 getFirstFingerLocalPos() {
        return firstfingerLocalPos;
    }
	/**
	 * Gets the second finger new pos.
	 * 
	 * @return the second finger new pos
	 */
	Vector3 getSecondFingerNewPos() {
		return secondFingerNewPos;
	}

    Vector3 getSecondFingerLocalPos() {
        return secondfingerLocalPos;
    }
    bool isInited() {
        return inited;
    }
};

class ScaleProcessor:public AbstractCursorProcessor 
{
	
	/** The applet. */
    Root *mRoot;
	
	/** The scale context. */
	ScaleContext sc;

public:	
    static const String NAME;
    
    ScaleProcessor() {
        init(0, false);
    }
    
	ScaleProcessor(Root *root){
       init(root, false);
	}
	
	/**
	 * Instantiates a new scale processor.
	 * 
	 * @param graphicsContext the graphics context
	 */
	ScaleProcessor(Root *root, bool stopPropagation){
		init(root,stopPropagation);
		
	}
	
	void init(Root *root, bool _stopEventPropagation)
    {
        mRoot = root;
        setLockPriority(2);
		setDebug(false);
        AbstractCursorProcessor::init(_stopEventPropagation);
    }

	void cursorStarted(InputCursor *newCursor, AbstractCursorInputEvt& fEvt);

	void cursorUpdated(InputCursor *cursor, AbstractCursorInputEvt& fEvt);

	void cursorEnded(InputCursor *cursor, AbstractCursorInputEvt& fEvt);

	void endGesture(InputCursor *cursor, AbstractCursorInputEvt& fEvt, InputCursor *firstCursor, InputCursor *secondCursor);
	
	void cursorLocked(InputCursor *cursor, IInputProcessor *lockingAnalyzer);
	
	void cursorUnlocked(InputCursor *cursor);
	
	String getName() {
		return "Scale Processor";
	}



};

#endif /* _ScaleProcessor_h_ */
