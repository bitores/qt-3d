#ifndef __MaterialSerializerr__h__
#define __MaterialSerializerr__h__

#include "utils/include/String.h"
#include "base/Object.h"

/// Function def for material attribute parser; return value determines if the next line should be {
typedef bool (*ATTRIBUTE_PARSER)(String& params, Object* obj);

class MaterialSerializer
{
public:
	MaterialSerializer();
	~MaterialSerializer();

	bool invokeParser(Pass* pass, String name, String value);
	bool invokeParser(TextureUnitState* textureUnit, String name, String value);
protected:
	/// Keyword-mapped attribute parsers.
	typedef map<String, ATTRIBUTE_PARSER> AttribParserList;

	/// Parsers for the pass section of a script
	AttribParserList mPassAttribParsers;
	/// Parsers for the texture unit section of a script
	AttribParserList mTextureUnitAttribParsers;
private:

};
#endif