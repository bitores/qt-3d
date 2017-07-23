#ifndef __Transform_h__
#define __Transform_h__

#include "Quaternion.h"
#include "Vector3.h"
#include "Matrix4.h"

enum TransformSpace
{
	/// Transform is relative to the local space
	TS_LOCAL,
	/// Transform is relative to the space of the parent node
	TS_PARENT,
	/// Transform is relative to world space
	TS_WORLD,
	TS_NOT_ADD
};

class ITransformListener
{
public:
	virtual void _notifyTransformChanged() = 0;
};

class Transform
{
public:
	/// Pointer to GameObject who include this
	GameObject* mGameObject;

	std::list<ITransformListener*> mListeners;
protected:

	/// Pointer to parent node
	Transform* mParent;

	typedef std::list<Transform*> TransformList;
	TransformList mChildren;

	/// Stores the Original quaternion of the node relative to it's parent
	/// This variable is supposed NOT to be changed after beening assigned initially
	Quaternion mOriginalOrientation;

	/// Stores the Original position/translation of the node relative to its parent.
	/// This variable is supposed NOT to be changed after beening assigned initially
	Vector3 mOriginalPosition;

	/// Stores the Original scaling factor applied to this node
	/// This variable is supposed NOT to be changed after beening assigned initially
	Vector3 mOriginalScale;

	/// Stores the orientation of the node relative to it's parent.
	Quaternion mOrientation;

	/// Stores the position/translation of the node relative to its parent.
	Vector3 mPosition;

	/// Stores the scaling factor applied to this node
	Vector3 mScale;

	/// Stores whether this node inherits orientation from it's parent
	bool mInheritOrientation;

	/// Stores whether this node inherits scale from it's parent
	bool mInheritScale;

    /// List of children which need updating, used if self is not out of date but children are
    mutable TransformList mChildrenToUpdate;
	mutable bool mNeedParentUpdate;
	/// Flag indicating that all children need to be updated
	mutable bool mNeedChildUpdate;
	/// Flag indicating that parent has been notified about update request
   mutable bool mParentNotified ;

	Matrix4 mCachedTransform;
	mutable bool mCachedTransformOutOfDate;

    Matrix4 mCachedInverseTransform;
    mutable bool mInverseTransformOutOfDate;

	/** Cached combined orientation.
        @par
            This member is the orientation derived by combining the
            local transformations and those of it's parents.
            This is updated when _updateFromParent is called by the
            SceneManager or the nodes parent.
    */
    mutable Quaternion mDerivedOrientation;

    /** Cached combined position.
        @par
            This member is the position derived by combining the
            local transformations and those of it's parents.
            This is updated when _updateFromParent is called by the
            SceneManager or the nodes parent.
    */
    mutable Vector3 mDerivedPosition;

    /** Cached combined scale.
        @par
            This member is the position derived by combining the
            local transformations and those of it's parents.
            This is updated when _updateFromParent is called by the
            SceneManager or the nodes parent.
    */
    mutable Vector3 mDerivedScale;

    /** Triggers the node to update it's combined transforms.
        @par
            This method is called internally by Ogre to ask the node
            to update it's complete transformation based on it's parents
            derived transform.
    */
    virtual void _updateFromParent(void) const;

	/** Class-specific implementation of _updateFromParent.
	@remarks
		Splitting the implementation of the update away from the update call
		itself allows the detail to be overridden without disrupting the 
		general sequence of updateFromParent (e.g. raising events)
	*/
	virtual void updateFromParentImpl(void) const;


	// those methods are supposed to be called within xml_transform_parser
	friend class xml_transform_parser;
	virtual void setOriginalOrientation( const Quaternion& q, bool bSetCurrent = true);
	virtual void setOriginalOrientation( Real w, Real x, Real y, Real z, bool bSetCurrent = true);
	virtual void setOriginalPosition(const Vector3& pos, bool bSetCurrent = true);
	virtual void setOriginalPosition(Real x, Real y, Real z, bool bSetCurrent = true);
	virtual void setOriginalScale(const Vector3& scale, bool bSetCurrent = true);
	virtual void setOriginalScale(Real x, Real y, Real z, bool bSetCurrent = true);

public:
	void addTransformListener(ITransformListener* listener);
	GameObject* getGameObject();
	Transform* getParent();
	void setParent(Transform* parent);
	Matrix4& _getFullTransform();
    Matrix4& _getInverseTransform();

