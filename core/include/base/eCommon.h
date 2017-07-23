#ifndef __eCommon_h__
#define __eCommon_h__
#include "Object.h"
#include "utils/include/Vector3.h"
#include "utils/include/String.h"

/// Defines the type of light
//enum LightType
//{
//	/// Spotlights simulate a cone of light from a source so require position and direction, plus extra values for falloff
//	Spot,
//	/// Directional lights simulate parallel light beams from a distant source, hence have direction but no position
//	Directional,
//	/// Point light sources give off light equally in all directions, so require only position not direction
//	Point
//	Area
//};

enum Anchor {
	TOP_LEFT,
	BOTTOM_LEFT,
	TOP_RIGHT,
	BOTTOM_RIGHT,
	CENTER,
	TOP_CENTER,
	CUSTOMIZE
};

inline String AnchorValueToString(Anchor anchorValue) {
	String sAnchor;
	switch (anchorValue) {
	case TOP_LEFT:
		sAnchor = "top_left";
		break;
	case BOTTOM_LEFT:
		sAnchor = "bottom_left";
		break;
	case TOP_RIGHT:
		sAnchor = "top_right";
		break;
	case BOTTOM_RIGHT:
		sAnchor = "bottom_right";
		break;
	case TOP_CENTER:
		sAnchor = "top_center";
		break;
	case CUSTOMIZE:
		sAnchor = "customize";
	default:
		sAnchor = "center";
		break;
	}
	return sAnchor;
}

inline Anchor AnchorStringToValue(String anchorString) {
	Anchor anchor = CENTER;
	StringUtil::toLowerCase(anchorString);
	if ("top_left" == anchorString) {
		anchor = TOP_LEFT;
	} else if ("bottom_left" == anchorString) {
		anchor = BOTTOM_LEFT;
	} else if ("top_right" == anchorString) {
		anchor = TOP_RIGHT;
	} else if ("bottom_right" == anchorString) {
		anchor = BOTTOM_RIGHT;
	} else if ("top_center" == anchorString) {
		anchor = TOP_CENTER;
	} else if ("customize" == anchorString) {
			anchor = CUSTOMIZE;
	} else {
		anchor = CENTER;
	}
	return anchor;
}

class MotionEvent
{
public:
	float x;
	float y;
    MotionEvent()
    {
        this->x = 0;
        this->y = 0;
    }
	MotionEvent(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
};

class Particle;

class Vector3Radius : public Object
{
public:
	Vector3 center;
	Vector3 lt;
	float width;
	float height;
//	float mRadius;
	Particle* p;
	Vector3Radius() {
		center.x = center.y = center.z = 0;
		lt.x = lt.y = lt.z = 0;
		width = 0.0;
		height = 0.0;
//		mRadius = -1;
		p = 0;
	}
	~Vector3Radius() {
		p = 0;
	}
	void getAsString(String & strstr) {
		char str[1024];
		sprintf(str, "center(%f, %f, %f), lt(%f, %f, %f), width=%f, height=%f, Particle addr=0x%x", center.x, center.y, center.z, lt.x, lt.y, lt.z, width, height, p);
		strstr = str;
	}
};

#endif
