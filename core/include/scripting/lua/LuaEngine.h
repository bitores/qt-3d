/****************************************************************************
 Copyright (c) 2012      cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __CC_LUA_ENGINE_H__
#define __CC_LUA_ENGINE_H__

extern "C" {
#include "lua.h"
}

#include "base/ScriptSupport.h"
#include "LuaStack.h"
#include "LuaValue.h"

#include "input/TapEvent.h"
#include "input/ScaleEvent.h"
#include "input/RotateEvent.h"
#include "input/DragEvent.h"

class ScriptHandlerMgr;


class LuaEngine : public ScriptEngineProtocol
{
public:
//    static LuaEngine* getInstance(void);
//    static LuaEngine* defaultEngine(void) { return LuaEngine::getInstance(); }
    LuaEngine(Root* root);
    virtual ~LuaEngine(void);
    
    virtual ScriptType getScriptType() {
        return kScriptTypeLua;
    };

    LuaStack *getLuaStack(void) {
        return _stack;
    }
    
    ScriptHandlerMgr* getScriptHandlerMgr() {
    	return _scriptHandlerMgr;
    }


    // used to switch scene
    void destroyResources();

    /**
     @brief Add a path to find lua files in
     @param path to be added to the Lua path
     */
    virtual void addSearchPath(const char* path);
    
    /**
     @brief Add lua loader, now it is used on android
     */
    virtual void addLuaLoader(lua_CFunction func);
    
    /**
     @brief Remove Object from lua state
     @param object to remove
     */
    virtual void removeScriptObjectByObject(Object* object);
    
    /**
     @brief Remove Lua function reference
     */
    virtual void removeScriptHandler(int nHandler);
    
    /**
     @brief Reallocate Lua function reference
     */
    virtual int reallocateScriptHandler(int nHandler);
    
    /**
     @brief Execute script code contained in the given string.
     @param codes holding the valid script code that should be executed.
     @return 0 if the string is excuted correctly.
     @return other if the string is excuted wrongly.
     */
    virtual int executeString(const char* codes);
    
    /**
     @brief Execute a script file.
     @param filename String object holding the filename of the script file that is to be executed
     */
    virtual int executeScriptFile(const char* filename);
    
    /**
     @brief Execute a scripted global function.
     @brief The function should not take any parameters and should return an integer.
     @param functionName String object holding the name of the function, in the global script environment, that is to be executed.
     @return The integer value returned from the script function.
     */
    virtual int executeGlobalFunction(const char* functionName);

    //virtual int executeNodeEvent(Node* pNode, int nAction);
    //virtual int executeMenuItemEvent(MenuItem* pMenuItem);
    //virtual int executeNotificationEvent(NotificationCenter* pNotificationCenter, const char* pszName);
    //virtual int executeCallFuncActionEvent(CallFunc* pAction, Object* pTarget = NULL);
    //virtual int executeSchedule(int nHandler, float dt, Node* pNode = NULL);
    //virtual int executeLayerTouchesEvent(Layer* pLayer, int eventType, Set *pTouches);
    //virtual int executeLayerTouchEvent(Layer* pLayer, int eventType, Touch *pTouch);
    //virtual int executeLayerKeypadEvent(Layer* pLayer, int eventType);
    ///** execute a accelerometer event */
    //virtual int executeAccelerometerEvent(Layer* pLayer, Acceleration* pAccelerationValue);
    virtual int executeEvent(int nHandler, const char* pEventName, Object* pEventSource = NULL, const char* pEventSourceClassName = NULL);

    virtual bool handleAssert(const char *msg);
    
    virtual bool parseConfig(ConfigType type, const std::string& str);
//    virtual int sendEvent(ScriptEvent* message);
//    virtual int handleEvent(ScriptHandlerMgr::HandlerType type,void* data);
//    virtual int handleEvent(ScriptHandlerMgr::HandlerType type, void* data, int numResults, const std::function<void(lua_State*,int)>& func);


    // add by jin
//    virtual int executePrepareSceneData();
//	virtual int executePrevCreateScene();
//	virtual int executePostCreateScene();
//	virtual int executeOnTouchEvent(int action, float x, float y);
//	virtual int executeOnOffsetsChanged(float xOffset, float yOffset, float xStep, float yStep, int xPixels, int yPixels);
//	virtual int executeOnStop(bool beStop);
//	virtual int executeOnSize(Real w, Real h);

    // scene events
	int handlePrepareSceneDataEvent(void* object);
	int handlePostCreateSceneEvent(void* object);
	int handleOnOffsetsChangedEvent(void* object, float xOffset, float yOffset, float xStep, float yStep, int xPixels, int yPixels);
	int handleOnStopEvent(void* object, bool beStop);
	int handleOnSizeEvent(void* object, Real w, Real h);
	int handleOnTouchEvent(void* object, int action, int id, float x, float y);

	// animation events
	int handleOnAnimationStartEvent(void* object);
	int handleOnAnimationRepeatEvent(void* object);
	int handleOnAnimationEndEvent(void* object);
	int handleOnAnimationProgressEvent(void* object, float progress);

	// gesture events
	int handleGestureEvent(void* object, TapEvent& ge);
	int handleGestureEvent(void* object, ScaleEvent& ge);
	int handleGestureEvent(void* object, RotateEvent& ge);
	int handleGestureEvent(void* object, DragEvent& ge);

	// particle system listener
	int handleOnParticleSystemClick(void* object, Object* sender);
	int handleOnParticleSystemActive(void* object, ParticleSystem* sender);
	int handleOnParticleSystemIdle(void* object, ParticleSystem* sender);

	// frame listener
	int handleOnFrameStart(void* object, const FrameEvent* evt);
	int handleOnFrameRenderingQueued(void* object, const FrameEvent* evt);
	int handleOnFrameEnded(void* object, const FrameEvent* evt);

private:
    bool init(void);
//    int handleNodeEvent(void* data);
//    int handleMenuClickedEvent(void* data);
//    int handleCallFuncActionEvent(void* data);
//    int handleScheduler(void* data);
//    int handleKeypadEvent(void* data);
//    int handleAccelerometerEvent(void* data);
//    int handleCommonEvent(void* data);
//    int handleTouchEvent(void* data);
//    int handleTouchesEvent(void* data);
//    int handlerControlEvent(void* data);
//    int handleEvenCustom(void* data);
//    int handleAssetsManagerEvent(ScriptHandlerMgr::HandlerType type,void* data);
//    int handleTableViewEvent(ScriptHandlerMgr::HandlerType type,void* data);
//    int handleTableViewEvent(ScriptHandlerMgr::HandlerType type,void* data, int numResults, const std::function<void(lua_State*,int)>& func);
//    int handleStudioEventListener(ScriptHandlerMgr::HandlerType type,void* data);
//    int handleArmatureWrapper(ScriptHandlerMgr::HandlerType type,void* data);
//    int handleEventAcc(void* data);
//    int handleEventKeyboard(ScriptHandlerMgr::HandlerType type,void* data);
//    int handleEventTouch(ScriptHandlerMgr::HandlerType type, void* data);
//    int handleEventTouches(ScriptHandlerMgr::HandlerType type, void* data);
//    int handleEventMouse(ScriptHandlerMgr::HandlerType type, void* data);
    
public:
    void setScriptEntryFile(String scriptEntryFile);
    String getScriptEntryFile();

private:
    Root* mRoot;

//    static LuaEngine* _defaultEngine;
    LuaStack *_stack;
    ScriptHandlerMgr* _scriptHandlerMgr;


    String _scriptEntryFile;
    bool _bScriptExists;
};

#endif // __CC_LUA_ENGINE_H__
