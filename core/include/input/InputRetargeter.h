#ifndef _INPUT_RETARGETER_H_
#define _INPUT_RETARGETER_H_
#include "utils/include/prerequisites.h"
#include "preinput.h"
#include "AbstractGlobalInputProcessor.h"

class InputRetargeter:public AbstractGlobalInputProcessor
{
	HashMap<InputCursor*, GameObject*> cursorToObjectMap;
	
	/** The app info provider. */
	IHitTestInfoProvider *appInfoProvider;
    
public:
	InputRetargeter(IHitTestInfoProvider *InfoProvider);
	~InputRetargeter();


	void processInputEvtImpl(InputEvent &inputEvent);



};


#endif /* _INPUT_RETARGETER_H_ */
