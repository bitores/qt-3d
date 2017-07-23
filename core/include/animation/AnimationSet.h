#ifndef __AnimationSet_h__
#define __AnimationSet_h__

#include "utils/include/prerequisites.h"
#include "utils/include/Common.h"
#include "Animation.h"

/**
 * Represents a group of Animations that should be played together.
 * The transformation of each individual animation are composed
 * together into a single transform.
 * If AnimationSet sets any properties that its children also set
 * (for example, duration or fillBefore), the values of AnimationSet
 * override the child values.
 *
 * <p>The way that AnimationSet inherits behavior from Animation is important to
 * understand. Some of the Animation attributes applied to AnimationSet affect the
 * AnimationSet itself, some are pushed down to the children, and some are ignored,
 * as follows:
 * <ul>
 *     <li>duration, repeatMode, fillBefore, fillAfter: These properties, when set
 *     on an AnimationSet object, will be pushed down to all child animations.</li>
 *     <li>repeatCount, fillEnabled: These properties are ignored for AnimationSet.</li>
 *     <li>startOffset, shareInterpolator: These properties apply to the AnimationSet itself.</li>
 * </ul>
 * Starting with {@link android.os.Build.VERSION_CODES#ICE_CREAM_SANDWICH},
 * the behavior of these properties is the same in XML resources and at runtime (prior to that
 * release, the values set in XML were ignored for AnimationSet). That is, calling
 * <code>setDuration(500)</code> on an AnimationSet has the same effect as declaring
 * <code>android:duration="500"</code> in an XML resource for an AnimationSet object.</p>
 */
class AnimationSet : public Animation
{
private:
	static int PROPERTY_FILL_AFTER_MASK         /*= 0x1*/;
    static int PROPERTY_FILL_BEFORE_MASK        /*= 0x2*/;
    static int PROPERTY_REPEAT_MODE_MASK       /* = 0x4*/;
    static int PROPERTY_START_OFFSET_MASK       /*= 0x8*/;
    static int PROPERTY_SHARE_INTERPOLATOR_MASK /*= 0x10*/;
    static int PROPERTY_DURATION_MASK           /*= 0x20*/;
    static int PROPERTY_MORPH_MATRIX_MASK       /*= 0x40*/;
    static int PROPERTY_CHANGE_BOUNDS_MASK      /*= 0x80*/;

    int mFlags;
    bool mDirty;
    bool mHasAlpha;

    std::list<Animation*> mAnimations;/* = new ArrayList<Animation*>()*/;

//    Transform* mTempTransformation/* = new Transformation()*/;

    long mLastEnd;

    long* mStoredOffsets;

//    void _init();
    /**
     * Constructor used when an AnimationSet is loaded from a resource.
     *
     * @param context Application context to use
     * @param attrs Attribute set from which to read values
     */
//    public AnimationSet(Context context, AttributeSet attrs) {
//        super(context, attrs);
//
//        TypedArray a =
//            context.obtainStyledAttributes(attrs, com.android.internal.R.styleable.AnimationSet);
//
//        setFlag(PROPERTY_SHARE_INTERPOLATOR_MASK,
//                a.getbool(com.android.internal.R.styleable.AnimationSet_shareInterpolator, true));
//        init();
//
//        if (context.getApplicationInfo().targetSdkVersion >=
//                Build.VERSION_CODES.ICE_CREAM_SANDWICH) {
//            if (a.hasValue(com.android.internal.R.styleable.AnimationSet_duration)) {
//                mFlags |= PROPERTY_DURATION_MASK;
//            }
//            if (a.hasValue(com.android.internal.R.styleable.AnimationSet_fillBefore)) {
//                mFlags |= PROPERTY_FILL_BEFORE_MASK;
//            }
//            if (a.hasValue(com.android.internal.R.styleable.AnimationSet_fillAfter)) {
//                mFlags |= PROPERTY_FILL_AFTER_MASK;
//            }
//            if (a.hasValue(com.android.internal.R.styleable.AnimationSet_repeatMode)) {
//                mFlags |= PROPERTY_REPEAT_MODE_MASK;
//            }
//            if (a.hasValue(com.android.internal.R.styleable.AnimationSet_startOffset)) {
//                mFlags |= PROPERTY_START_OFFSET_MASK;
//            }
//        }
//
//        a.recycle();
//    }


public:
    /**
     * Constructor to use when building an AnimationSet from code
     *
     * @param shareInterpolator Pass true if all of the animations in this set
     *        should use the interpolator assocciated with this AnimationSet.
     *        Pass false if each animation should use its own interpolator.
     */
    AnimationSet(Root* root, bool shareInterpolator = false, bool canStop = false) : Animation(root, canStop) {
        setFlag(PROPERTY_SHARE_INTERPOLATOR_MASK, shareInterpolator);
        init();
    }

