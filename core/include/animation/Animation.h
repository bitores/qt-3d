#ifndef __Animation_h__
#define __Animation_h__

#include "utils/include/prerequisites.h"
#include "utils/include/Common.h"
#include "base/Object.h"
#include "scripting/lua/LuaEngine.h"
#include "base/Root.h"

class Interpolator;

/**
 * <p>An animation listener receives notifications from an animation.
 * Notifications indicate animation related events, such as the end or the
 * repetition of the animation.</p>
 */
class AnimationListener {
public:
	/**
	 * <p>Notifies the start of the animation.</p>
	 *
	 * @param animation The started animation.
	 */
	virtual void onAnimationStart(Animation* animation) = 0;

	/**
	 * <p>Notifies the end of the animation. This callback is not invoked
	 * for animations with repeat count set to INFINITE.</p>
	 *
	 * @param animation The animation which reached its end.
	 */
	virtual void onAnimationEnd(Animation* animation) = 0;

	/**
	 * <p>Notifies the repetition of the animation.</p>
	 *
	 * @param animation The animation which was repeated.
	 */
	virtual void onAnimationRepeat(Animation* animation) = 0;

	virtual void onAnimationProgress(Animation* animation, float progress) = 0;
};

/**
 * Utility class to parse a string description of a size.
 */
class Description {
public:
	/**
	 * One of Animation.ABSOLUTE, Animation.RELATIVE_TO_SELF, or
	 * Animation.RELATIVE_TO_PARENT.
	 */
	int type;

	/**
	 * The absolute or relative dimension for this Description.
	 */
	float value;

	/**
	 * Size descriptions can appear inthree forms:
	 * <ol>
	 * <li>An absolute size. This is represented by a number.</li>
	 * <li>A size relative to the size of the object being animated. This
	 * is represented by a number followed by "%".</li> *
	 * <li>A size relative to the size of the parent of object being
	 * animated. This is represented by a number followed by "%p".</li>
	 * </ol>
	 * @param value The typed value to parse
	 * @return The parsed version of the description
	 */
//	static Description parseValue(TypedValue value) {
//		Description d = new Description();
//		if (value == null) {
//			d.type = ABSOLUTE;
//			d.value = 0;
//		} else {
//			if (value.type == TypedValue.TYPE_FRACTION) {
//				d.type = (value.data & TypedValue.COMPLEX_UNIT_MASK) ==
//						TypedValue.COMPLEX_UNIT_FRACTION_PARENT ?
//								RELATIVE_TO_PARENT : RELATIVE_TO_SELF;
//				d.value = TypedValue.complexToFloat(value.data);
//				return d;
//			} else if (value.type == TypedValue.TYPE_FLOAT) {
//				d.type = ABSOLUTE;
//				d.value = value.getFloat();
//				return d;
//			} else if (value.type >= TypedValue.TYPE_FIRST_INT &&
//					value.type <= TypedValue.TYPE_LAST_INT) {
//				d.type = ABSOLUTE;
//				d.value = value.data;
//				return d;
//			}
//		}
//
//		d.type = ABSOLUTE;
//		d.value = 0.0f;
//
//		return d;
//	}
};

/**
 * Abstraction for an Animation that can be applied to Views, Surfaces, or
 * other objects. See the {@link android.view.animation animation package
 * description file}.
 */
class Animation : public object_base {
public:
    /**
     * Repeat the animation indefinitely.
     */
	static int E3D_INFINITE;

    /**
     * When the animation reaches the end and the repeat count is INFINTE_REPEAT
     * or a positive value, the animation restarts from the beginning.
     */
    static int RESTART;

    /**
     * When the animation reaches the end and the repeat count is INFINTE_REPEAT
     * or a positive value, the animation plays backward (and then forward again).
     */
    static int REVERSE;

    /**
     * Can be used as the start time to indicate the start time should be the current
     * time when {@link #getTransformation(long, Transformation)} is invoked for the
     * first animation frame. This can is useful for short animations.
     */
    static int START_ON_FIRST_FRAME;

    enum {
    /**
     * The specified dimension is an absolute number of pixels.
     */
    /*static int */E3D_ABSOLUTE = 0,