	String toString() {
		return mPosition.toString() + mOrientation.toString();
	}

	Transform();
	Transform(GameObject * go);

	void addChild(Transform *transform);
	void removeChild(Transform *transform);
	void clear();
	void set(const Transform& transform);

	virtual const Quaternion & getOriginalOrientation() const {return mOriginalOrientation;};
	virtual const Vector3 & getOriginalPosition(void) const {return mOriginalPosition;};
	virtual const Vector3 & getOriginalScale(void) const {return mOriginalScale;};

	/** Resets the nodes orientation (local axes as world axes, no rotation).
	@remarks
		Orientations, unlike other transforms, are not always inherited by child nodes.
		Whether or not orientations affect the orientation of the child nodes depends on
		the setInheritOrientation option of the child. In some cases you want a orientating
		of a parent node to apply to a child node (e.g. where the child node is a part of
		the same object, so you want it to be the same relative orientation based on the
		parent's orientation), but not in other cases (e.g. where the child node is just
		for positioning another object, you want it to maintain it's own orientation).
		The default is to inherit as with other transforms.
	@par
		Note that rotations are oriented around the node's origin.
	*/
	virtual void resetOrientation(void);
	/** Returns a quaternion representing the nodes orientation.
	*/
	virtual const Quaternion & getOrientation() const;

	/** Sets the orientation of this node via a quaternion.
	@remarks
		Orientations, unlike other transforms, are not always inherited by child nodes.
		Whether or not orientations affect the orientation of the child nodes depends on
		the setInheritOrientation option of the child. In some cases you want a orientating
		of a parent node to apply to a child node (e.g. where the child node is a part of
		the same object, so you want it to be the same relative orientation based on the
		parent's orientation), but not in other cases (e.g. where the child node is just
		for positioning another object, you want it to maintain it's own orientation).
		The default is to inherit as with other transforms.
	@par
		Note that rotations are oriented around the node's origin.
	*/
	virtual void setOrientation( const Quaternion& q );

	/** Sets the orientation of this node via quaternion parameters.
	@remarks
		Orientations, unlike other transforms, are not always inherited by child nodes.
		Whether or not orientations affect the orientation of the child nodes depends on
		the setInheritOrientation option of the child. In some cases you want a orientating
		of a parent node to apply to a child node (e.g. where the child node is a part of
		the same object, so you want it to be the same relative orientation based on the
		parent's orientation), but not in other cases (e.g. where the child node is just
		for positioning another object, you want it to maintain it's own orientation).
		The default is to inherit as with other transforms.
	@par
		Note that rotations are oriented around the node's origin.
	*/
	virtual void setOrientation( Real w, Real x, Real y, Real z);

	/** Sets the position of the node relative to it's parent.
	*/
	virtual void setPosition(const Vector3& pos);

	/** Sets the position of the node relative to it's parent.
	*/
	virtual void setPosition(Real x, Real y, Real z);

	/** Gets the position of the node relative to it's parent.
	*/
	virtual const Vector3 & getPosition(void) const;

	const Quaternion& getQuaternion() const;

			/** Tells the node whether it should inherit orientation from it's parent node.
	@remarks
		Orientations, unlike other transforms, are not always inherited by child nodes.
		Whether or not orientations affect the orientation of the child nodes depends on
		the setInheritOrientation option of the child. In some cases you want a orientating
		of a parent node to apply to a child node (e.g. where the child node is a part of
		the same object, so you want it to be the same relative orientation based on the
		parent's orientation), but not in other cases (e.g. where the child node is just
		for positioning another object, you want it to maintain it's own orientation).
		The default is to inherit as with other transforms.
	@param inherit If true, this node's orientation will be affected by its parent's orientation.
		If false, it will not be affected.
	*/
	virtual void setInheritOrientation(bool inherit);

	/** Returns true if this node is affected by orientation applied to the parent node.
	@remarks
		Orientations, unlike other transforms, are not always inherited by child nodes.
		Whether or not orientations affect the orientation of the child nodes depends on
		the setInheritOrientation option of the child. In some cases you want a orientating
		of a parent node to apply to a child node (e.g. where the child node is a part of
		the same object, so you want it to be the same relative orientation based on the
		parent's orientation), but not in other cases (e.g. where the child node is just
		for positioning another object, you want it to maintain it's own orientation).
		The default is to inherit as with other transforms.
	@remarks
		See setInheritOrientation for more info.
	*/
	virtual bool getInheritOrientation(void) const;

