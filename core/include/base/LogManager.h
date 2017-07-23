#ifndef __LogManager_h__
#define __LogManager_h__

#include "utils/include/prerequisites.h"
//#include "utils/include/Singleton.h"
#define _LINUX_

#ifdef _LINUX_
#include <stdio.h>
#include <stdarg.h>
#else
#include <android/log.h>
#endif

class LogManager//: public Singleton<LogManager>
{
public:
//	virtual void log(char* tag, char* format, ...) = 0;
	static void log(String format, ...)
	{
		String tag = "easy3d_log";
		const char* fmt = format.c_str();
		const char* t = tag.c_str();

		char buffer[512];
		va_list args;
		va_start(args, format);
		vsprintf(buffer, fmt, args);
		va_end(args);
#ifdef _LINUX_
		printf(format.c_str(), args);
#else
		__android_log_print(ANDROID_LOG_INFO, t, buffer);
#endif
	}
	static void logMessage(String format, ...)
	{
		String tag = "easy3d_log";
		const char* fmt = format.c_str();
		const char* t = tag.c_str();

		char buffer[512];
		va_list args;
		va_start(args, format);
		vsprintf(buffer, fmt, args);
		va_end(args);
#ifdef _LINUX_
		printf(format.c_str(), args);
#else
		__android_log_print(ANDROID_LOG_INFO, t, buffer);
#endif
	}
	static void log(String tag, String format, ...)
	{
	//	const char* f = format.c_str();
	//	const char* t = tag.c_str();
	//	va_list args;
	//	va_start(args, format);
	//	__android_log_print(ANDROID_LOG_INFO, t, f, args);
	//	va_end(args);

		const char* fmt = format.c_str();
		const char* t = tag.c_str();

		char buffer[512];
		va_list args;
		va_start(args, format);
		vsprintf(buffer, fmt, args);
		va_end(args);
#ifdef _LINUX_
		printf(format.c_str(), args);
#else
		__android_log_print(ANDROID_LOG_INFO, t, buffer);
#endif
	}

//	virtual void log(String tag, float value) = 0;
//	virtual void log(String tag, int value) = 0;
//	virtual void log(String tag, String value) = 0;

//public:
//	static LogManager& getSingleton();
//	static LogManager* getSingletonPtr();

};

//LogManager* LogManager::getSingletonPtr(void) {
//	return ms_Singleton;
//}
//
//LogManager& LogManager::getSingleton(void) {
//	assert(ms_Singleton);
//	return (*ms_Singleton);
//}

#endif