    /**
     * The specified dimension holds a float and should be multiplied by the
     * height or width of the object being animated.
     */
    /*static int */RELATIVE_TO_SELF = 1,

    /**
     * The specified dimension holds a float and should be multiplied by the
     * height or width of the parent of the object being animated.
     */
    /*static int */RELATIVE_TO_PARENT = 2

    };

    /**
     * Do not reset transform,
	 * when the applyTransformation is called.
	 */
    static int RESETMODE_NONE/* = 0*/;

    /**
	 * Reset transform to it's initial value,
	 * when the applyTransformation is called.
	 */
    static int RESETMODE_ORIGINAL/* = 1*/;

    /**
	 * Reset transform to unit value,
	 * when the applyTransformation is called.
	 */
    static int RESETMODE_UNIT/* = 2*/;

    /**
     * Requests that the content being animated be kept in its current Z
     * order.
     */
    static int ZORDER_NORMAL/* = 0*/;
    
    /**
     * Requests that the content being animated be forced on top of all other
     * content for the duration of the animation.
     */
    static int ZORDER_TOP /*= 1*/;
    
    /**
     * Requests that the content being animated be forced under all other
     * content for the duration of the animation.
     */
    static int ZORDER_BOTTOM/* = -1*/;

    /**
     * Set by {@link #getTransformation(long, Transformation)} when the animation ends.
     */
    bool mEnded;

    /**
     * Set by {@link #startAnimation} when the animation starts.
     */
    bool mUpdate;

    bool mRelative;
    bool mIgnoreFirst;
    /**
     * Set by {@link #getTransformation(long, Transformation)} when the animation starts.
     */
    bool mStarted;

    /**
     * Set by {@link #getTransformation(long, Transformation)} when the animation repeats
     * in REVERSE mode.
     */
    bool mCycleFlip;

    /**
     * This value must be set to true by {@link #initialize(int, int, int, int)}. It
     * indicates the animation was successfully initialized and can be played.
     */
    bool mInitialized;

    /**
     * Indicates whether the animation transformation should be applied before the
     * animation starts. The value of this variable is only relevant if mFillEnabled is true;
     * otherwise it is assumed to be true.
     */
    bool mFillBefore;

    /**
     * Indicates whether the animation transformation should be applied after the
     * animation ends.
     */
    bool mFillAfter;

    /**
     * Indicates whether fillBefore should be taken into account.
     */
    bool mFillEnabled;

    /**
     * The time in milliseconds at which the animation must start;
     */
    long mStartTime /*= -1*/;

    /**
     * The delay in milliseconds after which the animation must start. When the
     * start offset is > 0, the start time of the animation is startTime + startOffset.
     */
    long mStartOffset;

    /**
     * The duration of one animation cycle in milliseconds.
     */
    long mDuration;

    /**
     * The number of times the animation must repeat. By default, an animation repeats
     * indefinitely.
     */
    int mRepeatCount/* = 0*/;

    /**
     * Indicates how many times the animation was repeated.
     */
    int mRepeated/* = 0*/;

    /**
     * The behavior of the animation when it repeats. The repeat mode is either
     * {@link #RESTART} or {@link #REVERSE}.
     *
     */
    int mRepeatMode/* = RESTART*/;

    int mResetMode/* = RESETMODE_UNIT*/;

    /**
     * The interpolator used by the animation to smooth the movement.
     */
    bool mBeFreeInterpolator;
    Interpolator* mInterpolator;

    /**
     * The animation listener to be notified when the animation starts, ends or repeats.
     */
    AnimationListener* mListener;
    String mName;
	bool mCanStop;
	bool mBeStop;
	long mLastStopTime;
	bool isAnimationStop();
	void onStopAnimation(bool beStop);

protected:
	Root* mRoot;

    /**
     * Desired Z order mode during animation.
     */
    int mZAdjustment;

    /**
     * Desired background color behind animation.
     */
    int mBackgroundColor;

    /**
     * scalefactor to apply to pivot points, etc. during animation. Subclasses retrieve the
     * value via getScaleFactor().
     */
    float mScaleFactor;

    /**
     * Don't animate the wallpaper.
     */
    bool mDetachWallpaper;

