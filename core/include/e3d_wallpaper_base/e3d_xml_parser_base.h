#ifndef _E3D_XML_PARSER_BASE_H_
#define _E3D_XML_PARSER_BASE_H_

#include "base/Object.h"
#include "external/tiny_xml/tinyxml.h"

class xml_parser_manager;

class xml_parser_base
{
public:
	xml_parser_base( void );

	virtual ~xml_parser_base( void );

public:
	virtual object_base* forward_parse( TiXmlNode* v_xml_node, object_base* parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node );

	void set_manager( xml_parser_manager* mngr );

protected:
	xml_parser_manager* m_parser_mngr;
};

#endif // _E3D_XML_PARSER_BASE_H_
