#ifndef __Common_H__
#define __Common_H__

/** An enumeration describing which material properties should track the vertex colours */
typedef int TrackVertexColourType;
enum TrackVertexColourEnum {
	TVC_NONE        = 0x0,
	TVC_AMBIENT     = 0x1,
	TVC_DIFFUSE     = 0x2,
	TVC_SPECULAR    = 0x4,
	TVC_EMISSIVE    = 0x8
};

/** Sort mode for billboard-set and particle-system */
enum SortMode
{
	/** Sort by direction of the camera */
	SM_DIRECTION,
	/** Sort by distance from the camera */
	SM_DISTANCE
};

/** Defines the frame buffer types. */
enum FrameBufferType {
	FBT_COLOUR  = 0x1,
	FBT_DEPTH   = 0x2,
	FBT_STENCIL = 0x4
};

/** Comparison functions used for the depth/stencil buffer operations and
	others. */
enum CompareFunction
{
    CMPF_ALWAYS_FAIL,
    CMPF_ALWAYS_PASS,
    CMPF_LESS,
    CMPF_LESS_EQUAL,
    CMPF_EQUAL,
    CMPF_NOT_EQUAL,
    CMPF_GREATER_EQUAL,
    CMPF_GREATER
};

/** High-level filtering options providing shortcuts to settings the
    minification, magnification and mip filters. */
enum TextureFilterOptions
{
    /// Equal to: min=FO_POINT, mag=FO_POINT, mip=FO_NONE
    TFO_NONE,
    /// Equal to: min=FO_LINEAR, mag=FO_LINEAR, mip=FO_POINT
    TFO_BILINEAR,
    /// Equal to: min=FO_LINEAR, mag=FO_LINEAR, mip=FO_LINEAR
    TFO_TRILINEAR,
    /// Equal to: min=FO_ANISOTROPIC, max=FO_ANISOTROPIC, mip=FO_LINEAR
	TFO_ANISOTROPIC
};

enum FilterType
{
    /// The filter used when shrinking a texture
    FT_MIN,
    /// The filter used when magnifying a texture
    FT_MAG,
    /// The filter used when determining the mipmap
    FT_MIP,
	NEAREST,
	LINEAR
};
/** Filtering options for textures / mipmaps. */
enum FilterOptions
{
    /// No filtering, used for FILT_MIP to turn off mipmapping
    FO_NONE,
    /// Use the closest pixel
    FO_POINT,
    /// Average of a 2x2 pixel area, denotes bilinear for MIN and MAG, trilinear for MIP
    FO_LINEAR,
    /// Similar to FO_LINEAR, but compensates for the angle of the texture plane
    FO_ANISOTROPIC
};

/** Light shading modes. */
enum ShadeOptions
{
    SO_FLAT,
    SO_GOURAUD,
    SO_PHONG
};

/** Fog modes. */
enum FogMode
{
    /// No fog. Duh.
    FOG_NONE,
    /// Fog density increases  exponentially from the camera (fog = 1/e^(distance * density))
    FOG_EXP,
    /// Fog density increases at the square of FOG_EXP, i.e. even quicker (fog = 1/e^(distance * density)^2)
    FOG_EXP2,
    /// Fog density increases linearly between the start and end distances
    FOG_LINEAR
};

/** Hardware culling modes based on vertex winding.
    This setting applies to how the hardware API culls triangles it is sent. */
enum CullingMode
{
    /// Hardware never culls triangles and renders everything it receives.
    CULL_NONE = 1,
    /// Hardware culls triangles whose vertices are listed clockwise in the view (default).
    CULL_CLOCKWISE = 2,
    /// Hardware culls triangles whose vertices are listed anticlockwise in the view.
    CULL_ANTICLOCKWISE = 3
};

/** Manual culling modes based on vertex normals.
    This setting applies to how the software culls triangles before sending them to the
	hardware API. This culling mode is used by scene managers which choose to implement it -
	normally those which deal with large amounts of fixed world geometry which is often
	planar (software culling movable variable geometry is expensive). */
enum ManualCullingMode
{
    /// No culling so everything is sent to the hardware.
    MANUAL_CULL_NONE = 1,
    /// Cull triangles whose normal is pointing away from the camera (default).
    MANUAL_CULL_BACK = 2,
    /// Cull triangles whose normal is pointing towards the camera.
    MANUAL_CULL_FRONT = 3
};

/** Enumerates the wave types usable with the Ogre engine. */
enum WaveformType
{
    /// Standard sine wave which smoothly changes from low to high and back again.
    WFT_SINE,
    /// An angular wave with a constant increase / decrease speed with pointed peaks.
    WFT_TRIANGLE,
    /// Half of the time is spent at the min, half at the max with instant transition between.
    WFT_SQUARE,
    /// Gradual steady increase from min to max over the period with an instant return to min at the end.
    WFT_SAWTOOTH,
    /// Gradual steady decrease from max to min over the period, with an instant return to max at the end.
    WFT_INVERSE_SAWTOOTH,
	/// Pulse Width Modulation. Works like WFT_SQUARE, except the high to low transition is controlled by duty cycle.
	/// With a duty cycle of 50% (0.5) will give the same output as WFT_SQUARE.
	WFT_PWM
};