    bool mMore;
    bool mOneMoreTime;

//    RectF mPreviousRegion/* = new RectF()*/;
//    RectF mRegion /*= new RectF()*/;
//    Transform *mTransformation/* = new Transformation()*/;
//    Transform *mPreviousTransformation/* = new Transformation()*/;

//    CloseGuard guard = CloseGuard.get();

//    Handler* mListenerHandler;
//    Runnable* mOnStart;
//    Runnable* mOnRepeat;
//    Runnable* mOnEnd;
private:
    void _init();
public:
    /**
     * Creates a new animation with a duration of 0ms, the default interpolator, with
     * fillBefore set to true and fillAfter set to false
     */
    Animation(/*GameObject* target, */Root* root, bool canStop = true);
    virtual ~Animation();

//    GameObject* getTarget() { return mTarget; };
    const String& getName() const;
    void setName(const String& name);

    /**
     * Creates a new animation whose parameters come from the specified context and
     * attributes set.
     *
     * @param context the application environment
     * @param attrs the set of attributes holding the animation parameters
     */
//    Animation(Context context, AttributeSet attrs);

public:

    Animation* clone();
    /**
     * Reset the initialization state of this animation.
     *
     * @see #initialize(int, int, int, int)
     */
    virtual void reset();

    /**
     * Cancel the animation. Cancelling an animation invokes the animation
     * listener, if set, to notify the end of the animation.
     * 
     * If you cancel an animation manually, you must call {@link #reset()}
     * before starting the animation again.
     * 
     * @see #reset() 
     * @see #start() 
     * @see #startNow() 
     */
    void cancel();

    /**
     * @hide
     */
    void detach();

    /**
     * Whether or not the animation has been initialized.
     *
     * @return Has this animation been initialized.
     * @see #initialize(int, int, int, int)
     */
    bool isInitialized();

    /**
     * Initialize this animation with the dimensions of the object being
     * animated as well as the objects parents. (This is to support animation
     * sizes being specified relative to these dimensions.)
     *
     * <p>Objects that interpret Animations should call this method when
     * the sizes of the object being animated and its parent are known, and
     * before calling {@link #getTransformation}.
     *
     *
     * @param width Width of the object being animated
     * @param height Height of the object being animated
     * @param parentWidth Width of the animated object's parent
     * @param parentHeight Height of the animated object's parent
     */
    virtual void initialize(int width, int height, int parentWidth, int parentHeight);

    /**
     * Sets the handler used to invoke listeners.
     * 
     * @hide
     */
//    void setListenerHandler(/*Handler handler*/);

    /**
     * Sets the acceleration curve for this animation. The interpolator is loaded as
     * a resource from the specified context.
     *
     * @param context The application environment
     * @param resID The resource identifier of the interpolator to load
     * @attr ref android.R.styleable#Animation_interpolator
     */
//    void setInterpolator(Context context, int resID);

    /**
     * Sets the acceleration curve for this animation. Defaults to a linear
     * interpolation.
     *
     * @param i The interpolator which defines the acceleration curve
     * @attr ref android.R.styleable#Animation_interpolator
     */
    void setInterpolator(Interpolator* i, bool freeInterpolator = true);

    /**
     * When this animation should start relative to the start time. This is most
     * useful when composing complex animations using an {@link AnimationSet }
     * where some of the animations components start at different times.
     *
     * @param startOffset When this Animation should start, in milliseconds from
     *                    the start time of the root AnimationSet.
     * @attr ref android.R.styleable#Animation_startOffset
     */
    virtual void setStartOffset(long startOffset);

    /**
     * How long this animation should last. The duration cannot be negative.
     * 
     * @param durationMillis Duration in milliseconds
     *
     * @throws java.lang.IllegalArgumentException if the duration is < 0
     *
     * @attr ref android.R.styleable#Animation_duration
     */
    virtual void setDuration(long durationMillis);

    /**
     * Ensure that the duration that this animation will run is not longer
     * than <var>durationMillis</var>.  In addition to adjusting the duration
     * itself, this ensures that the repeat count also will not make it run
     * longer than the given time.
     * 
     * @param durationMillis The maximum duration the animation is allowed
     * to run.
     */
    virtual void restrictDuration(long durationMillis);
    
    /**
     * How much to scale the duration by.
     *
     * @param scale The amount to scale the duration.
     */
    virtual void scaleCurrentDuration(float scale);

