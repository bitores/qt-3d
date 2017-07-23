#ifndef __IMesh_h__
#define __IMesh_h__

#include "utils/include/prerequisites.h"
#include "utils/include/platform.h"
#include "rendersystem/RenderOperation.h"
#include "utils/include/AxisAlignedBox.h"

class IMesh
{
protected:
    /// Local bounding box volume
	AxisAlignedBox mAABB;
public:
	// provide data query interface for client.
	virtual void getRenderOperation(RenderOperationList& op) = 0;
	virtual bool hitTest(float x, float y) { return false; }

	virtual void setAlpha(float alpha) {};
	virtual void resize(float width, float height) {}

	IMesh();
	virtual ~IMesh();

	//-----------------------------------------------------------------------
    const AxisAlignedBox& getBounds(void) const
    {
    	return mAABB;
    }
    ////-----------------------------------------------------------------------
    void _setBounds(const AxisAlignedBox& bounds, bool pad)
    {
    	mAABB = bounds;
    	Vector3 max = mAABB.getMaximum();
    	Vector3 min = mAABB.getMinimum();
    	//mBoundRadius = Math::boundingRadiusFromAABB(mAABB);

    	if(pad)
    	{
    		// Pad out the AABB a little, helps with most bounds tests
    		//Vector3 scaler = (max - min) * MeshManager::getSingleton().getBoundsPaddingFactor();
    		//mAABB.setExtents(min  - scaler, max + scaler);
    		// Pad out the sphere a little too
    		//mBoundRadius = mBoundRadius + (mBoundRadius * MeshManager::getSingleton().getBoundsPaddingFactor());
    	}
    	else
    	{
    		mAABB.setExtents(min, max);
    		//mBoundRadius = mBoundRadius;
    	}
    }
};
#endif
