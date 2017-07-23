#ifndef _ANDROID_INPUTSOURCE_H_
#define _ANDROID_INPUTSOURCE_H_
#include "utils/include/prerequisites.h"
#include "preinput.h"
//#include "ISurfaceTouchListener.h"
//#include "AbstractInputSource.h"

class AndroidInputSource: public AbstractInputSource 
{

public:
    AndroidInputSource(Root *root):AbstractInputSource(root) {
		
//		this.idToCursorID = new HashMap<Long, Long>();
	}
	
		
};


#endif /* _ANDROID_INPUTSOURCE_H_ */