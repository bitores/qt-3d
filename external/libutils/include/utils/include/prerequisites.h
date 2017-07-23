#ifndef __prerequisites_h__
#define __prerequisites_h__

#pragma warning(disable: 4786)

#include <stdlib.h>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <list>
#include <set>
#include <deque>
#include <assert.h>

#include "platform.h"


// -------------------------------------------------------------------------------------------------------
// STL
using namespace std;

#ifdef _UNICODE
	typedef std::wstring ustring;
	typedef wchar_t* pstr;
	typedef const wchar_t* cpstr;
#define _gstr(x) L##x
#else
	typedef std::string ustring;
	typedef char* pstr;
	typedef const char* cpstr;
#define _gstr(x) x
#endif // _UNICODE

#define AUTO_DELETE(ptr) {if(ptr){delete ptr;(ptr)=NULL;} }
#define AUTO_DELETE_ARRAY(ptr) {if(ptr){delete[] ptr;(ptr)=NULL;} }


#if OGRE_WCHAR_T_STRINGS
	typedef std::wstring _StringBase;
#else
	typedef std::string _StringBase;
#endif

#if OGRE_WCHAR_T_STRINGS
	typedef std::basic_stringstream<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > _StringStreamBase;
#else
	typedef std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > _StringStreamBase;
#endif


//typedef std::string _StringBase;
typedef std::ostringstream _OStringBase;

#define HashMap std::map

typedef _StringBase String;
typedef _OStringBase OString;

typedef _StringStreamBase StringStream;
typedef StringStream stringstream;

typedef HashMap<String, String> NameValuePairList;
typedef HashMap<String, uint32> NameIDMap;

typedef float Real;

#pragma warning(disable: 4786)

#include "threading/ThreadDefines.h"
#include "MemoryAllocatorConfig.h"

// -------------------------------------------------------------------------------------------------------
//
class Root;
class SceneManager;
class RenderQueueListener;
class Timer;
class Camera;
class Frustum;
class Viewport;
class RenderTargetListener;
class RenderWindow;
class RenderTarget;
class GameObject;
class RenderQueue;
class Image;
class Archive;
class ArchiveManager;
class ArchiveFactory;
class Resource;
class ResourceManager;
class ScriptLoader;
class IDGenerator;
class NameGenerator;
class DepthBuffer;
class Codec;
class CodecManager;
class EncryptManager;
class ScriptEngineManager;
// -------------------------------------------------------------------------------------------------------
// hardware buffer
class VertexData;
class IndexData;
class VertexDeclaration;
class HardwareBufferManagerBase;
class HardwareBufferManager;
class DefaultHardwareBufferManager;
class HardwarePixelBuffer;
class HardwarePixelBufferSharedPtr;
class HardwareOcclusionQuery;
class RenderTexture;
class MultiRenderTarget;
class Texture;
// -------------------------------------------------------------------------------------------------------
// billboard & particle system
class Particle;
class ParticleVisualData;
class BillboardSet;
class Billboard;
class ParticleSystem;
class ParticleSystemListener;
class ParticleSystemManager;
class ParticleSystemRenderer;
class ParticleEmitter;
class ParticleAffector;
class ParticleAffectorFactory;
class ParticleEmitterFactory;
class ParticleSystemRendererFactory;

// -------------------------------------------------------------------------------------------------------
// controller
template <typename T> class Controller;
template <typename T> class ControllerFunction;
template <typename T> class ControllerValue;
class ControllerManager;

struct FrameEvent;
class FrameListener;

class IClickListener;
class ISurfaceTouchListener;

// -------------------------------------------------------------------------------------------------------
//
class Light;
class RenderFunction;
class MeshFilter;
class IMesh;
class Mesh;
class SubMesh;
class MeshManager;
class UIMeshManager;
class MeshMap;
class Pass;
class AutoParamDataSource;
class GpuProgram;
class GpuProgramUsage;
class Material;
class Pass;
class TextureUnitState;
class TextureManager;
class MaterialManager;
class FontManager;
class KeyFramesManager;
class HighLevelGpuProgram;
class HighLevelGpuProgramManager;
class GLSLLinkProgramManager;
class GLSLLinkProgram;
class GLSLProgram;

class LogManager;
class Transform;
class Renderer;
class Component;
class AxisAlignedBox;
class Ray;
// -------------------------------------------------------------------------------------------------------
// math
class Math;
class Radian;
class Degree;

class Quaternion;
class Vector2;
class Vector3;
class Vector4;
class Matrix4;
class Matrix3;
class PlaneBoundedVolume;
class Sphere;
class AxisAlignedBox;
// -------------------------------------------------------------------------------------------------------
// animation
class Runnable;
class Animation;
class AnimationSet;
class AnimationManager;

// -------------------------------------------------------------------------------------------------------
// UI
class Plane;
class eGallery;
class eScorePanel;
//class eBaseAdapter;
class eRect;
class eButton;
typedef std::list<GameObject*> HitResultList;
typedef std::vector<Light*> LightList;
typedef std::list<ParticleSystem*> ParticleSystemList;

// -------------------------------------------------------------------------------------------------------
// Compositor
class Compositor;
class CompositorChain;
class CompositorInstance;
class CompositorLogic;
class CompositorManager;
class CompositorPass;
class CompositorTargetPass;
class Rectangle2D;

// -------------------------------------------------------------------------------------------------------
template<typename T> class SharedPtr;

typedef SharedPtr<eRect> eRectPtr;
typedef SharedPtr<Texture> TexturePtr;
typedef SharedPtr<GpuProgram> GpuProgramPtr;
typedef SharedPtr<Compositor> CompositorPtr;
typedef SharedPtr<Material> MaterialPtr;
typedef SharedPtr<Mesh> MeshPtr;
typedef SharedPtr<HighLevelGpuProgram> HighLevelGpuProgramPtr;
typedef SharedPtr<Camera> CameraPtr;
typedef SharedPtr<Frustum> FrustumPtr;
typedef SharedPtr<Light> LightPtr;
// -------------------------------------------------------------------------------------------------------


// debug
#include "debug_flags.h"

#endif
