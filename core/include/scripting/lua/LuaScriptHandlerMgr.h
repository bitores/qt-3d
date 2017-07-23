/****************************************************************************
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
#ifndef __LUA_SCRIPT_HANDLER_MGR_H__
#define __LUA_SCRIPT_HANDLER_MGR_H__


extern "C" {
#include "tolua++.h"
}

//#include "Object.h"
#include <vector>
#include <map>
#include "base/Root.h"

#include "input/AbstractCursorProcessor.h"

#include "scripting/lua/lua_easy3d_manual.h"
#include "particle/ParticleSystemRenderer.h"
#include "scripting/lua/LuaEngine.h"

//class LuaEngine;
class LuaParticleSystemListener;
class LuaFrameListener;
//class ScheduleHandlerDelegate;
//
//typedef std::vector<ScheduleHandlerDelegate*> VecShedule;
////typedef std::map<Node*,VecShedule> MapNodeSchedules;
//
//class ScheduleHandlerDelegate:public Object
//{
//public:
//    ScheduleHandlerDelegate():_isUpdateSchedule(false)
//    {}
//    virtual ~ScheduleHandlerDelegate()
//    {}
//
//    static ScheduleHandlerDelegate* create();
//
//    void scheduleFunc(float elapse);
//
//    virtual void update(float elapse);
//
//    void setUpdateSchedule(bool isUpdateSchedule){ _isUpdateSchedule = isUpdateSchedule; }
//    bool isUpdateSchedule(){ return _isUpdateSchedule; }
//private:
//    bool _isUpdateSchedule;
//};
//
//class LuaCallFunc : public CallFuncN
//{
//public:
//    LuaCallFunc():_functionLua(nullptr)
//    {}
//    virtual ~LuaCallFunc()
//    {}
//    
//    static LuaCallFunc* create(const std::function<void(void* self,Node*)>& func);
//    bool initWithFunction(const std::function<void(void* self,Node*)>& func);
//    virtual LuaCallFunc* clone() const;
//    virtual void execute() override;
//protected:
//    /**
//     */
//    std::function<void(void* self,Node*)> _functionLua;
//    
//};

class ScriptHandlerMgr
{
public:
    enum /*class */HandlerType/*: int*/
    {
        NODE = 0,

        ON_POST_CREATE_SCENE,
        ON_PREPARE_SCENE_DATA,
        ON_OFFSETS_CHANGED,
        ON_STOP,
        ON_SIZE,

        ON_ANIMATION_START,
        ON_ANIMATION_REPEAT,
        ON_ANIMATION_END,
        ON_ANIMATION_PROGRESS,

        ON_TAP_GESTURE,
        ON_SCALE_GESTURE,
        ON_ROTATE_GESTURE,
        ON_DRAG_GESTURE,

        ON_PARTICLE_SYSTEM_CLICK,
        ON_PARTICLE_SYSTEM_ACTIVE,
        ON_PARTICLE_SYSTEM_IDLE,
        ON_PARTICLE_SYSTEM_CREATED,

        ON_FRAME_START,
        ON_FRAME_RENDERING_QUEUED,
        ON_FRAME_ENDED

    };


    ScriptHandlerMgr(LuaEngine *luaEngine, Root* root);
    virtual ~ScriptHandlerMgr(void);
//    static ScriptHandlerMgr* getInstance(void);

    // normal handlers
    typedef int Handler;
	typedef std::pair<HandlerType, Handler> HandlerPair;
	typedef std::vector<HandlerPair> VecHandlerPairs;
	typedef std::map<void*,VecHandlerPairs> MapObjectHandlers;
    void addObjectHandler(void* object,int handler,ScriptHandlerMgr::HandlerType handlerType);
    void removeObjectHandler(void* object,ScriptHandlerMgr::HandlerType handlerType);
    int  getObjectHandler(void* object,ScriptHandlerMgr::HandlerType handlerType);
    void removeObjectAllHandlers(void* object);
    void removeAllHandlers();
    
    // manage gesture event listener handler
    typedef std::pair<String, IGestureEventListener*> GestureListenerPair;
	typedef std::vector<GestureListenerPair> VecGestureListenerPairs;
	typedef std::map<void*,VecGestureListenerPairs> MapObjectGestureListeners;
    void addObjectGestureListener(void* object, IGestureEventListener* listener, String processorTypeName);
    void removeObjectGestureListener(void* object, String processorTypeName);
    IGestureEventListener* getObjectGestureListener(void* object, String processorTypeName);
    void removeObjectAllGestureListeners(void* object);
    void removeAllGestureListeners();

    // manage input processor
    typedef std::pair<String, AbstractCursorProcessor*> ProcessorPair;
	typedef std::vector<ProcessorPair> VecProcessorPairs;
	typedef std::map<void*,VecProcessorPairs> MapObjectProcessors;
    void addObjectProcessor(void* object, AbstractCursorProcessor* inputProcessor, String processorTypeName);
    void removeObjectProcessor(void* object, String processorTypeName);
    AbstractCursorProcessor* getObjectProcessor(void* object, String processorTypeName);
    void removeObjectAllProcessors(void* object);
    void removeAllProcessors();


    void setLuaParticleSystemListenerEnabled(bool bEnabled);

    void setLuaFrameListenerEnabled(bool bEnabled);

private:
    void init(void);
    Root* mRoot;
//    static ScriptHandlerMgr* _scriptHandlerMgr;
    LuaEngine* mLuaEngine;


    MapObjectHandlers _mapObjectHandlers;
    MapObjectGestureListeners _mapObjectGestureListeners;
    MapObjectProcessors _mapObjectProcessors;
    LuaParticleSystemListener* _particleSystemListener;

    LuaFrameListener*	_luaFrameListener;



};





TOLUA_API int tolua_script_handler_mgr_open(lua_State* tolua_S);

#endif //__LUA_SCRIPT_HANDLER_MGR_H__
