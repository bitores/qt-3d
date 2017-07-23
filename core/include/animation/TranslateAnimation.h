#ifndef __TranslateAnimation_h__
#define __TranslateAnimation_h__

#include "utils/include/prerequisites.h"
#include "utils/include/Common.h"
#include "utils/include/Transform.h"
#include "Animation.h"


/**
 * An animation that controls the position of an object. See the
 * {@link android.view.animation full package} description for details and
 * sample code.
 *
 */
class TranslateAnimation : public Animation
{
private:
	Transform* mTarget;
	int mFromXType/* = ABSOLUTE*/;
    int mToXType/* = ABSOLUTE*/;
    int mFromYType/* = ABSOLUTE*/;
    int mToYType/* = ABSOLUTE*/;
    int mFromZType/* = ABSOLUTE*/;
    int mToZType/* = ABSOLUTE*/;
//    float mFromXValue/* = 0.0f*/;
//    float mToXValue/* = 0.0f*/;
//
//    float mFromYValue/* = 0.0f*/;
//    float mToYValue/* = 0.0f*/;

    float mFromXDelta;
    float mToXDelta;
    float mFromYDelta;
    float mToYDelta;
    float mFromZDelta;
    float mToZDelta;

    // coordinate relative to screen
    float mFromXDelta_Raw;
	float mToXDelta_Raw;
	float mFromYDelta_Raw;
	float mToYDelta_Raw;
	float mFromZDelta_Raw;
	float mToZDelta_Raw;
	float mScreenWidth;
	float mScreenHeight;
    bool mIsCoordinateRelativeToScreen;
	bool mIsDirty;

    bool mEnableXTranslate;
    bool mEnableYTranslate;
    bool mEnableZTranslate;



    void _init() {
        mFromXType = ABSOLUTE;
        mToXType = ABSOLUTE;
        mFromYType = ABSOLUTE;
        mToYType = ABSOLUTE;
        mFromZType = ABSOLUTE;
        mToZType = ABSOLUTE;
        mRelative = false;
        mEnableXTranslate = false;
        mEnableYTranslate = false;
        mEnableZTranslate = false;

        mIsCoordinateRelativeToScreen = false;
        mIsDirty = true;

        mScreenWidth = 0.0;
        mScreenHeight = 0.0;

//        mFromXValue = 0.0f;
//        mToXValue = 0.0f;
//        mFromYValue = 0.0f;
//        mToYValue = 0.0f;
    }
public:
    /**
     * Constructor used when a TranslateAnimation is loaded from a resource.
     *
     * @param context Application context to use
     * @param attrs Attribute set from which to read values
     */
//     TranslateAnimation(Context context, AttributeSet attrs) {
//        super(context, attrs);
//
//        TypedArray a = context.obtainStyledAttributes(attrs,
//                com.android.internal.R.styleable.TranslateAnimation);
//
//        Description d = Description.parseValue(a.peekValue(
//            com.android.internal.R.styleable.TranslateAnimation_fromXDelta));
//        mFromXType = d.type;
//        mFromXValue = d.value;
//
//        d = Description.parseValue(a.peekValue(
//                com.android.internal.R.styleable.TranslateAnimation_toXDelta));
//        mToXType = d.type;
//        mToXValue = d.value;
//
//        d = Description.parseValue(a.peekValue(
//            com.android.internal.R.styleable.TranslateAnimation_fromYDelta));
//        mFromYType = d.type;
//        mFromYValue = d.value;
//
//        d = Description.parseValue(a.peekValue(
//            com.android.internal.R.styleable.TranslateAnimation_toYDelta));
//        mToYType = d.type;
//        mToYValue = d.value;
//
//        a.recycle();
//    }

    TranslateAnimation(Root* root, Transform* target, bool canStop = true) : Animation(root, canStop) {
    	mTarget = target;
    	_init();
    }