    /**
     * When this animation should start. When the start time is set to
     * {@link #START_ON_FIRST_FRAME}, the animation will start the first time
     * {@link #getTransformation(long, Transformation)} is invoked. The time passed
     * to this method should be obtained by calling
     * {@link AnimationUtils#currentAnimationTimeMillis()} instead of
     * {@link System#currentTimeMillis()}.
     *
     * @param startTimeMillis the start time in milliseconds
     */
    virtual void setStartTime(long startTimeMillis);

    bool isRunning();

    void run();
    void stop();

    /**
     * Convenience method to start the animation the first time
     * {@link #getTransformation(long, Transformation)} is invoked.
     */
    void start();

    /**
     * Convenience method to start the animation at the current time in
     * milliseconds.
     */
    void startNow();

    /**
     * Defines what this animation should do when it reaches the end. This
     * setting is applied only when the repeat count is either greater than
     * 0 or {@link #INFINITE}. Defaults to {@link #RESTART}. 
     *
     * @param repeatMode {@link #RESTART} or {@link #REVERSE}
     * @attr ref android.R.styleable#Animation_repeatMode
     */
    virtual void setRepeatMode(int repeatMode);

    /**
     * Sets how many times the animation should be repeated. If the repeat
     * count is 0, the animation is never repeated. If the repeat count is
     * greater than 0 or {@link #INFINITE}, the repeat mode will be taken
     * into account. The repeat count is 0 by default.
     *
     * @param repeatCount the number of times the animation should be repeated
     * @attr ref android.R.styleable#Animation_repeatCount
     */
    void setRepeatCount(int repeatCount);

    void setResetMode(int resetMode) { mResetMode = resetMode;}

    /**
     * If fillEnabled is true, this animation will apply the value of fillBefore.
     *
     * @return true if the animation will take fillBefore into account
     * @attr ref android.R.styleable#Animation_fillEnabled
     */
    bool isFillEnabled();

    /**
     * If fillEnabled is true, the animation will apply the value of fillBefore.
     * Otherwise, fillBefore is ignored and the animation
     * transformation is always applied until the animation ends.
     *
     * @param fillEnabled true if the animation should take the value of fillBefore into account
     * @attr ref android.R.styleable#Animation_fillEnabled
     *
     * @see #setFillBefore(bool)
     * @see #setFillAfter(bool)
     */
    void setFillEnabled(bool fillEnabled);

    /**
     * If fillBefore is true, this animation will apply its transformation
     * before the start time of the animation. Defaults to true if
     * {@link #setFillEnabled(bool)} is not set to true.
     * Note that this applies when using an {@link
     * android.view.animation.AnimationSet AnimationSet} to chain
     * animations. The transformation is not applied before the AnimationSet
     * itself starts.
     *
     * @param fillBefore true if the animation should apply its transformation before it starts
     * @attr ref android.R.styleable#Animation_fillBefore
     *
     * @see #setFillEnabled(bool)
     */
    virtual void setFillBefore(bool fillBefore);

    /**
     * If fillAfter is true, the transformation that this animation performed
     * will persist when it is finished. Defaults to false if not set.
     * Note that this applies to individual animations and when using an {@link
     * android.view.animation.AnimationSet AnimationSet} to chain
     * animations.
     *
     * @param fillAfter true if the animation should apply its transformation after it ends
     * @attr ref android.R.styleable#Animation_fillAfter
     *
     * @see #setFillEnabled(bool)
     */
    virtual void setFillAfter(bool fillAfter);

    /**
     * Set the Z ordering mode to use while running the animation.
     * 
     * @param zAdjustment The desired mode, one of {@link #ZORDER_NORMAL},
     * {@link #ZORDER_TOP}, or {@link #ZORDER_BOTTOM}.
     * @attr ref android.R.styleable#Animation_zAdjustment
     */
    void setZAdjustment(int zAdjustment);
    
    /**
     * Set background behind animation.
     *
     * @param bg The background color.  If 0, no background.  Currently must
     * be black, with any desired alpha level.
     */
    void setBackgroundColor(int bg);

