#ifndef _DRAG_PROCESSOR_H_
#define _DRAG_PROCESSOR_H_
#include "utils/include/prerequisites.h"
#include "preinput.h"
#include "AbstractCursorProcessor.h"
#include "utils/include/Vector3.h"
#include "utils/include/Plane.h"

/**
 * The Class DragContext.
 * @author Christopher Ruff
 */
class DragContext 
{
    Root *mRoot;
    
    /** The start position. */
    Vector3 startPosition;
    
    /** The last position. */
    Vector3 lastPosition;
    
    /** The new position. */
    Vector3 newPosition;
    
    /** The drag object. */
    GameObject *dragObject;
    
    /** The m. */
    InputCursor *m; 
    
    /** The gesture aborted. */
    bool gestureAborted;
    
    /** The drag plane normal. */
    Vector3 dragPlaneNormal;
    Plane plane;

    bool inited;

public:
    DragContext() {
        mRoot = 0;
        dragObject = 0;
        m = 0;
        inited = false;
        gestureAborted = false;
    }
    /**
     * Instantiates a new drag context.
     * 
     * @param c the cursor
     * @param dragObject the drag object
     */
    DragContext(Root *root, InputCursor *c, GameObject *_dragObject) {  
        gestureAborted = false;
        init(root, c, _dragObject);
    }

    void init(Root *root, InputCursor *c, GameObject *_dragObject);
    void uninit();
    void updateDragPosition();

    Vector3 getLastPosition() {
        return lastPosition;
    }

    Vector3 getNewPosition() {
        return newPosition;
    }

    bool isGestureAborted() {
        return gestureAborted;
    }
    
    InputCursor* getCursor(){
        return m;
    }

    bool isInited() {
        return inited;
    }
 };

class DragProcessor:public AbstractCursorProcessor 
{
	
	/** The applet. */
	Root *mRoot;
	
	/** The dc. */
	DragContext mDc;

public:
    static const String NAME;
    DragProcessor()
    {
        init(0, false);
    }
	DragProcessor(Root *root)
    {
		init(root, false);
	}

	/**
	 * Instantiates a new drag processor.
	 * 
	 * @param graphicsContext the graphics context
	 */
	DragProcessor(Root *root, bool _stopEventPropagation)
    {
        init(root, _stopEventPropagation);
	}
    void init(Root *root, bool _stopEventPropagation)
    {
        mRoot = root;
        setLockPriority(1);
		setDebug(false);
        AbstractCursorProcessor::init(_stopEventPropagation);
    }

	
	/* (non-Javadoc)
	 * @see org.mt4j.input.inputProcessors.componentProcessors.AbstractCursorProcessor#cursorStarted(org.mt4j.input.inputData.InputCursor, org.mt4j.input.inputData.MTFingerInputEvt)
	 */
	void cursorStarted(InputCursor *cursor, AbstractCursorInputEvt &fe);

	/* (non-Javadoc)
	 * @see org.mt4j.input.inputProcessors.componentProcessors.AbstractCursorProcessor#cursorUpdated(org.mt4j.input.inputData.InputCursor, org.mt4j.input.inputData.MTFingerInputEvt)
	 */
	void cursorUpdated(InputCursor *cursor, AbstractCursorInputEvt &fe);

	
	/* (non-Javadoc)
	 * @see org.mt4j.input.inputProcessors.componentProcessors.AbstractCursorProcessor#cursorEnded(org.mt4j.input.inputData.InputCursor, org.mt4j.input.inputData.MTFingerInputEvt)
	 */
	void cursorEnded(InputCursor *cursor, AbstractCursorInputEvt &fe);



	/* (non-Javadoc)
	 * @see org.mt4j.input.inputProcessors.componentProcessors.AbstractCursorProcessor#cursorLocked(org.mt4j.input.inputData.InputCursor, org.mt4j.input.inputProcessors.IInputProcessor)
	 */
	void cursorLocked(InputCursor *cursor, IInputProcessor *p);



	/* (non-Javadoc)
	 * @see org.mt4j.input.inputProcessors.componentProcessors.AbstractCursorProcessor#cursorUnlocked(org.mt4j.input.inputData.InputCursor)
	 */
	void cursorUnlocked(InputCursor *cursor);


	
	
	/* (non-Javadoc)
	 * @see org.mt4j.input.inputProcessors.componentProcessors.AbstractComponentProcessor#getName()
	 */
	String getName() {
		return "Drag Processor";
	}

};



#endif /* _DRAG_PROCESSOR_H_ */
