#ifndef _ComponentInputProcessorSupport_h_
#define _ComponentInputProcessorSupport_h_
#include "utils/include/prerequisites.h"
#include "preinput.h"

#include "IInputEventListener.h"
#include "base/Object.h"

class ComponentInputProcessorSupport:public IInputEventListener /*, IGestureEventListener*/ {
	
	/** The registered processors. */
//	private ArrayList<AbstractComponentProcessor> registeredProcessors;
    typedef std::list<AbstractComponentProcessor*> ProcessorList;
    ProcessorList registeredProcessors;
	
	/** The associated component. */
//	private MTComponent associatedComponent;
    Object *associatedComponent;
    
public:
    ComponentInputProcessorSupport() {}
	/**
	 * Instantiates a new component input processor support.
	 *
	 * @param graphicsContext the graphics context
	 * @param associatedComponent the associated component
	 */
	ComponentInputProcessorSupport(Object *Component) {
		associatedComponent = Component;
	}
    
    void setComponent(Object *obj) {
        associatedComponent = obj;
    }
	/* (non-Javadoc)
	 * @see org.mt4j.input.IMTInputEventListener#processInputEvent(org.mt4j.input.inputData.MTInputEvent)
	 */
	bool processInputEvent(InputEvent &inEvt);
	
	
	/**
	 * Register input processor.
	 *
	 * @param inputProcessor the input processor
	 */
	void registerInputProcessor(AbstractComponentProcessor *inputProcessor);
	
	/**
	 * Unregister input processor.
	 *
	 * @param inputProcessor the input processor
	 */
	void unregisterInputProcessor(AbstractComponentProcessor *inputProcessor);

    void clearInputProcessors();
	
	/**
	 * Gets the input processors.
	 *
	 * @return the input processors
	 */
//	public AbstractComponentProcessor[] getInputProcessors(){
//		return this.registeredProcessors.toArray(new AbstractComponentProcessor[this.registeredProcessors.size()]);
//	}
	
	

};



#endif /* _ComponentInputProcessorSupport_h_ */
