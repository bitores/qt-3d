#ifndef __AndroidLogManager_h__
#define __AndroidLogManager_h__

#include "base/LogManager.h"
//#include "utils/include/Singleton.h"

class AndroidLogManager : public LogManager/*, Singleton<AndroidLogManager>*/
{
public:
	static void log(String format, ...);
	static void log(String tag, String format, ...);
//	void log(String tag, float value);
//	void log(String tag, int value);
//	void log(String tag, String value);

//	static AndroidLogManager& getSingleton();
//	static AndroidLogManager* getSingletonPtr();
};

#endif