	/** Tells the node whether it should inherit scaling factors from it's parent node.
	@remarks
		Scaling factors, unlike other transforms, are not always inherited by child nodes.
		Whether or not scalings affect the size of the child nodes depends on the setInheritScale
		option of the child. In some cases you want a scaling factor of a parent node to apply to
		a child node (e.g. where the child node is a part of the same object, so you want it to be
		the same relative size based on the parent's size), but not in other cases (e.g. where the
		child node is just for positioning another object, you want it to maintain it's own size).
		The default is to inherit as with other transforms.
	@param inherit If true, this node's scale will be affected by its parent's scale. If false,
		it will not be affected.
	*/
	virtual void setInheritScale(bool inherit);

	/** Returns true if this node is affected by scaling factors applied to the parent node.
	@remarks
		See setInheritScale for more info.
	*/
	virtual bool getInheritScale(void) const;

	/** Sets the scaling factor applied to this node.
	@remarks
		Scaling factors, unlike other transforms, are not always inherited by child nodes.
		Whether or not scalings affect the size of the child nodes depends on the setInheritScale
		option of the child. In some cases you want a scaling factor of a parent node to apply to
		a child node (e.g. where the child node is a part of the same object, so you want it to be
		the same relative size based on the parent's size), but not in other cases (e.g. where the
		child node is just for positioning another object, you want it to maintain it's own size).
		The default is to inherit as with other transforms.
	@par
		Note that like rotations, scalings are oriented around the node's origin.
	*/
	virtual void setScale(const Vector3& scale);

	/** Sets the scaling factor applied to this node.
	@remarks
		Scaling factors, unlike other transforms, are not always inherited by child nodes.
		Whether or not scalings affect the size of the child nodes depends on the setInheritScale
		option of the child. In some cases you want a scaling factor of a parent node to apply to
		a child node (e.g. where the child node is a part of the same object, so you want it to be
		the same relative size based on the parent's size), but not in other cases (e.g. where the
		child node is just for positioning another object, you want it to maintain it's own size).
		The default is to inherit as with other transforms.
	@par
		Note that like rotations, scalings are oriented around the node's origin.
	*/
	virtual void setScale(Real x, Real y, Real z);

	/** Gets the scaling factor of this node.
	*/
	virtual const Vector3 & getScale(void) const;

	/** Scales the node, combining it's current scale with the passed in scaling factor.
	@remarks
		This method applies an extra scaling factor to the node's existing scale, (unlike setScale
		which overwrites it) combining it's current scale with the new one. E.g. calling this
		method twice with Vector3(2,2,2) would have the same effect as setScale(Vector3(4,4,4)) if
		the existing scale was 1.
	@par
		Note that like rotations, scalings are oriented around the node's origin.
	*/
	virtual void scale(const Vector3& scale);

	/** Scales the node, combining it's current scale with the passed in scaling factor.
	@remarks
		This method applies an extra scaling factor to the node's existing scale, (unlike setScale
		which overwrites it) combining it's current scale with the new one. E.g. calling this
		method twice with Vector3(2,2,2) would have the same effect as setScale(Vector3(4,4,4)) if
		the existing scale was 1.
	@par
		Note that like rotations, scalings are oriented around the node's origin.
	*/
	virtual void scale(Real x, Real y, Real z);
	/** Moves the node along the Cartesian axes.
		@par
			This method moves the node by the supplied vector along the
			world Cartesian axes, i.e. along world x,y,z
		@param
			d Vector with x,y,z values representing the translation.
		@param
			relativeTo The space which this transform is relative to.
	*/
	virtual void translate(const Vector3& d, TransformSpace relativeTo = TS_PARENT);
	/** Moves the node along the Cartesian axes.
		@par
			This method moves the node by the supplied vector along the
			world Cartesian axes, i.e. along world x,y,z
		@param
			x
		@param
			y
		@param
			z Real x, y and z values representing the translation.
		@param
		relativeTo The space which this transform is relative to.
	*/
	virtual void translate(Real x, Real y, Real z, TransformSpace relativeTo = TS_PARENT);
	/** Moves the node along arbitrary axes.
		@remarks
			This method translates the node by a vector which is relative to
			a custom set of axes.
		@param
			axes A 3x3 Matrix containg 3 column vectors each representing the
			axes X, Y and Z respectively. In this format the standard cartesian
			axes would be expressed as:
			<pre>
			1 0 0
			0 1 0
			0 0 1
			</pre>
			i.e. the identity matrix.
		@param
			move Vector relative to the axes above.
		@param
		relativeTo The space which this transform is relative to.
	*/
	virtual void translate(const Matrix3& axes, const Vector3& move, TransformSpace relativeTo = TS_PARENT);
	/** Moves the node along arbitrary axes.
		@remarks
		This method translates the node by a vector which is relative to
		a custom set of axes.
		@param
			axes A 3x3 Matrix containg 3 column vectors each representing the
			axes X, Y and Z respectively. In this format the standard cartesian
			axes would be expressed as
			<pre>
			1 0 0
			0 1 0
			0 0 1
			</pre>
			i.e. the identity matrix.
		@param
			x,y,z Translation components relative to the axes above.
		@param
			relativeTo The space which this transform is relative to.
	*/
	virtual void translate(const Matrix3& axes, Real x, Real y, Real z, TransformSpace relativeTo = TS_PARENT);

