#ifndef __ScaleAnimation_h__
#define __ScaleAnimation_h__

#include "utils/include/prerequisites.h"
#include "utils/include/Common.h"
#include "utils/include/Transform.h"
#include "Animation.h"

/**
 * An animation that controls the scale of an object. You can specify the point
 * to use for the center of scaling.
 *
 */
class ScaleAnimation  : public Animation
{
private:
	Transform* mTarget;
    float mFromXDelta_Raw;
	float mToXDelta_Raw;
	float mFromYDelta_Raw;
	float mToYDelta_Raw;
	float mFromZDelta_Raw;
	float mToZDelta_Raw;


    float mFromXDelta;
    float mToXDelta;
    float mFromYDelta;
    float mToYDelta;
    float mFromZDelta;
    float mToZDelta;

    bool mIsDirty;
//    int mFromXType/* = TypedValue.TYPE_NULL*/;
//    int mToXType/* = TypedValue.TYPE_NULL*/;
//    int mFromYType/* = TypedValue.TYPE_NULL*/;
//    int mToYType/* = TypedValue.TYPE_NULL*/;
//
//    int mFromXData;
//    int mToXData;
//    int mFromYData;
//    int mToYData;

    int mPivotXType/* = ABSOLUTE*/;
    int mPivotYType/* = ABSOLUTE*/;
    float mPivotXValue;
    float mPivotYValue;

    float mPivotX;
    float mPivotY;

	void _init() {
//		mFromXType = /*TypedValue.*/TYPE_NULL;
//		mToXType = /*TypedValue.*/TYPE_NULL;
//		mFromYType = /*TypedValue.*/TYPE_NULL;
//		mToYType = /*TypedValue.*/TYPE_NULL;
//
//		mFromXData = 0;
//		mToXData = 0;
//		mFromYData = 0;
//		mToYData = 0;

		mPivotXType = ABSOLUTE;
		mPivotYType = ABSOLUTE;
		mPivotXValue = 0.0f;
		mPivotYValue = 0.0f;
	}

public:
    /**
     * Constructor used when a ScaleAnimation is loaded from a resource.
     *
     * @param context Application context to use
     * @param attrs Attribute set from which to read values
     */
//	ScaleAnimation(Context context, AttributeSet attrs) {
//        super(context, attrs);
//        _init();
//        mResources = context.getResources();
//
//        TypedArray a = context.obtainStyledAttributes(attrs,
//                com.android.internal.R.styleable.ScaleAnimation);
//
//        TypedValue tv = a.peekValue(
//                com.android.internal.R.styleable.ScaleAnimation_fromXScale);
//        mFromX = 0.0f;
//        if (tv != null) {
//            if (tv.type == TypedValue.TYPE_FLOAT) {
//                // This is a scaling factor.
//                mFromX = tv.getFloat();
//            } else {
//                mFromXType = tv.type;
//                mFromXData = tv.data;
//            }
//        }
//        tv = a.peekValue(
//                com.android.internal.R.styleable.ScaleAnimation_toXScale);
//        mToX = 0.0f;
//        if (tv != null) {
//            if (tv.type == TypedValue.TYPE_FLOAT) {
//                // This is a scaling factor.
//                mToX = tv.getFloat();
//            } else {
//                mToXType = tv.type;
//                mToXData = tv.data;
//            }
//        }
//
//        tv = a.peekValue(
//                com.android.internal.R.styleable.ScaleAnimation_fromYScale);
//        mFromY = 0.0f;
//        if (tv != null) {
//            if (tv.type == TypedValue.TYPE_FLOAT) {
//                // This is a scaling factor.
//                mFromY = tv.getFloat();
//            } else {
//                mFromYType = tv.type;
//                mFromYData = tv.data;
//            }
//        }
//        tv = a.peekValue(
//                com.android.internal.R.styleable.ScaleAnimation_toYScale);
//        mToY = 0.0f;
//        if (tv != null) {
//            if (tv.type == TypedValue.TYPE_FLOAT) {
//                // This is a scaling factor.
//                mToY = tv.getFloat();
//            } else {
//                mToYType = tv.type;
//                mToYData = tv.data;
//            }
//        }
//
//        Description d = Description.parseValue(a.peekValue(
//                com.android.internal.R.styleable.ScaleAnimation_pivotX));
//        mPivotXType = d.type;
//        mPivotXValue = d.value;
//
//        d = Description.parseValue(a.peekValue(
//            com.android.internal.R.styleable.ScaleAnimation_pivotY));
//        mPivotYType = d.type;
//        mPivotYValue = d.value;
//
//        a.recycle();
//
//        initializePivotPoint();
//    }


    /**
     * Constructor to use when building a ScaleAnimation from code
     *
     * @param fromX Horizontal scaling factor to apply at the start of the
     *        animation
     * @param toX Horizontal scaling factor to apply at the end of the animation
     * @param fromY Vertical scaling factor to apply at the start of the
     *        animation
     * @param toY Vertical scaling factor to apply at the end of the animation
     */
    ScaleAnimation(Root* root, Transform* target, float fromXDelta = 1.0f, float toXDelta = 1.0f, float fromYDelta = 1.0f, float toYDelta = 1.0f, float fromZDelta = 1.0f, float toZDelta = 1.0f, bool canStop = true);

