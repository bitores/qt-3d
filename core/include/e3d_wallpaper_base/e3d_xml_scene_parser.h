#ifndef _E3D_XML_SCENE_PARSER_H_
#define _E3D_XML_SCENE_PARSER_H_

#include "e3d_xml_parser_base.h"
#include "utils/include/String.h"
#include "utils/include/BlendMode.h"

class TextureUnitState;

class xml_scene_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_camera_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_viewport_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_render_target_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_light_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_ambient_light_parser: public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_texture_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};
class xml_font_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};
class xml_program_parser : public xml_parser_base
{
protected:
	int mType;
public:
	xml_program_parser(int type) { mType = type; }

	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

//class xml_vertex_program_parser : public xml_program_parser
//{
//public:
//	xml_vertex_program_parser();
//};
//
//class xml_fragment_program_parser : public xml_program_parser
//{
//public:
//	xml_fragment_program_parser();
//};

class xml_default_params_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_material_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_pass_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_texture_unit_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_TexCoordModifierAnimation_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_TexAlphaModifierAnimation_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_TexCoordSetAnimation_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_wave_xform_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_eRect_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_TextAreaOverlayElement_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_emesh_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_obj_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_particle_system_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_sky_dome_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

//class xml_pack_parser : public xml_parser_base
//{
//public:
//	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );
//
//	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
//};

class xml_gameobject_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_transform_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_renderer_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_meshfilter_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_auto_layout_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_animation_set_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_rotate_animation_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_translate_animation_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_sequence_frame_animation_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_scale_animation_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_event_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_eButton_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_eRectDataSource_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_eGallery_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

// begin : compositor relevant parsers
class xml_compositors_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_compositor_ref_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_compositor_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};


class xml_compositor_textures_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_compositor_texture_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_compositor_texture_ref_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_compositor_target_pass_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_compositor_pass_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_compositor_input_texture_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};
// end : compositor relevant parsers

class xml_lua_parser : public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_keyframes_parser:public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_kfTranslate_parser:public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_kfRotate_parser:public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};

class xml_kfScale_parser:public xml_parser_base
{
public:
	virtual object_base* forward_parse( TiXmlNode *v_xml_node, object_base *parent_object );

	virtual TiXmlNode*   backward_parse( object_base* ret_object, TiXmlNode* parent_node ) { return NULL; }
};
#endif // _E3D_XML_SCENE_PARSER_H_