	/** Rotate the node around the Z-axis.
	*/
	virtual void roll(const Radian& angle, TransformSpace relativeTo = TS_LOCAL);

	/** Rotate the node around the X-axis.
	*/
	virtual void pitch(const Radian& angle, TransformSpace relativeTo = TS_LOCAL);

	/** Rotate the node around the Y-axis.
	*/
	virtual void yaw(const Radian& angle, TransformSpace relativeTo = TS_LOCAL);

	/** Rotate the node around an arbitrary axis.
	*/
	virtual void rotate(const Vector3& axis, const Radian& angle, TransformSpace relativeTo = TS_LOCAL);

	/** Rotate the node around an arbitrary axis using a Quarternion.
	*/
	virtual void rotate(const Quaternion& q, TransformSpace relativeTo = TS_LOCAL);

	/** Gets the local position, relative to this node, of the given world-space position */
	virtual Vector3 convertWorldToLocalPosition( const Vector3 &worldPos );

	/** Gets the world position of a point in the node local space
		useful for simple transforms that don't require a child node.*/
	virtual Vector3 convertLocalToWorldPosition( const Vector3 &localPos );

	/** Gets the local orientation, relative to this node, of the given world-space orientation */
	virtual Quaternion convertWorldToLocalOrientation( const Quaternion &worldOrientation );

	/** Gets the world orientation of an orientation in the node local space
		useful for simple transforms that don't require a child node.*/
	virtual Quaternion convertLocalToWorldOrientation( const Quaternion &localOrientation );

	/** Sets the final world position of the node directly.
	@remarks
		It's advisable to use the local setPosition if possible
	*/
	virtual void _setDerivedPosition(const Vector3& pos);

	/** Sets the final world orientation of the node directly.
	@remarks
	It's advisable to use the local setOrientation if possible, this simply does
	the conversion for you.
	*/
	virtual void _setDerivedOrientation(const Quaternion& q);

	/** Gets the orientation of the node as derived from all parents.
	*/
	virtual const Quaternion & _getDerivedOrientation(void) const;

	/** Gets the position of the node as derived from all parents.
	*/
	virtual const Vector3 & _getDerivedPosition(void) const;

	/** Gets the scaling factor of the node as derived from all parents.
	*/
	virtual const Vector3 & _getDerivedScale(void) const;

	/** To be called in the event of transform changes to this node that require it's recalculation.
	@remarks
		This not only tags the node state as being 'dirty', it also requests it's parent to
		know about it's dirtiness so it will get an update next time.
	@param forceParentUpdate Even if the node thinks it has already told it's
		parent, tell it anyway
	*/
	virtual void needUpdate(bool forceParentUpdate = false);

	/** Called by children to notify their parent that they need an update.
	@param forceParentUpdate Even if the node thinks it has already told it's
		parent, tell it anyway
	*/
	virtual void requestUpdate(Transform* child, bool forceParentUpdate = false);
	/** Internal method to update the Node.
		@note
			Updates this node and any relevant children to incorporate transforms etc.
			Don't call this yourself unless you are writing a SceneManager implementation.
		@param
			updateChildren If true, the update cascades down to all children. Specify false if you wish to
			update children separately, e.g. because of a more selective SceneManager implementation.
		@param
			parentHasChanged This flag indicates that the parent xform has changed,
				so the child should retrieve the parent's xform and combine it with its own
				even if it hasn't changed itself.
	*/
	virtual void _update(bool updateChildren, bool parentHasChanged);
};
#endif
