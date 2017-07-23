#ifndef _Easy3dWallpaperJni_h__
#define _Easy3dWallpaperJni_h__

#include <jni.h>
#include "utils/include/prerequisites.h"

//#define	_DEBUG_BASE_JNI_
#define	BASE_JNI_TAG			"tag_base_jni"
class E3dWallpaperBase;

// ------------------------------------------------------------------------------------------------------------
typedef int (*regfunc)(JNIEnv*);
struct RegistrationMethod {
    const char* name;
//    int (*func)(JNIEnv*);
    regfunc func;
    RegistrationMethod(const char*_name, regfunc _func) {
    	name = _name;
    	func = _func;
    }
};

jint E3dBase_JNI_Registration(JavaVM* vm, std::list<RegistrationMethod> & methodList);
void surfaceCreated(JNIEnv * env, jobject obj, E3dWallpaperBase* pE3d/*, bool isWallpaper, jstring jZipDir, jstring jFilepath*/);
// ------------------------------------------------------------------------------------------------------------

//static std::list<JNINativeMethod> gEasy3dWallpaperJNINativeMethodList;
//int register_scenes(JNIEnv* env);
//int registerNatives(JNIEnv* env, JNINativeMethod* methods);
int registerNativeMethods(JNIEnv* env, const char* className, JNINativeMethod* gMethods, int numMethods);

//namespace android {

//static std::list<RegistrationMethod> gEasy3dBaseRegistrationMethodList;

// A helper class that automatically deletes the local reference to the jobject
// returned from getRealObject.
class AutoJObject {
public:
    ~AutoJObject() {
        if (m_obj)
            m_env->DeleteLocalRef(m_obj);
    }
    jobject get() const {
        return m_obj;
    }
    // Releases the local reference to the caller. The caller *must* delete the
    // local reference when it is done with it.
    jobject release() {
        jobject obj = m_obj;
        m_obj = 0;
        return obj;
    }
    JNIEnv* env() const {
        return m_env;
    }
private:
    AutoJObject(JNIEnv* env, jobject obj)
        : m_env(env)
        , m_obj(obj) {}
    JNIEnv* m_env;
    jobject m_obj;
    friend AutoJObject getRealObject(JNIEnv*, jobject);
};

// Get the real object stored in the weak reference returned as an
// AutoJObject.
AutoJObject getRealObject(JNIEnv*, jobject);

// Helper method for check java exceptions. Returns true if an exception
// occurred and logs the exception.
bool checkException(JNIEnv* env);

// Create a String object from a jstring object.
String to_string(JNIEnv* env, jstring str);

//}

#endif
