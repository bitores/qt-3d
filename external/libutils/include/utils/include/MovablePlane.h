#ifndef __MovablePlane_H__
#define __MovablePlane_H__

#include "prerequisites.h"
#include "Plane.h"

/** \addtogroup Core
*  @{
*/
/** \addtogroup Scene
*  @{
*/
/** Definition of a Plane that may be attached to a node, and the derived
    details of it retrieved simply.
@remarks
    This plane is not here for rendering purposes, it's to allow you to attach
    planes to the scene in order to have them move and follow nodes on their
    own, which is useful if you're using the plane for some kind of calculation,
    e.g. reflection.
*/
class _un_export MovablePlane : public Plane/*, public MovableObject*/
{
protected:
    mutable Plane mDerivedPlane;
    mutable Vector3 mLastTranslate;
    mutable Quaternion mLastRotate;
//     AxisAlignedBox mNullBB;
    mutable bool mDirty;
    static String msMovableType;
public:

    MovablePlane(const String& name);
    MovablePlane (const Plane& rhs);
    /** Construct a plane through a normal, and a distance to move the plane along the normal.*/
    MovablePlane (const Vector3& rkNormal, Real fConstant);
    MovablePlane (const Vector3& rkNormal, const Vector3& rkPoint);
    MovablePlane (const Vector3& rkPoint0, const Vector3& rkPoint1,
        const Vector3& rkPoint2);
    ~MovablePlane() {}
    /// Overridden from MovableObject
    //void _notifyCurrentCamera(Camera*) { /* don't care */ }
    /// Overridden from MovableObject
//     const AxisAlignedBox& getBoundingBox(void) const { return mNullBB; }
    /// Overridden from MovableObject
    Real getBoundingRadius(void) const { return 0.0f; }
    /// Overridden from MovableObject
    void _updateRenderQueue(/*RenderQueue**/) { /* do nothing */}
    /// Overridden from MovableObject
    const String& getMovableType(void) const;
    /// Get the derived plane as transformed by its parent node. 
    const Plane& _getDerivedPlane(void) const;
	/// @copydoc MovableObject::visitRenderables
	//void visitRenderables(Renderable::Visitor* visitor, bool debugRenderables = false)
 //           {
 //               /* do nothing */
 //               (void)visitor;
 //               (void)debugRenderables;
 //           }

};
/** @} */
/** @} */
#endif