    /**
     * Constructor to use when building a TranslateAnimation from code
     *
     * @param fromXDelta Change in X coordinate to apply at the start of the
     *        animation
     * @param toXDelta Change in X coordinate to apply at the end of the
     *        animation
     * @param fromYDelta Change in Y coordinate to apply at the start of the
     *        animation
     * @param toYDelta Change in Y coordinate to apply at the end of the
     *        animation
     */
    TranslateAnimation(Root* root, Transform* target, float fromXDelta, float toXDelta, float fromYDelta, float toYDelta, bool canStop = true) : Animation(root, canStop) {
    	mTarget = target;
    	_init();
    	mFromXDelta_Raw = fromXDelta;
    	mToXDelta_Raw = toXDelta;
    	mFromYDelta_Raw = fromYDelta;
    	mToYDelta_Raw = toYDelta;

        mEnableXTranslate = true;
        mEnableYTranslate = true;
    }

    TranslateAnimation(Root* root, Transform* target, float fromXDelta, float toXDelta, float fromYDelta, float toYDelta, float fromZDelta, float toZDelta, bool canStop = true) : Animation(root, canStop) {
    	mTarget = target;
    	_init();
    	mFromXDelta_Raw = fromXDelta;
    	mToXDelta_Raw = toXDelta;
    	mFromYDelta_Raw = fromYDelta;
    	mToYDelta_Raw = toYDelta;
    	mFromZDelta_Raw = fromZDelta;
    	mToZDelta_Raw = toZDelta;

        mEnableXTranslate = true;
        mEnableYTranslate = true;
        mEnableZTranslate = true;
    }

    void updateCoordinateData()
    {
		if (mIsCoordinateRelativeToScreen)
		{
			mFromXDelta = mScreenWidth * mFromXDelta_Raw;
			mToXDelta = mScreenWidth * mToXDelta_Raw;
			mFromYDelta = mScreenHeight * mFromYDelta_Raw;
			mToYDelta = mScreenHeight * mToYDelta_Raw;
			mFromZDelta = mFromZDelta_Raw;
			mToZDelta = mToZDelta_Raw;
		}else{
			mFromXDelta = mFromXDelta_Raw;
			mToXDelta = mToXDelta_Raw;
			mFromYDelta = mFromYDelta_Raw;
			mToYDelta = mToYDelta_Raw;
			mFromZDelta = mFromZDelta_Raw;
			mToZDelta = mToZDelta_Raw;
		}


		mIsDirty = false;

    }

    void setIsCoordinateRelativeToScreen(bool isCoordinateRelativeToScreen)
    {
    	mIsCoordinateRelativeToScreen = isCoordinateRelativeToScreen;
    	mIsDirty = true;
    }

    void enableXTranslate(bool enable, float fromXDelta, float toXDelta) {
    	if (mEnableXTranslate != enable) {
    		mEnableXTranslate = enable;
        	if (enable) {
            	mFromXDelta_Raw = fromXDelta;
            	mToXDelta_Raw = toXDelta;
        	}

        	mIsDirty = true;
    	}
    }

    void enableYTranslate(bool enable, float fromYDelta, float toYDelta) {
    	if (mEnableYTranslate != enable) {
    		mEnableYTranslate = enable;
    		if (enable) {
    	    	mFromYDelta_Raw = fromYDelta;
    	    	mToYDelta_Raw = toYDelta;
    		}

    		mIsDirty = true;
    	}
    }

    void enableZTranslate(bool enable, float fromZDelta, float toZDelta) {
    	if (mEnableZTranslate != enable) {
    		mEnableZTranslate = enable;
    		if (enable) {
    	    	mFromZDelta_Raw = fromZDelta;
    	    	mToZDelta_Raw = toZDelta;
    		}

    		mIsDirty = true;
    	}
    }
    
    void setFromXDelta(float fromXDelta) {
		mFromXDelta_Raw = fromXDelta;
		mEnableXTranslate = true;
		mIsDirty = true;
	}

	void setToXDelta(float toXDelta) {
		mToXDelta_Raw = toXDelta;
		mEnableXTranslate = true;
		mIsDirty = true;
	}

