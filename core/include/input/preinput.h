#ifndef _PRE_INPUT_DEFINE_H_
#define _PRE_INPUT_DEFINE_H_
#include "utils/include/debug_flags.h"


#if defined(_DEBUG_INPUT_)
#include "base/LogManager.h"
#define logprint(tag, info, args...) LogManager::log(tag, info, ##args)
#else
#define logprint(tag, info, ...)
#endif


class Event;
class InputEvent;
class AbstractCursorInputEvt;
class GestureEvent;
class TapEvent;

class IInputProcessor;
class AbstractGlobalInputProcessor;
class AbstractComponentProcessor;
class ComponentInputProcessorSupport;
class AbstractCursorProcessor;
class InputRetargeter;
class TapProcessor;

class InputCursor;

class AbstractInputSource;
class GestureEventSupport;

class IInputSourceListener;
class IInputEventListener;
class IGestureEventListener;

class IHitTestInfoProvider;

class ISurfaceTouchListener;
class InputManager;

class PickInfo;
class PickResult;
class PickEntry;


#endif /* _PRE_INPUT_DEFINE_H_ */
