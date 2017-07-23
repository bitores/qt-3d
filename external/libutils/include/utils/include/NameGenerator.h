#ifndef __NameGenerator_H__
#define __NameGenerator_H__

#include "String.h"

//#if defined ( OGRE_GCC_VISIBILITY )
//#   pragma GCC visibility push(default)
//#endif

#include <sstream>

//#if defined ( OGRE_GCC_VISIBILITY )
//#   pragma GCC visibility pop
//#endif

//#include "OgreHeaderPrefix.h"

#include "threading/ThreadDefines.h"

/** \addtogroup Core
*  @{
*/
/** \addtogroup General
*  @{
*/

/// Utility class to generate a sequentially numbered series of names
class NameGenerator
{
protected:
	String mPrefix;
	unsigned long long int mNext;
	OGRE_AUTO_MUTEX;
public:
	NameGenerator(const NameGenerator& rhs)
		: mPrefix(rhs.mPrefix), mNext(rhs.mNext) {}

	NameGenerator(const String& prefix) : mPrefix(prefix), mNext(1) {}

	/// Generate a new name
	String generate()
	{
		OGRE_LOCK_AUTO_MUTEX;
		StringStream s;
		s << mPrefix << mNext++;
		return s.str();
	}

	/// Reset the internal counter
	void reset()
	{
		OGRE_LOCK_AUTO_MUTEX;
		mNext = 1ULL;
	}

	/// Manually set the internal counter (use caution)
	void setNext(unsigned long long int val)
	{
		OGRE_LOCK_AUTO_MUTEX;
		mNext = val;
	}

	/// Get the internal counter
	unsigned long long int getNext() const
	{
		// lock even on get because 64-bit may not be atomic read
		OGRE_LOCK_AUTO_MUTEX;
		return mNext;
	}
};

/** @} */
/** @} */
#endif