	void setFromYDelta(float fromYDelta) {
		mFromYDelta_Raw = fromYDelta;
		mEnableYTranslate = true;
		mIsDirty = true;
	}

	void setToYDelta(float toYDelta) {
		mToYDelta_Raw = toYDelta;
		mEnableYTranslate = true;
		mIsDirty = true;
	}

	void setFromZDelta(float fromZDelta) {
	   	mFromZDelta_Raw = fromZDelta;
	   	mEnableZTranslate = true;
	   	mIsDirty = true;
	}

	void setToZDelta(float toZDelta) {
		mToZDelta_Raw = toZDelta;
		mEnableZTranslate = true;
		mIsDirty = true;
	}

    void resetXTranslateDelta(float fromXDelta, float toXDelta) {
    	mFromXDelta_Raw = fromXDelta;
    	mToXDelta_Raw = toXDelta;
    	mIsDirty = true;
    }

    void resetYTranslateDelta(float fromYDelta, float toYDelta) {
    	mFromYDelta_Raw = fromYDelta;
    	mToYDelta_Raw = toYDelta;
    	mIsDirty = true;
    }

    void resetZTranslateDelta(float fromZDelta, float toZDelta) {
    	mFromZDelta_Raw = fromZDelta;
    	mToZDelta_Raw = toZDelta;
    	mIsDirty = true;
    }

   	void onResize(float screenWidth, float screenHeight) {
   		mScreenWidth = screenWidth;
   		mScreenHeight = screenHeight;
   		mIsDirty = true;
   	}

    /**
     * Constructor to use when building a TranslateAnimation from code
     *
     * @param fromXType Specifies how fromXValue should be interpreted. One of
     *        Animation.ABSOLUTE, Animation.RELATIVE_TO_SELF, or
     *        Animation.RELATIVE_TO_PARENT.
     * @param fromXValue Change in X coordinate to apply at the start of the
     *        animation. This value can either be an absolute number if fromXType
     *        is ABSOLUTE, or a percentage (where 1.0 is 100%) otherwise.
     * @param toXType Specifies how toXValue should be interpreted. One of
     *        Animation.ABSOLUTE, Animation.RELATIVE_TO_SELF, or
     *        Animation.RELATIVE_TO_PARENT.
     * @param toXValue Change in X coordinate to apply at the end of the
     *        animation. This value can either be an absolute number if toXType
     *        is ABSOLUTE, or a percentage (where 1.0 is 100%) otherwise.
     * @param fromYType Specifies how fromYValue should be interpreted. One of
     *        Animation.ABSOLUTE, Animation.RELATIVE_TO_SELF, or
     *        Animation.RELATIVE_TO_PARENT.
     * @param fromYValue Change in Y coordinate to apply at the start of the
     *        animation. This value can either be an absolute number if fromYType
     *        is ABSOLUTE, or a percentage (where 1.0 is 100%) otherwise.
     * @param toYType Specifies how toYValue should be interpreted. One of
     *        Animation.ABSOLUTE, Animation.RELATIVE_TO_SELF, or
     *        Animation.RELATIVE_TO_PARENT.
     * @param toYValue Change in Y coordinate to apply at the end of the
     *        animation. This value can either be an absolute number if toYType
     *        is ABSOLUTE, or a percentage (where 1.0 is 100%) otherwise.
     */
    TranslateAnimation(Root* root, Transform* target, int fromXType, float fromXValue, int toXType, float toXValue,
            int fromYType, float fromYValue, int toYType, float toYValue, bool canStop = true) : Animation(root, canStop) {
    	mTarget = target;
    	_init();
    	mFromXDelta_Raw = fromXValue;
    	mToXDelta_Raw = toXValue;
    	mFromYDelta_Raw = fromYValue;
    	mToYDelta_Raw = toYValue;

    	mIsDirty = true;

//        mFromXType = fromXType;
//        mToXType = toXType;
//        mFromYType = fromYType;
//        mToYType = toYType;
    }

    void applyTransformation(float interpolatedTime/*, Transform* t*/);

    void initialize(int width, int height, int parentWidth, int parentHeight);
};

#endif