    virtual void preTransform() {}

protected:
    /**
     * The scale factor is set by the call to <code>getTransformation</code>. Overrides of 
     * {@link #getTransformation(long, Transformation, float)} will get this value
     * directly. Overrides of {@link #applyTransformation(float, Transformation)} can
     * call this method to get the value.
     * 
     * @return float The scale factor that should be applied to pre-scaled values in
     * an Animation such as the pivot points in {@link ScaleAnimation} and {@link RotateAnimation}.
     */
     float getScaleFactor();
public:
    /**
     * If detachWallpaper is true, and this is a window animation of a window
     * that has a wallpaper background, then the window will be detached from
     * the wallpaper while it runs.  That is, the animation will only be applied
     * to the window, and the wallpaper behind it will remain static.
     *
     * @param detachWallpaper true if the wallpaper should be detached from the animation
     * @attr ref android.R.styleable#Animation_detachWallpaper
     */
    void setDetachWallpaper(bool detachWallpaper);
    /**
     * Gets the acceleration curve type for this animation.
     *
     * @return the {@link Interpolator} associated to this animation
     * @attr ref android.R.styleable#Animation_interpolator
     */
    Interpolator* getInterpolator();

    /**
     * When this animation should start. If the animation has not startet yet,
     * this method might return {@link #START_ON_FIRST_FRAME}.
     *
     * @return the time in milliseconds when the animation should start or
     *         {@link #START_ON_FIRST_FRAME}
     */
    virtual long getStartTime();

    /**
     * How long this animation should last
     *
     * @return the duration in milliseconds of the animation
     * @attr ref android.R.styleable#Animation_duration
     */
    virtual long getDuration();

    /**
     * When this animation should start, relative to StartTime
     *
     * @return the start offset in milliseconds
     * @attr ref android.R.styleable#Animation_startOffset
     */
    long getStartOffset();

    /**
     * Defines what this animation should do when it reaches the end.
     *
     * @return either one of {@link #REVERSE} or {@link #RESTART}
     * @attr ref android.R.styleable#Animation_repeatMode
     */
    int getRepeatMode();

    /**
     * Defines how many times the animation should repeat. The default value
     * is 0.
     *
     * @return the number of times the animation should repeat, or {@link #INFINITE}
     * @attr ref android.R.styleable#Animation_repeatCount
     */
    int getRepeatCount();

    /**
     * If fillBefore is true, this animation will apply its transformation
     * before the start time of the animation. If fillBefore is false and
     * {@link #isFillEnabled() fillEnabled} is true, the transformation will not be applied until
     * the start time of the animation.
     *
     * @return true if the animation applies its transformation before it starts
     * @attr ref android.R.styleable#Animation_fillBefore
     */
    bool getFillBefore();

    /**
     * If fillAfter is true, this animation will apply its transformation
     * after the end time of the animation.
     *
     * @return true if the animation applies its transformation after it ends
     * @attr ref android.R.styleable#Animation_fillAfter
     */
    bool getFillAfter();

    /**
     * Returns the Z ordering mode to use while running the animation as
     * previously set by {@link #setZAdjustment}.
     * 
     * @return Returns one of {@link #ZORDER_NORMAL},
     * {@link #ZORDER_TOP}, or {@link #ZORDER_BOTTOM}.
     * @attr ref android.R.styleable#Animation_zAdjustment
     */
    int getZAdjustment();

    /**
     * Returns the background color behind the animation.
     */
    int getBackgroundColor();

    /**
     * Return value of {@link #setDetachWallpaper(bool)}.
     * @attr ref android.R.styleable#Animation_detachWallpaper
     */
    bool getDetachWallpaper();

    /**
     * <p>Indicates whether or not this animation will affect the transformation
     * matrix. For instance, a fade animation will not affect the matrix whereas
     * a scale animation will.</p>
     *
     * @return true if this animation will change the transformation matrix
     */
    bool willChangeTransformationMatrix();

    /**
     * <p>Indicates whether or not this animation will affect the bounds of the
     * animated view. For instance, a fade animation will not affect the bounds
     * whereas a 200% scale animation will.</p>
     *
     * @return true if this animation will change the view's bounds
     */
    bool willChangeBounds();

