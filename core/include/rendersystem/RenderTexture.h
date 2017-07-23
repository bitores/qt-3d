#ifndef __RenderTexture__h
#define __RenderTexture__h

#include "utils/include/prerequisites.h"
#include "utils/include/PixelFormat.h"
#include "RenderTarget.h"

/** \addtogroup Core
*  @{
*/
/** \addtogroup RenderSystem
*  @{
*/
/** This class represents a RenderTarget that renders to a Texture. There is no 1 on 1
	relation between Textures and RenderTextures, as there can be multiple
	RenderTargets rendering to different mipmaps, faces (for cubemaps) or slices (for 3D textures)
	of the same Texture.
*/
class RenderTexture : public RenderTarget
{
public:
    RenderTexture(Root*root, HardwarePixelBuffer *buffer, size_t zoffset);
    virtual ~RenderTexture();

	virtual void copyContentsToMemory(const PixelBox &dst, FrameBuffer buffer);
	PixelFormat suggestPixelFormat() const;

protected:
	HardwarePixelBuffer *mBuffer;
	size_t mZOffset;
};


/** This class represents a render target that renders to multiple RenderTextures
	at once. Surfaces can be bound and unbound at will, as long as the following constraints
	are met:
	- All bound surfaces have the same size
	- All bound surfaces have the same bit depth
	- Target 0 is bound
*/
class MultiRenderTarget : public RenderTarget
{
public:
	MultiRenderTarget(Root* root, const String &name);

	/** Bind a surface to a certain attachment point.
        @param attachment	0 .. mCapabilities->getNumMultiRenderTargets()-1
		@param target		RenderTexture to bind.

		It does not bind the surface and fails with an exception (ERR_INVALIDPARAMS) if:
		- Not all bound surfaces have the same size
		- Not all bound surfaces have the same internal format
	*/

	virtual void bindSurface(size_t attachment, RenderTexture *target)
	{
		for (size_t i = mBoundSurfaces.size(); i <= attachment; ++i)
		{
			mBoundSurfaces.push_back(0);
		}
		mBoundSurfaces[attachment] = target;

		bindSurfaceImpl(attachment, target);
	}



	/** Unbind attachment.
	*/

	virtual void unbindSurface(size_t attachment)
	{
		if (attachment < mBoundSurfaces.size())
			mBoundSurfaces[attachment] = 0;
		unbindSurfaceImpl(attachment);
	}

	/** Error throwing implementation, it's not possible to write a MultiRenderTarget
		to disk.
	*/
	virtual void copyContentsToMemory(const PixelBox &dst, FrameBuffer buffer);

	/// Irrelevant implementation since cannot copy
	PixelFormat suggestPixelFormat() const { return PF_UNKNOWN; }

	typedef vector<RenderTexture*> BoundSufaceList;
	/// Get a list of the surfaces which have been bound
	const BoundSufaceList& getBoundSurfaceList() const { return mBoundSurfaces; }

	/** Get a pointer to a bound surface */
	RenderTexture* getBoundSurface(size_t index)
	{
		assert (index < mBoundSurfaces.size());
		return mBoundSurfaces[index];
	}


protected:
	BoundSufaceList mBoundSurfaces;

	/// implementation of bindSurface, must be provided
	virtual void bindSurfaceImpl(size_t attachment, RenderTexture *target) = 0;
	/// implementation of unbindSurface, must be provided
	virtual void unbindSurfaceImpl(size_t attachment) = 0;


};
/** @} */
/** @} */

#endif