/** The polygon mode to use when rasterising. */
enum PolygonMode
{
	/// Only points are rendered.
    PM_POINTS = 1,
	/// Wireframe models are rendered.
    PM_WIREFRAME = 2,
	/// Solid polygons are rendered.
    PM_SOLID = 3
};

#define E3D_MAX_SIMULTANEOUS_LIGHTS 8
/** Define number of texture coordinate sets allowed per vertex.
*/
#define E3D_MAX_TEXTURE_COORD_SETS 6

/** Define max number of texture layers allowed per pass on any card.
*/
#define E3D_MAX_TEXTURE_LAYERS 16

/** Define max number of multiple render targets (MRTs) to render to at once.
*/
#define E3D_MAX_MULTIPLE_RENDER_TARGETS 8

const int TYPE_NULL = 0x00;
const int TYPE_DIMENSION = 0x05;
const int TYPE_FRACTION = 0x06;

const int E3D_PACKAGENAME = 100;
const int E3D_LOCALE = 150;
const int E3D_VERSION = 200;
const int E3D_CHANNEL = 250;
// move to "eCommon.h"
//class MotionEvent
//{
//public:
//	float x;
//	float y;
//	MotionEvent(float x, float y)
//	{
//		this->x = x;
//		this->y = y;
//	}
//};
//
//class Particle;
//
//class Vector3Radius : public Object
//{
//public:
//	Vector3 center;
//	Vector3 lt;
//	float width;
//	float height;
////	float mRadius;
//	Particle* p;
//	Vector3Radius() {
//		center.x = center.y = center.z = 0;
//		lt.x = lt.y = lt.z = 0;
//		width = 0.0;
//		height = 0.0;
////		mRadius = -1;
//		p = 0;
//	}
//	~Vector3Radius() {
//		p = 0;
//	}
//	void getAsString(String & strstr) {
//		char str[1024];
//		sprintf(str, "center(%f, %f, %f), lt(%f, %f, %f), width=%f, height=%f, Particle addr=0x%x", center.x, center.y, center.z, lt.x, lt.y, lt.z, width, height, p);
//		strstr = str;
//	}
//};

//typedef SharedPtr<MotionEvent> MotionEventPtr;

template<typename T> struct TRect {
	T left, top, right, bottom;
	TRect() :
			left(0), top(0), right(0), bottom(0) {
	}
	TRect(T const & l, T const & t, T const & r, T const & b) :
			left(l), top(t), right(r), bottom(b) {
	}
	TRect(TRect const & o) :
			left(o.left), top(o.top), right(o.right), bottom(o.bottom) {
	}
	TRect & operator=(TRect const & o) {
		left = o.left;
		top = o.top;
		right = o.right;
		bottom = o.bottom;
		return *this;
	}
    /**
     * Set the rectangle's coordinates to the specified values. Note: no range
     * checking is performed, so it is up to the caller to ensure that
     * left <= right and top <= bottom.
     *
     * @param left   The X coordinate of the left side of the rectangle
     * @param top    The Y coordinate of the top of the rectangle
     * @param right  The X coordinate of the right side of the rectangle
     * @param bottom The Y coordinate of the bottom of the rectangle
     */
    void set(T left, T top, T right, T bottom) {
        this->left   = left;
        this->top    = top;
        this->right  = right;
        this->bottom = bottom;
    }
    /**
     * Copy the coordinates from src into this rectangle.
     *
     * @param src The rectangle whose coordinates are copied into this
     *           rectangle.
     */
    void set(TRect src) {
        this->left   = src.left;
        this->top    = src.top;
        this->right  = src.right;
        this->bottom = src.bottom;
    }
    /**
     * Inset the rectangle by (dx,dy). If dx is positive, then the sides are
     * moved inwards, making the rectangle narrower. If dx is negative, then the
     * sides are moved outwards, making the rectangle wider. The same holds true
     * for dy and the top and bottom.
     *
     * @param dx The amount to add(subtract) from the rectangle's left(right)
     * @param dy The amount to add(subtract) from the rectangle's top(bottom)
     */
    void inset(T dx, T dy) {
        left    += dx;
        top     += dy;
        right   -= dx;
        bottom  -= dy;
    }
    /**
      * Update this Rect to enclose itself and the specified rectangle. If the
      * specified rectangle is empty, nothing is done. If this rectangle is empty
      * it is set to the specified rectangle.
      *
      * @param left The left edge being unioned with this rectangle
      * @param top The top edge being unioned with this rectangle
      * @param right The right edge being unioned with this rectangle
      * @param bottom The bottom edge being unioned with this rectangle
      */
	void uniont(T left, T top, T right, T bottom) {
		if ((left < right) && (top < bottom)) {
			if ((this->left < this->right) && (this->top < this->bottom)) {
				if (this->left > left)
					this->left = left;
				if (this->top > top)
					this->top = top;
				if (this->right < right)
					this->right = right;
				if (this->bottom < bottom)
					this->bottom = bottom;
			} else {
				this->left = left;
				this->top = top;
				this->right = right;
				this->bottom = bottom;
			}
		}
	}

	/**
	 * Update this Rect to enclose itself and the specified rectangle. If the
	 * specified rectangle is empty, nothing is done. If this rectangle is empty
	 * it is set to the specified rectangle.
	 *
	 * @param r The rectangle being unioned with this rectangle
	 */
	void uniont(TRect r) {
		uniont(r.left, r.top, r.right, r.bottom);
	}
	T width() const {
		return right - left;
	}
	T height() const {
		return bottom - top;
	}
	bool isNull() const {
		return width() == 0 || height() == 0;
	}
	void setNull() {
		left = right = top = bottom = 0;
	}
	TRect & merge(const TRect& rhs) {
		if (isNull()) {
			*this = rhs;
		} else if (!rhs.isNull()) {
			left = std::min(left, rhs.left);
			right = std::max(right, rhs.right);
			top = std::min(top, rhs.top);
			bottom = std::max(bottom, rhs.bottom);
		}

		return *this;

	}
	TRect intersect(const TRect& rhs) const {
		TRect ret;
		if (isNull() || rhs.isNull()) {
			// empty
			return ret;
		} else {
			ret.left = std::max(left, rhs.left);
			ret.right = std::min(right, rhs.right);
			ret.top = std::max(top, rhs.top);
			ret.bottom = std::min(bottom, rhs.bottom);
		}

		if (ret.left > ret.right || ret.top > ret.bottom) {
			// no intersection, return empty
			ret.left = ret.top = ret.right = ret.bottom = 0;
		}

		return ret;

	}

};

