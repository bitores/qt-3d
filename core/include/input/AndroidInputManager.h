#ifndef _ANDROID_INPUT_MANAGER_H_
#define _ANDROID_INPUT_MANAGER_H_
#include "utils/include/prerequisites.h"
#include "preinput.h"
//#include "InputManager.h"
//#include "AndroidInputSource.h"

class AndroidInputManager:public InputManager {

public:
    AndroidInputManager(Root *root):InputManager(root) {
	}
	
    AndroidInputManager(Root *root, bool registerDefaultSources):InputManager(root, registerDefaultSources){
	}

protected:
    void registerDefaultInputSources() {
		registerInputSource(new AndroidInputSource(mRoot);	
	}

};


#endif /* _ANDROID_INPUT_MANAGER_H_ */