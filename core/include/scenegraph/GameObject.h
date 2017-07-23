#ifndef __GameObject_h__
#define __GameObject_h__

#include "utils/include/prerequisites.h"
#include "utils/include/platform.h"
#include "utils/include/AxisAlignedBox.h"
#include "base/Object.h"
#include "rendersystem/Renderer.h"
#include "component/Component.h"
#include "base/Light.h"
#include "input/AbstractComponentProcessor.h"
#include "input/IGestureEventListener.h"
#include "input/IInputEventListener.h"
#include "input/ComponentInputProcessorSupport.h"
#include "input/GestureEventSupport.h"
#include "input/PickInfo.h"
#include "input/PickResult.h"
#include "utils/include/Transform.h"

class GameObject : public Object, public IInputEventListener, public IGestureEventListener, public ITransformListener
{
protected:
	String mName;
	bool mVisible;
	bool mPickable;
	bool mComposite;
	bool mEnabled;
	bool mUseIdentityView;

	typedef std::list<GameObject*> GameObjectList;
	GameObjectList mChildrenGameObjects;

	Transform *mTransform;
	RendererPtr mRenderer;
	//LightPtr mLight;

	typedef std::list<ComponentPtr> ComponentList;
	ComponentList mComponents;

//	Animation* mCurrentAnimation;
    AxisAlignedBox mWorldAABB;

    /** The input listeners. */
	std::list<IInputEventListener*> mInputListeners; //  default: inputProcessorSupport
    /** The input processors support. */
    ComponentInputProcessorSupport inputProcessorsSupport;
    /** The gesture evt support. */
    GestureEventSupport gestureEvtSupport;
    /** The allowed gestures. */
	std::list<String> allowedGestures;
public:
	GameObject(const String& name, bool visible = true);
	virtual ~GameObject();

	bool isVisible();
	void setVisible(bool visible);

	void setUseIdentityView(bool useIdentityView);
	const bool getUseIdentityView() const;

	GameObject * getParent();

	void addGameObject(GameObject* go);
	void removeGameObject(GameObject * go);

	void addComponent(ComponentPtr component);
	//void removeComponents();
	ComponentPtr getComponent(size_t idx);
	std::list<ComponentPtr>& getComponents();


	// override ITransformListener::_notifyTransformChanged
	void _notifyTransformChanged();

//	Quad* getComponent();

	void setRenderer(RendererPtr pRender);
	RendererPtr& getRenderer();

	MeshFilter* getMeshFilter();

	//void setTransform(Transform* transform);
	Transform* getTransform();

	void findVisibleObject(RenderQueue* renderQueue);
	const String& getName(void) const;

	void hitTest(float x, float y, HitResultList hits);

	void dumpGameObjectTree(int depth = 0);

    AxisAlignedBox getBoundingBox();
    AxisAlignedBox getFullBoundingBox(void);
    AxisAlignedBox getChildObjectsBoundingBox(void);
    AxisAlignedBox getWorldBoundingBox();
    bool isComposite() { return mComposite; }
    /**
	 * Setting a components <code>setComposite</code> to 'true' will result in 
	 * THIS component getting picked and returned
	 * when a child of this component is picked. So this component sort of consumes all picking
	 * of its children.
	 * This behaviour is desireable if we have a component with children that should be treated 
	 * as one component as a whole by gestures etc.
	 * 
	 * @param composite the composite
	 */
    void setComposite(bool composite) { mComposite = composite; }
    void sendToFront();
    void sendChildToFront(GameObject *child);
    bool isPickable() { return mPickable; }
	void setPickable(bool pickable) { mPickable = pickable; }
    float pickRecursive(PickInfo &pickInfo, PickResult &pickResult, float currObjDist, Ray &currentRay, bool onlyPickables);
	bool processInputEvent(InputEvent &event);
    bool processGestureEvent(GestureEvent &ge);
    bool dispatchInputEvent(InputEvent &iEvt);
    std::pair<bool, Vector3> getIntersectionLocal(Ray& ray);
    std::pair<bool, Vector3> getIntersectionGlobal(Ray& ray);
    void addInputListener(IInputEventListener *inputListener){
//		if (inputListener instanceof AbstractComponentProcessor) {
//			logger.warn("An abstract component processor (" + inputListener + ") was added to component '" + this + "' using addInputListener(). You probably need to use the registerInputProcessor() method instead!");
//		}
//		this.inputListeners.add(inputListener);
        mInputListeners.push_back(inputListener);
	}
	
