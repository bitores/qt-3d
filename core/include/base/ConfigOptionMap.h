#ifndef _ConfigOptionMap_H__
#define _ConfigOptionMap_H__

#include "utils/include/prerequisites.h"
#include "utils/include/StringVector.h"
#include "utils/include/String.h"


/** \addtogroup Core
*  @{
*/
/** \addtogroup General
*  @{
*/
/** Packages the details of a configuration option.
	@remarks
		Used for RenderSystem::getConfigOptions. If immutable is true, this
		option must be disabled for modifying.
*/
typedef struct _ConfigOption
{
	String name;
	String currentValue;
	StringVector possibleValues;
	bool immutable;
} ConfigOption;

typedef map< String, ConfigOption > ConfigOptionMap;
/** @} */
/** @} */

#endif
