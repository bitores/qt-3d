#ifndef _MeshParser_H_
#define _MeshParser_H_

#include "utils/include/prerequisites.h"
#include "io/DataStream.h"
#include "OGLES2Tools.h"
#include "utils/include/Timer.h"
class MeshParser/* : public IAssetParser*/
{
public:
	MeshParser();
	~MeshParser();
	void exportMesh(Root* mRoot, DataStreamPtr stream, const String& groupName);
	void exportMeshV2(Root* mRoot, DataStreamPtr stream, const String& groupName);
	void exportPodMesh(Root*mRoot, DataStreamPtr &stream,const String& groupName);
	bool readMesh(Root *mRoot,DataStreamPtr &stream,const String & groupName,CSourceStream &src);
	bool isEqual(const String& str1,const String & str2);
//	IAsset* parse(AssetInfo* pAssetInfo);

protected:
	//!	Data buffer
//	std::vector<char> m_Buffer;
//	void parserFile(String &strModelName);
//	void CreateDataFromImport(const ObjFile::Model* pModel, eMeshMap *pMeshMap);
//
//	void TextFileToBuffer(const char* zipDir, const char* filePath);
//	void TextFileToBuffer(const char* assetPath);
};

#endif