    /**
     * <p>Binds an animation listener to this animation. The animation listener
     * is notified of animation events such as the end of the animation or the
     * repetition of the animation.</p>
     *
     * @param listener the animation listener to be notified
     */
    void setAnimationListener(AnimationListener* listener);

protected:
    /**
     * Gurantees that this animation has an interpolator. Will use
     * a AccelerateDecelerateInterpolator is nothing else was specified.
     */
    void ensureInterpolator();
public:
    /**
     * Compute a hint at how long the entire animation may last, in milliseconds.
     * Animations can be written to cause themselves to run for a different
     * duration than what is computed here, but generally this should be
     * accurate.
     */
    virtual long computeDurationHint();
    
    /**
     * Gets the transformation to apply at a specified point in time. Implementations of this
     * method should always replace the specified Transformation or document they are doing
     * otherwise.
     *
     * @param currentTime Where we are in the animation. This is wall clock time.
     * @param outTransformation A transformation object that is provided by the
     *        caller and will be filled in by the animation.
     * @return True if the animation is still running
     */
    virtual bool getTransformation(long currentTime/*, Transform* outTransformation*/);

private:
    void fireAnimationStart();

    void fireAnimationRepeat();

    void fireAnimationEnd();

    void fireAnimationProgress(float progress);

public:
    /**
     * Gets the transformation to apply at a specified point in time. Implementations of this
     * method should always replace the specified Transformation or document they are doing
     * otherwise.
     *
     * @param currentTime Where we are in the animation. This is wall clock time.
     * @param outTransformation A transformation object that is provided by the
     *        caller and will be filled in by the animation.
     * @param scale Scaling factor to apply to any inputs to the transform operation, such
     *        pivot points being rotated or scaled around.
     * @return True if the animation is still running
     */
    virtual bool getTransformation(long currentTime, /*Transform* outTransformation, */float scale);

    virtual void updateAnimation(/*float deltaTime*/);
    void startAnimation();

    /**
     * <p>Indicates whether this animation has started or not.</p>
     *
     * @return true if the animation has started, false otherwise
     */
    bool hasStarted();

    /**
     * <p>Indicates whether this animation has ended or not.</p>
     *
     * @return true if the animation has ended, false otherwise
     */
    bool hasEnded();

public:
    /**
     * Helper for getTransformation. Subclasses should implement this to apply
     * their transforms given an interpolation value.  Implementations of this
     * method should always replace the specified Transformation or document
     * they are doing otherwise.
     * 
     * @param interpolatedTime The value of the normalized time (0.0 to 1.0)
     *        after it has been run through the interpolation function.
     * @param t The Transformation object to fill in with the current
     *        transforms.
     */
    virtual void applyTransformation(float interpolatedTime/*, Transform* t*/);

    /**
     * Convert the information in the description of a size to an actual
     * dimension
     *
     * @param type One of Animation.ABSOLUTE, Animation.RELATIVE_TO_SELF, or
     *             Animation.RELATIVE_TO_PARENT.
     * @param value The dimension associated with the type parameter
     * @param size The size of the object being animated
     * @param parentSize The size of the parent of the object being animated
     * @return The dimension to use for the animation
     */
    float resolveSize(int type, float value, int size, int parentSize);

public:
    /**
     * @param left
     * @param top
     * @param right
     * @param bottom
     * @param invalidate
     * @param transformation
     * 
     * @hide
     */
//    void getInvalidateRegion(int left, int top, int right, int bottom, RectF invalidate, Transform* transformation);
    /**
     * @param left
     * @param top
     * @param right
     * @param bottom
     *
     * @hide
     */
    virtual void initializeInvalidateRegion(int left, int top, int right, int bottom);

protected:
//    voidize() throws Throwable {
//        try {
//            if (guard != null) {
//                guard.warnIfOpen();
//            }
//        }ly {
//            super.finalize();
//        }
//    }

public:
    /**
     * Return true if this animation changes the view's alpha property.
     * 
     * @hide
     */
    virtual bool hasAlpha();

    bool beReverse() { return mCycleFlip; }

    virtual void setRepeatMode(String repeatMode);

    void setRelavie(bool relative) {
        mRelative = relative;
    }
    void setIgnore(bool ignore) {
        mIgnoreFirst = ignore;
    }

    virtual void onResize(float screenWidth, float screenHeight) {}
};

#endif