    /**
     * Constructor to use when building a ScaleAnimation from code
     *
     * @param fromX Horizontal scaling factor to apply at the start of the
     *        animation
     * @param toX Horizontal scaling factor to apply at the end of the animation
     * @param fromY Vertical scaling factor to apply at the start of the
     *        animation
     * @param toY Vertical scaling factor to apply at the end of the animation
     * @param pivotX The X coordinate of the point about which the object is
     *        being scaled, specified as an absolute number where 0 is the left
     *        edge. (This point remains fixed while the object changes size.)
     * @param pivotY The Y coordinate of the point about which the object is
     *        being scaled, specified as an absolute number where 0 is the top
     *        edge. (This point remains fixed while the object changes size.)
     */
//    ScaleAnimation(float fromX, float toX, float fromY, float toY,
//            float pivotX, float pivotY) {
//    	_init();
//        mFromX = fromX;
//        mToX = toX;
//        mFromY = fromY;
//        mToY = toY;
//
//        mPivotXType = ABSOLUTE;
//        mPivotYType = ABSOLUTE;
//        mPivotXValue = pivotX;
//        mPivotYValue = pivotY;
//        initializePivotPoint();
//    }

    /**
     * Constructor to use when building a ScaleAnimation from code
     *
     * @param fromX Horizontal scaling factor to apply at the start of the
     *        animation
     * @param toX Horizontal scaling factor to apply at the end of the animation
     * @param fromY Vertical scaling factor to apply at the start of the
     *        animation
     * @param toY Vertical scaling factor to apply at the end of the animation
     * @param pivotXType Specifies how pivotXValue should be interpreted. One of
     *        Animation.ABSOLUTE, Animation.RELATIVE_TO_SELF, or
     *        Animation.RELATIVE_TO_PARENT.
     * @param pivotXValue The X coordinate of the point about which the object
     *        is being scaled, specified as an absolute number where 0 is the
     *        left edge. (This point remains fixed while the object changes
     *        size.) This value can either be an absolute number if pivotXType
     *        is ABSOLUTE, or a percentage (where 1.0 is 100%) otherwise.
     * @param pivotYType Specifies how pivotYValue should be interpreted. One of
     *        Animation.ABSOLUTE, Animation.RELATIVE_TO_SELF, or
     *        Animation.RELATIVE_TO_PARENT.
     * @param pivotYValue The Y coordinate of the point about which the object
     *        is being scaled, specified as an absolute number where 0 is the
     *        top edge. (This point remains fixed while the object changes
     *        size.) This value can either be an absolute number if pivotYType
     *        is ABSOLUTE, or a percentage (where 1.0 is 100%) otherwise.
     */
//    ScaleAnimation(float fromX, float toX, float fromY, float toY,
//            int pivotXType, float pivotXValue, int pivotYType, float pivotYValue) {
//    	_init();
//        mFromX = fromX;
//        mToX = toX;
//        mFromY = fromY;
//        mToY = toY;
//
//        mPivotXValue = pivotXValue;
//        mPivotXType = pivotXType;
//        mPivotYValue = pivotYValue;
//        mPivotYType = pivotYType;
//        initializePivotPoint();
//    }

    /**
     * Called at the end of constructor methods to initialize, if possible, values for
     * the pivot point. This is only possible for ABSOLUTE pivot values.
     */
    void initializePivotPoint() {
        if (mPivotXType == ABSOLUTE) {
            mPivotX = mPivotXValue;
        }
        if (mPivotYType == ABSOLUTE) {
            mPivotY = mPivotYValue;
        }
    }

    void setFromXDelta(float fromXDelta) {
  		mFromXDelta_Raw = fromXDelta;
//  		mEnableXTranslate = true;
  		mIsDirty = true;
  	}

  	void setToXDelta(float toXDelta) {
  		mToXDelta_Raw = toXDelta;
//  		mEnableXTranslate = true;
  		mIsDirty = true;
  	}

  	void setFromYDelta(float fromYDelta) {
  		mFromYDelta_Raw = fromYDelta;
//  		mEnableYTranslate = true;
  		mIsDirty = true;
  	}

  	void setToYDelta(float toYDelta) {
  		mToYDelta_Raw = toYDelta;
//  		mEnableYTranslate = true;
  		mIsDirty = true;
  	}

  	void setFromZDelta(float fromZDelta) {
  	   	mFromZDelta_Raw = fromZDelta;
//  	   	mEnableZTranslate = true;
  	   	mIsDirty = true;
  	}

  	void setToZDelta(float toZDelta) {
  		mToZDelta_Raw = toZDelta;
//  		mEnableZTranslate = true;
  		mIsDirty = true;
  	}

    void updateCoordinateData()
    {
//		if (mIsCoordinateRelativeToScreen)
//		{
//			mFromXDelta = mScreenWidth * mFromXDelta_Raw;
//			mToXDelta = mScreenWidth * mToXDelta_Raw;
//			mFromYDelta = mScreenHeight * mFromYDelta_Raw;
//			mToYDelta = mScreenHeight * mToYDelta_Raw;
//			mFromZDelta = mFromZDelta_Raw;
//			mToZDelta = mToZDelta_Raw;
//		}else{
			mFromXDelta = mFromXDelta_Raw;
			mToXDelta = mToXDelta_Raw;
			mFromYDelta = mFromYDelta_Raw;
			mToYDelta = mToYDelta_Raw;
			mFromZDelta = mFromZDelta_Raw;
			mToZDelta = mToZDelta_Raw;
//		}
//
//
//		mIsDirty = false;

    }

    void applyTransformation(float interpolatedTime/*, Transform* t*/);
    float resolveScale(float scale, int type, int data, int size, int psize);

    void initialize(int width, int height, int parentWidth, int parentHeight);
};

#endif
