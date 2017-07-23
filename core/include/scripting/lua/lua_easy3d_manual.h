#ifndef LUA_EASY3D_MANUAL_H
#define LUA_EASY3D_MANUAL_H

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

#include "LuaScriptHandlerMgr.h"
#include "animation/Animation.h"
#include "scripting/lua/LuaValue.h"
#include "scripting/lua/LuaStack.h"
#include "base/ScriptSupport.h"
#include "scripting/lua/LuaEngine.h"
#include "scripting/lua/LuaScriptHandlerMgr.h"
#include "input/GestureEvent.h"
#include "input/TapEvent.h"
#include "input/ScaleEvent.h"
#include "input/RotateEvent.h"
#include "input/DragEvent.h"
#include "input/TapProcessor.h"
#include "input/ScaleProcessor.h"
#include "input/RotateProcessor.h"
#include "input/DragProcessor.h"
#include <typeinfo>
#include "particle/ParticleSystemRenderer.h"
#include "particle/ParticleSystem.h"
#include "rendersystem/MeshFilter.h"
#include "ui/eRect.h"
#include "rendersystem/MaterialManager.h"
#include "asset/MeshManager.h"
#include "base/FrameListener.h"
#include "rendersystem/Pass.h"


TOLUA_API int register_all_easy3d_manual(lua_State* tolua_S);

template <class T>
class LuaGestureEventListener: public IGestureEventListener
{
private:
	Root* mRoot;
public:
	LuaGestureEventListener(Root* root) {
		mRoot = root;
    }
    ~LuaGestureEventListener(){}

    bool processGestureEvent(GestureEvent &ge)
    {
    	 ((LuaEngine*)(mRoot->getScriptEngineManager()->getScriptEngine()))->handleGestureEvent(ge.getTarget(), (T&)ge);
		 return true;
    }
};


class LuaParticleSystemListener : public ParticleSystemListener
{
private:
	Root* mRoot;
public:
	LuaParticleSystemListener(Root* root){
		mRoot = root;
	}

	virtual void click(Object* sender)
	{
		((LuaEngine*)(mRoot->getScriptEngineManager()->getScriptEngine()))->handleOnParticleSystemClick(mRoot, sender);
	}

	virtual void onParticleSystemActive(ParticleSystem* sender)
	{
		((LuaEngine*)(mRoot->getScriptEngineManager()->getScriptEngine()))->handleOnParticleSystemActive(mRoot, sender);
	}

	virtual void onParticleSystemIdle(ParticleSystem* sender)
	{
		((LuaEngine*)(mRoot->getScriptEngineManager()->getScriptEngine()))->handleOnParticleSystemIdle(mRoot, sender);
	}

};


class LuaFrameListener : public FrameListener
{
private:
	Root* mRoot;
public:
	LuaFrameListener(Root* root){
		mRoot = root;
	}
	virtual bool frameStarted(const FrameEvent& evt)
	{
		((LuaEngine*)(mRoot->getScriptEngineManager()->getScriptEngine()))->handleOnFrameStart(mRoot, &evt);
		return true;
	}

	virtual bool frameRenderingQueued(const FrameEvent& evt)
	{
		((LuaEngine*)(mRoot->getScriptEngineManager()->getScriptEngine()))->handleOnFrameRenderingQueued(mRoot, &evt);
		return true;
	}

	virtual bool frameEnded(const FrameEvent& evt)
	{
		((LuaEngine*)(mRoot->getScriptEngineManager()->getScriptEngine()))->handleOnFrameEnded(mRoot, &evt);
		return true;
	}
};


#endif // LUA_EASY3D_MANUAL_H
