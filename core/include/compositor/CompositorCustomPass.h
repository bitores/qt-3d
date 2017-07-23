#ifndef __CompositionCustomPass_h__
#define __CompositionCustomPass_h__

#include "compositor/CompositorInstance.h"

/** Interface for custom composition passes, allowing custom operations (in addition to
*	the quad, scene and clear operations) in composition passes.
*	@see CompositorManager::registerCustomCompositionPass
*/
class CompositorCustomPass
{
public:
	/** Create a custom composition operation.
		@param pass The CompositionPass that triggered the request
		@param instance The compositor instance that this operation will be performed in
		@remarks This call only happens once during creation. The RenderSystemOperation will
		get called each render.
		@remarks The created operation must be instanciated using the OGRE_NEW macro.
	*/
	virtual CompositorInstance::RenderSystemOperation* createOperation(
		CompositorInstance* instance, const CompositorPass* pass) = 0;

protected:
	virtual ~CompositorCustomPass() {}
};


#endif //__CompositionCustomPass_h__
