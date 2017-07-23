#ifndef __ScriptSupport_H__
#define __ScriptSupport_H__

#include "utils/include/prerequisites.h"
#include "utils/include/StringVector.h"
#include "utils/include/SharedPtr.h"
#include "base/Object.h"

typedef struct lua_State lua_State;

enum ScriptType {
    kScriptTypeNone = 0,
    kScriptTypeLua,
    kScriptTypeJavascript
};


//enum ScriptEventType
//{
//    kAnimationEvent = 0
//};
//
//struct ScriptEvent
//{
//    ScriptEventType type;
//    void* data;
//
//    // Constructor
//    /**
//     * @js NA
//     * @lua NA
//     */
//    ScriptEvent(ScriptEventType inType,void* inData)
//    : type(inType),
//      data(inData)
//    {
//    }
//};

class ScriptHandlerEntry : public SharedPtr<ScriptHandlerEntry>, public Object
{
public:
	ScriptHandlerEntry(ScriptEngineManager* sem, int handler);
    ~ScriptHandlerEntry(void);

    int getHandler(void) {
        return _handler;
    }

    int getEntryId(void) {
        return _entryId;
    }

protected:
    ScriptEngineManager* mScriptEngineManager;
    int _handler;
    int _entryId;
};


// Don't make ScriptEngineProtocol inherits from Object since setScriptEngine is invoked only once in AppDelegate.cpp,
// It will affect the lifecycle of ScriptCore instance, the autorelease pool will be destroyed before destructing ScriptCore.
// So a crash will appear on Win32 if you click the close button.
class ScriptEngineProtocol
{
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ScriptEngineProtocol() {};

    /** Get script type
     * @js NA
     * @lua NA
     */
    virtual ScriptType getScriptType() { return kScriptTypeNone; };

    /** Remove script object.
     * @js NA
     * @lua NA
     */
    virtual void removeScriptObjectByObject(Object* obj) = 0;

    /** Remove script function handler, only LuaEngine class need to implement this function.
     * @js NA
     * @lua NA
     */
    virtual void removeScriptHandler(int handler) {};

    /** Reallocate script function handler, only LuaEngine class need to implement this function.
     * @js NA
     * @lua NA
     */
    virtual int reallocateScriptHandler(int handler) { return 0;}

    /**
     @brief Execute script code contained in the given string.
     @param codes holding the valid script code that should be executed.
     @return 0 if the string is executed correctly.
     @return other if the string is executed wrongly.
     * @js NA
     * @lua NA
     */
    virtual int executeString(const char* codes) = 0;

    /**
     @brief Execute a script file.
     @param filename String object holding the filename of the script file that is to be executed
     * @js NA
     * @lua NA
     */
    virtual int executeScriptFile(const char* filename) = 0;

    /**
     @brief Execute a scripted global function.
     @brief The function should not take any parameters and should return an integer.
     @param functionName String object holding the name of the function, in the global script environment, that is to be executed.
     @return The integer value returned from the script function.
     * @js NA
     * @lua NA
     */
    virtual int executeGlobalFunction(const char* functionName) = 0;

    /**when trigger a script event ,call this func,add params needed into ScriptEvent object.nativeObject is object triggering the event, can be nullptr in lua
     * @js NA
     * @lua NA
     */
//    virtual int sendEvent(ScriptEvent* evt) = 0;

    /** called by CCAssert to allow scripting engine to handle failed assertions
     * @return true if the assert was handled by the script engine, false otherwise.
     * @js NA
     * @lua NA
     */
    virtual bool handleAssert(const char *msg) = 0;

    enum ConfigType
    {
        NONE,
        COCOSTUDIO
    };
    /** Parse configuration file */
    virtual bool parseConfig(ConfigType type, const std::string& str) = 0;
};

/**
 ScriptEngineManager is a singleton which holds an object instance of ScriptEngineProtocl
 It helps cocos2d-x and the user code to find back LuaEngine object
 @since v0.99.5-x-0.8.5
 */
class ScriptEngineManager
{
public:
	ScriptEngineManager(Root* root);

    ~ScriptEngineManager(void);
    /**
     * @js NA
     * @lua NA
     */
    ScriptEngineProtocol* getScriptEngine(void) {
        return _scriptEngine;
    }
    /**
     * @js NA
     * @lua NA
     */
    void setScriptEngine(ScriptEngineProtocol *scriptEngine);
    /**
     * @js NA
     * @lua NA
     */
    void removeScriptEngine(void);
//    /**
//     * @js NA
//     * @lua NA
//     */
//    static ScriptEngineManager* getInstance();
//    /**
//     * @js NA
//     * @lua NA
//     */
//    static void destroyInstance();
//    /**
//     * @js NA
//     * @lua NA
//     */
//    static ScriptEngineManager* sharedManager() { return ScriptEngineManager::getInstance(); };
//    /**
//     * @js NA
//     * @lua NA
//     */
//    static void purgeSharedManager() { ScriptEngineManager::destroyInstance(); };


private:
    Root* mRoot;
    ScriptEngineProtocol *_scriptEngine;
};


#endif
