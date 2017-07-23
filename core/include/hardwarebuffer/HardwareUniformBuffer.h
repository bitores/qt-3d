#ifndef __HardwareUniformBuffer__
#define __HardwareUniformBuffer__

// Precompiler options
#include "utils/include/prerequisites.h"
#include "utils/include/SharedPtr.h"
#include "HardwareBuffer.h"
#include "rendersystem/GpuProgramParams.h"
//#include "OgreAny.h"
#include "base/HeaderPrefix.h"


class HardwareBufferManagerBase;

/** \addtogroup Core
*  @{
*/
/** \addtogroup RenderSystem
*  @{
*/
/** Specialisation of HardwareBuffer for a uniform buffer. */
class HardwareUniformBuffer : public HardwareBuffer
{
protected:
	HardwareBufferManagerBase* mMgr;
	String mName;

public:
	/// Should be called by HardwareBufferManager
	HardwareUniformBuffer(HardwareBufferManagerBase* mgr, size_t sizeBytes, HardwareBuffer::Usage usage, bool useShadowBuffer = false, const String& name = "");
	~HardwareUniformBuffer();
	/// Return the manager of this buffer, if any
	HardwareBufferManagerBase* getManager() const { return mMgr; }

	const String& getName() const { return mName; }
};

/** Shared pointer implementation used to share uniform buffers. */
class HardwareUniformBufferSharedPtr : public SharedPtr<HardwareUniformBuffer>
{
public:
	HardwareUniformBufferSharedPtr() : SharedPtr<HardwareUniformBuffer>() {}
	explicit HardwareUniformBufferSharedPtr(HardwareUniformBuffer* buf);
};

#include "base/HeaderSuffix.h"

#endif
