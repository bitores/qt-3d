#ifndef _DefaultScaleAction_h_
#define _DefaultScaleAction_h_
#include "utils/include/prerequisites.h"
#include "preinput.h"
#include "IGestureEventListener.h"
#include "AbstractCursorProcessor.h"
#include "ScaleEvent.h"
#include "utils/include/Vector3.h"
#include "scenegraph/GameObject.h"

class DefaultScaleAction:public IGestureEventListener {
	
	/** The target. */
	GameObject *target;
	
	/** The has scale limit. */
	bool hasScaleLimit;
	
	/** The min scale. */
	float minScale;
	
	/** The max scale. */
	float maxScale;
	
	/** The last event. */
	ScaleEvent lastEvent;
	
	/** The gesture aborted. */
	bool Aborted;

public:
	/**
	 * Instantiates a new default scale action.
	 */
	DefaultScaleAction(){
		init(0, 0,0, false);
	}
	
	/**
	 * Instantiates a new default scale action.
	 * 
	 * @param customTarget the custom target
	 */
	DefaultScaleAction(GameObject *customTarget){
		init(customTarget, 0,0, false);
	}
	
	
	
	
	/**
	 * Instantiates a new default scale action.
	 *
	 * @param minScaleFactor the min scale factor
	 * @param maxScaleFactor the max scale factor
	 */
	DefaultScaleAction(float minScaleFactor, float maxScaleFactor){
		init(0, minScaleFactor, maxScaleFactor, true);
	}
	
	/**
	 * Instantiates a new default scale action.
	 *
	 * @param customTarget the custom target
	 * @param minScaleFactor the min scale factor
	 * @param maxScaleFactor the max scale factor
	 */
	DefaultScaleAction(GameObject *customTarget, float minScaleFactor, float maxScaleFactor){
		init(customTarget, minScaleFactor, maxScaleFactor, true);
	}
	
	
	/**
	 * Instantiates a new default scale action.
	 *
	 * @param customTarget the custom target
	 * @param minScaleFactor the min scale factor
	 * @param maxScaleFactor the max scale factor
	 * @param useScaleLimit  use scale limit
	 */
	DefaultScaleAction(GameObject *customTarget, float minScaleFactor, float maxScaleFactor, bool useScaleLimit){
		init(customTarget, minScaleFactor, maxScaleFactor, useScaleLimit);
	}

    void init(GameObject *customTarget, float minScaleFactor, float maxScaleFactor, bool useScaleLimit)
    {
        Aborted = false;
        target = customTarget;
		if (minScaleFactor < 0 || maxScaleFactor < 0){
//			System.err.println("minScaleFactor < 0 || maxScaleFactor < 0    invalid settings!");
			hasScaleLimit = false;
		}
        else{
			hasScaleLimit = useScaleLimit;
		}
		minScale = minScaleFactor;
		maxScale = maxScaleFactor;
    }


	/* (non-Javadoc)
	 * @see org.mt4j.input.inputProcessors.IGestureEventListener#processGestureEvent(org.mt4j.input.inputProcessors.MTGestureEvent)
	 */
	bool processGestureEvent(GestureEvent& g) {
//		if (g instanceof ScaleEvent){
			ScaleEvent& scaleEvent = (ScaleEvent&)g;
			lastEvent = scaleEvent;
			
			if (target == 0)
				target = scaleEvent.getTarget(); 
			
			switch (scaleEvent.getId()) {
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
				doAction(target, scaleEvent);
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
	void doAction(GameObject *target, ScaleEvent& se) {
		if(!Aborted) {
			if (hasScaleLimit){
//				if (target instanceof MTComponent) {
					GameObject *comp = (GameObject*) target;

					//FIXME actually we should use globalmatrix but performance is better for localMatrix..
					Vector3 currentScale = comp->getTransform()->getScale();


					//We only check X because only uniform scales (x=y factor) should be used!
					if (currentScale.x * se.getScaleFactorX() > maxScale){
						//We should set to min scale, but we choose performance over accuracy
						//float factor = (1f/currentScale.x) * maxScale;
						//target.scaleGlobal(factor, factor, scaleEvent.getScaleFactorZ(), scaleEvent.getScalingPoint());
					}
                    else if (currentScale.x * se.getScaleFactorX() < minScale){
						//							System.out.println("Scale MIN Limit Hit!");
						//We should set to min scale, but we choose performance over accuracy
						//float factor = (1f/currentScale.x) * minScale;
						//target.scaleGlobal(factor, factor, scaleEvent.getScaleFactorZ(), scaleEvent.getScalingPoint());
					}
                    else{
                        
                        logprint(TAG_INPUT, "DefaultScaleAction->limit setScale:x:%f,y:%f,z:%f", 
                            se.getScaleFactorX(),
                            se.getScaleFactorY(),
                            se.getScaleFactorZ());
                        Vector3 pos = se.getLocalScalingPoint();
                        Vector3 newPos = Vector3(pos.x*se.getScaleFactorX(), pos.y*se.getScaleFactorY(), pos.z*se.getScaleFactorZ());
                        Vector3 globalPos = target->getTransform()->convertLocalToWorldPosition(newPos);
                        target->getTransform()->scale(se.getScaleFactorX(), 
                            								se.getScaleFactorY(), 
                            								se.getScaleFactorZ());
                        target->getTransform()->translate(se.getScalingPoint() - globalPos); // scale the object arcorrding to scalingPoint
					}
			}
            else{
                Vector3 pos = se.getLocalScalingPoint();
                logprint(TAG_INPUT, "DefaultScaleAction->setScale:x:%f,y:%f,z:%f,scalepos:x:%f,y:%f,z:%f", 
                    se.getScaleFactorX(),
                    se.getScaleFactorY(),
                    se.getScaleFactorZ(),
                    pos.x, pos.y, pos.z);

                Vector3 newPos = Vector3(pos.x*se.getScaleFactorX(), pos.y*se.getScaleFactorY(), pos.z*se.getScaleFactorZ());
                Vector3 globalPos = target->getTransform()->convertLocalToWorldPosition(newPos);
                target->getTransform()->scale(se.getScaleFactorX(), 
                    								se.getScaleFactorY(), 
                    								se.getScaleFactorZ());
                target->getTransform()->translate(se.getScalingPoint() - globalPos); // scale the object arcorrding to scalingPoint
//				target.scaleGlobal(
//						se.getScaleFactorX(), 
//						se.getScaleFactorY(), 
//						se.getScaleFactorZ(), 
//						se.getScalingPoint());
			}
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
	ScaleEvent getLastEvent() {
		return lastEvent;
	}

	/* (non-Javadoc)
	 * @see org.mt4j.input.inputProcessors.ICollisionAction#setGestureAborted(boolean)
	 */
	void setGestureAborted(bool aborted) {
		Aborted = aborted;
	}

};

#endif /* _DefaultScaleAction_h_ */