    virtual ~AnimationSet();

    AnimationSet* clone();

    void enableShareInterpolator(bool shareInterpolator) {
        setFlag(PROPERTY_SHARE_INTERPOLATOR_MASK, shareInterpolator);
    }

private:

    void setFlag(int mask, bool value) {
        if (value) {
            mFlags |= mask;
        } else {
            mFlags &= ~mask;
        }
    }

    void init();

public:
    void setFillAfter(bool fillAfter) {
        mFlags |= PROPERTY_FILL_AFTER_MASK;
        Animation::setFillAfter(fillAfter);
    }

    void setFillBefore(bool fillBefore) {
        mFlags |= PROPERTY_FILL_BEFORE_MASK;
        Animation::setFillBefore(fillBefore);
    }

    void setRepeatMode(int repeatMode) {
        mFlags |= PROPERTY_REPEAT_MODE_MASK;
        Animation::setRepeatMode(repeatMode);
    }

    void setRepeatMode(String repeatMode) {
        mFlags |= PROPERTY_REPEAT_MODE_MASK;
        Animation::setRepeatMode(repeatMode);
    }

    void setStartOffset(long startOffset) {
        mFlags |= PROPERTY_START_OFFSET_MASK;
        Animation::setStartOffset(startOffset);
    }

    /**
     * @hide
     */
    bool hasAlpha();
    /**
     * <p>Sets the duration of every child animation.</p>
     *
     * @param durationMillis the duration of the animation, in milliseconds, for
     *        every child in this set
     */
    void setDuration(long durationMillis) {
        mFlags |= PROPERTY_DURATION_MASK;
        Animation::setDuration(durationMillis);
        mLastEnd = mStartOffset + mDuration;
    }

    /**
     * Add a child animation to this animation set.
     * The transforms of the child animations are applied in the order
     * that they were added
     * @param a Animation to add.
     */
    void addAnimation(Animation *a);
    /**
     * Sets the start time of this animation and all child animations
     *
     * @see android.view.animation.Animation#setStartTime(long)
     */
    void setStartTime(long startTimeMillis);

    long getStartTime();

    void restrictDuration(long durationMillis);

    /**
     * The duration of an AnimationSet is defined to be the
     * duration of the longest child animation.
     *
     * @see android.view.animation.Animation#getDuration()
     */
    long getDuration();
    /**
     * The duration hint of an animation set is the maximum of the duration
     * hints of all of its component animations.
     *
     * @see android.view.animation.Animation#computeDurationHint
     */
    long computeDurationHint();
    /**
     * @hide
     */
    void initializeInvalidateRegion(int left, int top, int right, int bottom);
    /**
     * The transformation of an animation set is the concatenation of all of its
     * component animations.
     *
     * @see android.view.animation.Animation#getTransformation
     */
    bool getTransformation(long currentTime/*, Transform* t*/);
    /**
     * @see android.view.animation.Animation#scaleCurrentDuration(float)
     */
    void scaleCurrentDuration(float scale);

    /**
     * @see android.view.animation.Animation#initialize(int, int, int, int)
     */
    void initialize(int width, int height, int parentWidth, int parentHeight);

    void reset();

    /**
     * @hide
     */
    void restoreChildrenStartOffset();
    Animation* findAnimation(const String & objName);

    /**
     * @return All the child animations in this AnimationSet. Note that
     * this may include other AnimationSets, which are not expanded.
     */
    std::list<Animation*> getAnimations() {
        return mAnimations;
    }

    bool willChangeTransformationMatrix() {
        return (mFlags & PROPERTY_MORPH_MATRIX_MASK) == PROPERTY_MORPH_MATRIX_MASK;
    }

    bool willChangeBounds() {
        return (mFlags & PROPERTY_CHANGE_BOUNDS_MASK) == PROPERTY_CHANGE_BOUNDS_MASK;
    }

    virtual void onResize(float screenWidth, float screenHeight);
};

#endif
