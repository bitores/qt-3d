#ifndef __RotateAnimation_h__
#define __RotateAnimation_h__

#include "utils/include/prerequisites.h"
#include "utils/include/Common.h"
#include "Animation.h"
#include "utils/include/Transform.h"

/**
 * An animation that controls the rotation of an object. This rotation takes
 * place in the X-Y plane. You can specify the point to use for the center of
 * the rotation, where (0,0) is the top left point. If not specified, (0,0) is
 * the default rotation point.
 *
 */
class RotateAnimation : public Animation
{
    enum {
    /**
     * The specified dimension is an absolute number of pixels.
     */
    /*static int */DEGREE = 0,

    /**
     * The specified dimension holds a float and should be multiplied by the
     * height or width of the object being animated.
     */
    /*static int */VELOCITY = 1
    };
private:
	Transform* mTarget;
	float mFromDegrees;
    float mToDegrees;
    int   mAniMode;
    float mDegreeOffset; //
    float mCurDegrees;
    //float mRelativeToDegree;	// if relative, keep the start degree
    //float mPrevDegrees;			// if relative, keep the degree of last update
    Quaternion mRelativeToOrientation;	// if relative, keep the start orientation
    bool isRelativeToOrientationBeenSet;

    float mVelocity;
    long  mLastTime;
    int mPivotXType;
    int mPivotYType;
    float mPivotXValue;
    float mPivotYValue;

    float mPivotX;
    float mPivotY;

    Vector3 mAxis;
    TransformSpace mTransformSpace;

	void _init() {
		mPivotXType = ABSOLUTE;
		mPivotYType = ABSOLUTE;
		mPivotXValue = 0.0f;
		mPivotYValue = 0.0f;
        mDegreeOffset = 0.0f;
        mAniMode = DEGREE;
        mVelocity = 0.0f;
        mLastTime = 0;
	}
public:
    /**
     * Constructor used when a RotateAnimation is loaded from a resource.
     *
     * @param context Application context to use
     * @param attrs Attribute set from which to read values
     */
//    RotateAnimation(Context context, AttributeSet attrs) {
//        super(context, attrs);
//
//        TypedArray a = context.obtainStyledAttributes(attrs,
//                com.android.internal.R.styleable.RotateAnimation);
//
//        mFromDegrees = a.getFloat(
//                com.android.internal.R.styleable.RotateAnimation_fromDegrees, 0.0f);
//        mToDegrees = a.getFloat(com.android.internal.R.styleable.RotateAnimation_toDegrees, 0.0f);
//
//        Description d = Description.parseValue(a.peekValue(
//            com.android.internal.R.styleable.RotateAnimation_pivotX));
//        mPivotXType = d.type;
//        mPivotXValue = d.value;
//
//        d = Description.parseValue(a.peekValue(
//            com.android.internal.R.styleable.RotateAnimation_pivotY));
//        mPivotYType = d.type;
//        mPivotYValue = d.value;
//
//        a.recycle();
//
//        initializePivotPoint();
//    }

    /**
     * Constructor to use when building a RotateAnimation from code.
     * Default pivotX/pivotY point is (0,0).
     *
     * @param fromDegrees Rotation offset to apply at the start of the
     *        animation.
     *
     * @param toDegrees Rotation offset to apply at the end of the animation.
     */
    RotateAnimation(Root* root, Transform* target, float fromDegrees, float toDegrees, bool canStop = true);

    RotateAnimation(Root* root, Transform* target, const Vector3& axis, float fromDegrees, float toDegrees, bool canStop = true, TransformSpace relativeTo = TS_LOCAL);

    /**
     * Constructor to use when building a RotateAnimation from code
     *
     * @param fromDegrees Rotation offset to apply at the start of the
     *        animation.
     *
     * @param toDegrees Rotation offset to apply at the end of the animation.
     *
     * @param pivotX The X coordinate of the point about which the object is
     *        being rotated, specified as an absolute number where 0 is the left
     *        edge.
     * @param pivotY The Y coordinate of the point about which the object is
     *        being rotated, specified as an absolute number where 0 is the top
     *        edge.
     */
//    RotateAnimation(float fromDegrees, float toDegrees, float pivotX, float pivotY) {
//        _init();
//        mFromDegrees = fromDegrees;
//        mToDegrees = toDegrees;
//
//        mPivotXType = ABSOLUTE;
//        mPivotYType = ABSOLUTE;
//        mPivotXValue = pivotX;
//        mPivotYValue = pivotY;
//        initializePivotPoint();
//    }

    /**
     * Constructor to use when building a RotateAnimation from code
     *
     * @param fromDegrees Rotation offset to apply at the start of the
     *        animation.
     *
     * @param toDegrees Rotation offset to apply at the end of the animation.
     *
     * @param pivotXType Specifies how pivotXValue should be interpreted. One of
     *        Animation.ABSOLUTE, Animation.RELATIVE_TO_SELF, or
     *        Animation.RELATIVE_TO_PARENT.
     * @param pivotXValue The X coordinate of the point about which the object
     *        is being rotated, specified as an absolute number where 0 is the
     *        left edge. This value can either be an absolute number if
     *        pivotXType is ABSOLUTE, or a percentage (where 1.0 is 100%)
     *        otherwise.
     * @param pivotYType Specifies how pivotYValue should be interpreted. One of
     *        Animation.ABSOLUTE, Animation.RELATIVE_TO_SELF, or
     *        Animation.RELATIVE_TO_PARENT.
     * @param pivotYValue The Y coordinate of the point about which the object
     *        is being rotated, specified as an absolute number where 0 is the
     *        top edge. This value can either be an absolute number if
     *        pivotYType is ABSOLUTE, or a percentage (where 1.0 is 100%)
     *        otherwise.
     */
//    RotateAnimation(float fromDegrees, float toDegrees, int pivotXType, float pivotXValue, int pivotYType, float pivotYValue) {
//        _init();
//        mFromDegrees = fromDegrees;
//        mToDegrees = toDegrees;
//
//        mPivotXValue = pivotXValue;
//        mPivotXType = pivotXType;
//        mPivotYValue = pivotYValue;
//        mPivotYType = pivotYType;
//        initializePivotPoint();
//    }
    void reset();
    /**
     * Called at the end of constructor methods to initialize, if possible, values for
     * the pivot point. This is only possible for ABSOLUTE pivot values.
     */
private:
    void initializePivotPoint() {
        if (mPivotXType == ABSOLUTE) {
            mPivotX = mPivotXValue;
        }
        if (mPivotYType == ABSOLUTE) {
            mPivotY = mPivotYValue;
        }
    }

    void preTransform();

public:
    bool getTransformation(long currentTime/*, Transform* t*/);
    void applyTransformation(long detalTime/*, Transform* t*/);
    void applyTransformation(float interpolatedTime/*, Transform* t*/);
    void initialize(int width, int height, int parentWidth, int parentHeight);


    float getFromDegrees();
    void setFromDegrees(float fromDegrees);
    float getToDegrees();
    void setToDegrees(float toDegrees);
    void setAniMode(String mode);
    void setVelocity(float velocity);
    float getVelocity();
    void setDegreesOffset(float Offset);
    float getCurDegrees();
    void setAxis(Vector3 axis);
    void setTransformSpace(TransformSpace ts);
    void setTransformSpace(String tfsName);
};

#endif
