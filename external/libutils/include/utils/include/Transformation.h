#ifndef __Transformation_H__
#define __Transformation_H__

#include "Matrix4.h"

/**
 * Defines the transformation to be applied at
 * one point in time of an Animation.
 *
 */
class Transformation {
public:
    /**
     * Indicates a transformation that has no effect (alpha = 1 and identity matrix.)
     */
     static int TYPE_IDENTITY/* = 0x0*/;
    /**
     * Indicates a transformation that applies an alpha only (uses an identity matrix.)
     */
    static int TYPE_ALPHA/* = 0x1*/;
    /**
     * Indicates a transformation that applies a matrix only (alpha = 1.)
     */
    static int TYPE_MATRIX/* = 0x2*/;
    /**
     * Indicates a transformation that applies an alpha and a matrix.
     */
    static int TYPE_BOTH/* = TYPE_ALPHA | TYPE_MATRIX*/;
protected:
    Matrix4 mMatrix;
    float mAlpha;
    int mTransformationType;

public:
    /**
     * Creates a new transformation with alpha = 1 and the identity matrix.
     */
    Transformation();

    /**
     * Reset the transformation to a state that leaves the object
     * being animated in an unmodified state. The transformation type is
     * {@link #TYPE_BOTH} by default.
     */
    void clear();

    /**
     * Indicates the nature of this transformation.
     *
     * @return {@link #TYPE_ALPHA}, {@link #TYPE_MATRIX},
     *         {@link #TYPE_BOTH} or {@link #TYPE_IDENTITY}.
     */
    int getTransformationType() {
        return mTransformationType;
    }

    /**
     * Sets the transformation type.
     *
     * @param transformationType One of {@link #TYPE_ALPHA},
     *        {@link #TYPE_MATRIX}, {@link #TYPE_BOTH} or
     *        {@link #TYPE_IDENTITY}.
     */
    void setTransformationType(int transformationType) {
        mTransformationType = transformationType;
    }

    /**
     * Clones the specified transformation.
     *
     * @param t The transformation to clone.
     */
    void set(Transformation &t);
    /**
     * Apply this Transformation to an existing Transformation, e.g. apply
     * a scale effect to something that has already been rotated.
     * @param t
     */
    void compose(Transformation &t);

    /**
     * Like {@link #compose(Transformation)} but does this.postConcat(t) of
     * the transformation matrix.
     * @hide
     */
    void postCompose(Transformation &t);

    /**
     * @return The 3x3 Matrix representing the trnasformation to apply to the
     * coordinates of the object being animated
     */
    Matrix4 getMatrix() {
        return mMatrix;
    }

    /**
     * Sets the degree of transparency
     * @param alpha 1.0 means fully opaqe and 0.0 means fully transparent
     */
    void setAlpha(float alpha) {
        mAlpha = alpha;
    }

    /**
     * @return The degree of transparency
     */
    float getAlpha() {
        return mAlpha;
    }

//    public String toString() {
//        StringBuilder sb = new StringBuilder(64);
//        sb.append("Transformation");
//        toShortString(sb);
//        return sb.toString();
//    }

    /**
     * Return a string representation of the transformation in a compact form.
     */
//    public String toShortString() {
//        StringBuilder sb = new StringBuilder(64);
//        toShortString(sb);
//        return sb.toString();
//    }

    /**
     * @hide
     */
//    public void toShortString(StringBuilder sb) {
//        sb.append("{alpha="); sb.append(mAlpha);
//        sb.append(" matrix="); mMatrix.toShortString(sb);
//        sb.append('}');
//    }

    /**
     * Print short string, to optimize dumping.
     * @hide
     */
//    public void printShortString(PrintWriter pw) {
//        pw.print("{alpha="); pw.print(mAlpha);
//        pw.print(" matrix=");
//        mMatrix.printShortString(pw);
//        pw.print('}');
//    }
};
#endif