	/**
	 * Removes the input listener.
	 * @param inputListener the input listener
	 */
	void removeInputListener(IInputEventListener *inputListener){
//		this.inputListeners.remove(inputListener);
        for(std::list<IInputEventListener*>::iterator it = mInputListeners.begin(); it != mInputListeners.end(); it ++) {
            if(*it == inputListener) {
                mInputListeners.erase(it);
                break;
            }
        }
	}
	
	/**
	 * Gets the input listeners.
	 * @return the input listeners
	 */
//	public IInputEventListener[] getInputListeners(){
//		return this.inputListeners.toArray(new IInputEventListener[this.inputListeners.size()]);
//	}
    void registerInputProcessor(AbstractComponentProcessor *inputProcessor) {
//		AbstractComponentProcessor[] processors = inputProcessorsSupport.getInputProcessors();
//        for (AbstractComponentProcessor abstractComponentProcessor : processors) {
//            if (inputProcessor.getClass() == abstractComponentProcessor.getClass()) {
//                logger.warn("Warning: The same type of input processor (" + inputProcessor.getName() + ") is already registered at component: " + this);
//            }
//        }
		inputProcessorsSupport.registerInputProcessor(inputProcessor);
		setGestureAllowance(inputProcessor->getName(), true); //Enable by default
	}
	
	/**
	 * Unregister a component input processor.
	 * @param inputProcessor the input processor
	 */
	void unregisterInputProcessor(AbstractComponentProcessor *inputProcessor) {
		inputProcessorsSupport.unregisterInputProcessor(inputProcessor);
	}
	
	/**
	 * Unregister all previously registered component input processors.
	 */
	void unregisterAllInputProcessors() {
//		AbstractComponentProcessor[] ps = inputProcessorsSupport.getInputProcessors();
//        for (AbstractComponentProcessor p : ps) {
//            inputProcessorsSupport.unregisterInputProcessor(p);
//        }
        inputProcessorsSupport.clearInputProcessors();
	}
	
	/**
	 * Gets the component input processors.
	 * @return the input processors
	 */
//	AbstractComponentProcessor[] getInputProcessors() {
//		return inputProcessorsSupport.getInputProcessors();
//	}
    
    void addGestureListener(String gestureEvtSender, IGestureEventListener *listener){
		gestureEvtSupport.addGestureEvtListener(gestureEvtSender, listener);
	}
	
	/**
	 * Removes the gesture event listener.
	 * @param gestureEvtSender the gesture evt sender
	 * @param listener the listener
	 */
	void removeGestureEventListener(String gestureEvtSender, IGestureEventListener *listener) {
		gestureEvtSupport.removeGestureEventListener(gestureEvtSender, listener);
	}
	
	/**
	 * Removes the all gesture event listeners.
	 */
	void removeAllGestureEventListeners() {
		gestureEvtSupport.clearListeners();
	}
	
	/**
	 * Removes the all gesture event listeners who listen to the specified input processor.
	 * @param gestureEvtSender the gesture evt sender
	 */
	void removeAllGestureEventListeners(String gestureEvtSender) {
		gestureEvtSupport.removeAllGesturEventListeners(gestureEvtSender);
	}

    bool isGestureAllowed(String c){
//		return this.allowedGestures.contains(c);
        for(std::list<String>::iterator it = allowedGestures.begin(); it != allowedGestures.end(); it ++) {
            if(*it == c)
                return true;
        }
        return false;
	}
	
	/**
	 * Sets the gesture allowance. 
	 * @param c the gesture processors class
	 * @param allowed allowance
	 */
	void setGestureAllowance(String c, bool allowed){
//		if (allowed){
//			if (!this.allowedGestures.contains(c)){
//				this.allowedGestures.add(c);
//			}
//		}else{
//			if (this.allowedGestures.contains(c)){
//				this.allowedGestures.remove(c);
//			}
//		}
        if(allowed) {
            for(std::list<String>::iterator it = allowedGestures.begin(); it != allowedGestures.end(); it ++) {
                if(*it == c)
                    return ;
            }
            allowedGestures.push_back(c);
        }
        else {
            for(std::list<String>::iterator it = allowedGestures.begin(); it != allowedGestures.end(); it ++) {
                if(*it == c) {
                    allowedGestures.erase(it);
                    break;
                }
            }
        }
	}
	/**
	 * Returns the gesture listeners.
	 * @return the gesture listeners
	 */
//	IGestureEventListener[] getGestureListeners() {
//		return gestureEvtSupport.getListeners();
//	}
//	void updateAnimation();
//	Animation* getAnimation();
//	void startAnimation(Animation* animation);
//	void clearAnimation();
//	void setAnimation(Animation* animation);
//	bool drawAnimation(Transform* transform, long drawingTime, Animation& a, bool scalingRequired);

	GameObject * getChild(String name);
};

#endif
