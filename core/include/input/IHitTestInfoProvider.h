#ifndef _HITTEST_INFO_PROVIDER_H_
#define _HITTEST_INFO_PROVIDER_H_
#include "utils/include/prerequisites.h"
#include "preinput.h"
class IHitTestInfoProvider {
public:
	/**
	 * Gets the object at.
	 * 
	 * @param x the x
	 * @param y the y
	 * 
	 * @return the object at
	 */
	virtual GameObject* getComponentAt(float x, float y) = 0;
	
	/**
	 * Checks if is back ground at.
	 * 
	 * @param x the x
	 * @param y the y
	 * 
	 * @return true, if is back ground at
	 */
	bool isBackGroundAt(float x, float y);

};


#endif /* _HITTEST_INFO_PROVIDER_H_ */