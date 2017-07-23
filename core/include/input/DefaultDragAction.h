#ifndef _DEFAULT_DRAG_ACTION_H_
#define _DEFAULT_DRAG_ACTION_H_
#include "utils/include/prerequisites.h"
#include "preinput.h"
#include "IGestureEventListener.h"
#include "AbstractCursorProcessor.h"
#include "DragEvent.h"
#include "utils/include/Vector3.h"
#include "scenegraph/GameObject.h"

class DefaultDragAction:public IGestureEventListener
{
	
	/** The drag target. */
	GameObject *dragTarget;
	
	/** The use custom target. */
	bool useCustomTarget;
	
	/** The gesture aborted. */
	bool Aborted;
	
	/** The last event. */
	DragEvent lastEvent;

public:	
	/**
	 * Instantiates a new default drag action.
	 */
	DefaultDragAction(){
		useCustomTarget = false;
        Aborted = false;
	}
	
	/**
	 * Instantiates a new default drag action.
	 *
	 * @param dragTarget the drag target
	 */
	DefaultDragAction(GameObject *_dragTarget){
		dragTarget = _dragTarget;
		useCustomTarget = true;
        Aborted = false;
	}
	

	/* (non-Javadoc)
	 * @see org.mt4j.input.inputProcessors.IGestureEventListener#processGestureEvent(org.mt4j.input.inputProcessors.MTGestureEvent)
	 */
	bool processGestureEvent(GestureEvent &g) {
			DragEvent& dragEvent = (DragEvent&)g;
			lastEvent = dragEvent;
			
			if (!useCustomTarget)
				dragTarget = dragEvent.getTarget(); 
			
			switch (dragEvent.getId()) {
			case GestureEvent::GESTURE_STARTED:
			case GestureEvent::GESTURE_RESUMED:
				//Put target on top -> draw on top of others
//				if (dragTarget instanceof MTComponent){
//					MTComponent baseComp = (MTComponent)dragTarget;
					
//					baseComp.sendToFront();  // TODO: Puts this components to the end of the children list of its parent.
	                                      //            This will result in this component being drawn last and on top
	                                      //            of others at the same z-position.
	                dragTarget->sendToFront();
	 
					//// TODO:
					/*
					//End all animations of the target
					Animation[] animations = AnimationManager.getInstance().getAnimationsForTarget(dragTarget);
					for (int i = 0; i < animations.length; i++) {
						Animation animation = animations[i];
						animation.stop();
					}
					*/
//				}
					
				translate(dragTarget, dragEvent);
				break;
			case GestureEvent::GESTURE_UPDATED:
				translate(dragTarget, dragEvent);
				break;
			case GestureEvent::GESTURE_CANCELED:
				break;
			case GestureEvent::GESTURE_ENDED:
				break;
			default:
				break;
			}
		return false;
	}

	
	void translate(GameObject *obj, DragEvent &de) {
		if(!Aborted)
		{
//		    obj.translateGlobal(de.getTranslationVect());
            logprint(TAG_INPUT, "DefaultDragAction->translate,x:%f,y:%f,z:%f", de.getTranslationVect().x, de.getTranslationVect().y, de.getTranslationVect().z);
            obj->getTransform()->translate(de.getTranslationVect()); // FIXME: TransformSpace relativeTo = TS_PARENT? or TS_WORLD ?
		}
	}

	/* (non-Javadoc)
	 * @see org.mt4j.input.inputProcessors.ICollisionAction#gestureAborted()
	 */
	bool gestureAborted() {
		return Aborted;
	}

	/* (non-Javadoc)
	 * @see org.mt4j.input.inputProcessors.ICollisionAction#getLastEvent()
	 */
	DragEvent getLastEvent() {
		return lastEvent;
	}

	/* (non-Javadoc)
	 * @see org.mt4j.input.inputProcessors.ICollisionAction#setGestureAborted(boolean)
	 */
	void setGestureAborted(bool aborted) {
		Aborted = aborted;
	}

};


#endif /* _DEFAULT_DRAG_ACTION_H_ */
