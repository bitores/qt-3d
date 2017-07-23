#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

#include "utils/include/prerequisites.h"
#include "preinput.h"

//#include "input/AbstractInputSource.h"
//#include "input/AbstractGlobalInputProcessor.h"
#include "ISurfaceTouchListener.h"
/**
 * Manages the InputSources and Inputprocessors for each scene.
 * Starts up the default input sources.
 *
 * @author Christopher Ruff
 */
class InputManager:public ISurfaceTouchListener
{

protected:
    /** The root. */
    Root* mRoot;
    
    /** The registered input sources. */
    typedef std::list<AbstractInputSource*> AbstractInputSourceList;
    AbstractInputSourceList mRegisteredInputSources;

    /** The In processor to scene. */
    typedef HashMap<AbstractGlobalInputProcessor*, SceneManager*> InputProcessorMap;
    InputProcessorMap mInputProcessorsToScene;

    typedef std::list<AbstractGlobalInputProcessor*> InputProcessorList;

public:
    /**
     * Instantiates a new input manager.
     *
     * @param pa the processing context
     */
    InputManager(Root *root, bool registerDefaultSources = true);

    ~InputManager();

    void destroyAllInput();
    /**
     * Registers a new input source for the application.
     *
     * @param newInputSource the new input source
     */
    void registerInputSource(AbstractInputSource *newInputSource);

    /**
     * Unregisters a input source.
     * @param is the input source
     */
    void unregisterInputSource(AbstractInputSource *inputSource);

    /**
     * Gets the input sources.
     * @return the input sources
     */
//    AbstractInputSource[] getInputSources();

    /**
     * Gets the registered input sources.
     *
     * @return the registered input sources
     * @deprecated use getInputSources() instead
     */
//    Collection<AbstractInputSource> getRegisteredInputSources();

    /**
     * Registers a new inputprocessor and adds it to the inputsources as listeners.
     *
     * @param scene the scene
     * @param inputprocessor the input processor
     */
    void registerGlobalInputProcessor(SceneManager *sceneMgr, AbstractGlobalInputProcessor *inputprocessor);

    /**
     * Unregisters a inputprocessor from _all_ the registered inputsources.
     *
     * @param inputprocessor the input processor
     */
    void unregisterGlobalInputProcessor(AbstractGlobalInputProcessor *inputprocessor);

    /**
     * Gets the global inputprocessors associated with the specified scene.
     *
     * @param scene the scene
     *
     * @return the scene inputprocessors
     */
    InputProcessorList getGlobalInputProcessors(SceneManager *sceneMgr);

    /**
     * Enables the global inputprocessors that are associated with the given scene.
     *
     * @param scene the scene
     */
    void enableGlobalInputProcessors(SceneManager *sceneMgr);

    /**
     * Disables the global inputprocessors that are associated with the given scene.
     *
     * @param scene the scene
     */
    void disableGlobalInputProcessors(SceneManager *sceneMgr);

    /**
     * Removes input processors of the specified scene from listening to the registered input sources.
     *
     * @param scene the scene
     */
    void removeGlobalInputProcessors(SceneManager *sceneMgr);

    bool onTouchEvent(int action, int id, float x, float y);
protected:
    /**
     * Initialize default input sources.
     */
    virtual void registerDefaultInputSources();
private:

    void saveAddInputListenerToSource(AbstractInputSource *source, AbstractGlobalInputProcessor *inputprocessor);

};

#endif /* _INPUT_MANAGER_H_ */