template<typename T>
std::ostream& operator<<(std::ostream& o, const TRect<T>& r) {
	o << "TRect<>(l:" << r.left << ", t:" << r.top << ", r:" << r.right << ", b:" << r.bottom << ")";
	return o;
}

 /** Structure used to define a rectangle in a 2-D floating point space.
 */
typedef TRect<float> FloatRect;
typedef TRect<float> RectF;
/** Structure used to define a rectangle in a 2-D floating point space,
	subject to double / single floating point settings.
*/
typedef TRect<Real> RealRect;

/** Structure used to define a rectangle in a 2-D integer space.
*/
typedef TRect< long > Rect;


/** Structure used to define a box in a 3-D integer space.
 	Note that the left, top, and front edges are included but the right,
 	bottom and back ones are not.
 */
struct Box
{
    size_t left, top, right, bottom, front, back;
	/// Parameterless constructor for setting the members manually
    Box()
		: left(0), top(0), right(1), bottom(1), front(0), back(1)
    {
    }
    /** Define a box from left, top, right and bottom coordinates
    	This box will have depth one (front=0 and back=1).
    	@param	l	x value of left edge
    	@param	t	y value of top edge
    	@param	r	x value of right edge
    	@param	b	y value of bottom edge
    	@note Note that the left, top, and front edges are included
	           	but the right, bottom and back ones are not.
    */
    Box( size_t l, size_t t, size_t r, size_t b ):
        left(l),
        top(t),
        right(r),
        bottom(b),
        front(0),
        back(1)
    {
  		assert(right >= left && bottom >= top && back >= front);
    }
    /** Define a box from left, top, front, right, bottom and back
    	coordinates.
    	@param	l	x value of left edge
    	@param	t	y value of top edge
    	@param  ff  z value of front edge
    	@param	r	x value of right edge
    	@param	b	y value of bottom edge
    	@param  bb  z value of back edge
    	@note Note that the left, top, and front edges are included
	           	but the right, bottom and back ones are not.
    */
    Box( size_t l, size_t t, size_t ff, size_t r, size_t b, size_t bb ):
        left(l),
        top(t),
        right(r),
        bottom(b),
        front(ff),
        back(bb)
    {
  		assert(right >= left && bottom >= top && back >= front);
    }

    /// Return true if the other box is a part of this one
    bool contains(const Box &def) const
    {
    	return (def.left >= left && def.top >= top && def.front >= front &&
			def.right <= right && def.bottom <= bottom && def.back <= back);
    }

    /// Get the width of this box
    size_t getWidth() const { return right-left; }
    /// Get the height of this box
    size_t getHeight() const { return bottom-top; }
    /// Get the depth of this box
    size_t getDepth() const { return back-front; }
};

#endif
