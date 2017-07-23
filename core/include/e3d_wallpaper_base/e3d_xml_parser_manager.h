#ifndef _E3D_XML_PARSER_MANAGER_H_
#define _E3D_XML_PARSER_MANAGER_H_

#include "utils/include/prerequisites.h"
//#include "parser/IAssetParser.h"
#include "base/ScriptLoader.h"

class xml_parser_base;
class xml_parser_manager : public ScriptLoader
{
public:
	Root* mRoot;
	String mGroupName;
public:
//	IAsset* parse(AssetInfo* pAssetInfo);

	const StringVector& getScriptPatterns(void) const { return mScriptPatterns; }

	void parseScript(DataStreamPtr& stream, const String& groupName);

	virtual Real getLoadingOrder(void) const { return 0; }

	xml_parser_manager(Root* root);
	virtual ~xml_parser_manager(void);

	typedef std::map<ustring, xml_parser_base*> xml_parser_map;

public:
	xml_parser_base* get_parser ( cpstr str_key );
	
	void register_parser( cpstr str_key, xml_parser_base* v_parser );

protected:
	xml_parser_map m_parser_map;
	/// Patterns to use to look for scripts if supported (e.g. *.overlay)
	StringVector mScriptPatterns;
};

#endif // _E3D_XML_PARSER_MANAGER_H_
