#ifndef _DefaultRotateAction_h_
#define _DefaultRotateAction_h_
#include "utils/include/prerequisites.h"
#include "preinput.h"
#include "IGestureEventListener.h"
#include "AbstractCursorProcessor.h"
#include "RotateEvent.h"
#include "utils/include/Vector3.h"
#include "scenegraph/GameObject.h"


/**
 * The Class DefaultRotateAction.
 * 
 * @author Christopher Ruff
 */
class DefaultRotateAction:public IGestureEventListener {
	
	/** The target. */
	GameObject *target;
	
	/** The use custom target. */
//	bool useCustomTarget;
	
	/** The last event. */
	RotateEvent lastEvent;
	
	/** The gesture aborted. */
	bool Aborted;
    
public:	
	/**
	 * Instantiates a new default rotate action.
	 */
	DefaultRotateAction(){
	    Aborted = false;
	    target = 0;
//		useCustomTarget = false;
	}
	
	/**
	 * Instantiates a new default rotate action.
	 * 
	 * @param customTarget the custom target
	 */
	DefaultRotateAction(GameObject *customTarget){
	    Aborted = false;
		target = customTarget;
//		useCustomTarget = true;
	}

	/* (non-Javadoc)
	 * @see org.mt4j.input.inputProcessors.IGestureEventListener#processGestureEvent(org.mt4j.input.inputProcessors.MTGestureEvent)
	 */
	bool processGestureEvent(GestureEvent &g) {
//		if (g instanceof RotateEvent){
			RotateEvent &rotateEvent = (RotateEvent&)g;
			lastEvent = rotateEvent;
			
			if (target == 0)
				target = rotateEvent.getTarget(); 
			
			switch (rotateEvent.getId()) {
			case GestureEvent::GESTURE_STARTED:
			case GestureEvent::GESTURE_RESUMED:
//				if (target instanceof MTComponent){
					target->sendToFront();
					/*
					Animation[] animations = AnimationManager.getInstance().getAnimationsForTarget(target);
					for (int i = 0; i < animations.length; i++) {
						Animation animation = animations[i];
						animation.stop();
					}
					*/
//				}
				break;
			case GestureEvent::GESTURE_UPDATED:
				doAction(target, rotateEvent);
				break;
			case GestureEvent::GESTURE_CANCELED:
			case GestureEvent::GESTURE_ENDED:
				break;
			default:
				break;
			}
//		}
		return false;
	}
protected:	
	void doAction(GameObject *comp, RotateEvent &re){
		if(!gestureAborted()) {
//			comp.rotateZGlobal(re.getRotationPoint(), re.getRotationDegrees());
            Vector3 pos = re.getRotationPoint(); // global point
            comp->getTransform()->roll(re.getRotationRadian(), TS_LOCAL);
            Matrix4 matrix = comp->getTransform()->_getFullTransform();
            Vector3 newpos = matrix * pos;
            comp->getTransform()->translate(pos - newpos);
            
			if (comp->isGestureAllowed(DragProcessor::NAME))
				comp->getTransform()->translate(re.getTranslationVector());
		}
	}
public:

	/* (non-Javadoc)
	 * @see org.mt4j.input.inputProcessors.ICollisionAction#gestureAborted()
	 */
	bool gestureAborted() {
		return Aborted;
	}

	/* (non-Javadoc)
	 * @see org.mt4j.input.inputProcessors.ICollisionAction#getLastEvent()
	 */
	GestureEvent getLastEvent() {
		return lastEvent;
	}

	/* (non-Javadoc)
	 * @see org.mt4j.input.inputProcessors.ICollisionAction#setGestureAborted(boolean)
	 */
	void setGestureAborted(bool aborted) {
		Aborted = aborted;
	}
};



#endif /* _DefaultRotateAction_h_ */
