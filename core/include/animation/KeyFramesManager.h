#ifndef __KeyFramesManager_h__
#define __KeyFramesManager_h__

#include "utils/include/prerequisites.h"
//#include "base/Root.h"
#include "OGLES2Tools.h"
#include "io/DataStream.h"
#include "utils/include/String.h"
class KeyFramesManager
{
private:
	typedef map<String,float*> KeyFramesMap;
	KeyFramesMap mKeyFramesMap;
	Root *mRoot;
	bool readKeyFrame(Root *mRoot,DataStreamPtr &stream,const String & groupName,CSourceStream &src);

public:
	KeyFramesManager(Root *root);
	~KeyFramesManager();

    bool addKeyFrames(String name, float*data);

	float* findKeyFrames(String objName);

	//float* KeyFramesManager::findKeyFrames(char* objName)

	void releaseAllKeyFrames();

    void parseKeyFrames(const String & fileName,const String& groupName);
};
#endif
