#ifndef __AtomicScalar_H__
#define __AtomicScalar_H__

#include "threading/ThreadDefines.h"

/** \addtogroup Core
*  @{
*/
/** \addtogroup General
*  @{
*/
template <class T> class AtomicScalar {

	public:

	AtomicScalar (const T &initial)
		: mField(initial)
	{   }

	AtomicScalar (const AtomicScalar<T> &cousin)
		: mField(cousin.mField)
	{   }

	AtomicScalar ()
	{   }

	void operator= (const AtomicScalar<T> &cousin)
	{
		mField = cousin.mField;
	}

	T get (void) const
	{
		// no lock required here
		// since get will not interfere with set or cas
		// we may get a stale value, but this is ok
		return mField;
	}

	void set (const T &v)
	{
		mField = v;
	}

	bool cas (const T &old, const T &nu)
	{
		OGRE_LOCK_AUTO_MUTEX;
		if (mField != old) return false;
		mField = nu;
		return true;
	}

	T operator++ (void)
	{
		OGRE_LOCK_AUTO_MUTEX;
		return ++mField;
	}

	T operator-- (void)
	{
		OGRE_LOCK_AUTO_MUTEX;
		return --mField;
	}

	T operator++ (int)
	{
		OGRE_LOCK_AUTO_MUTEX;
		return mField++;
	}

	T operator-- (int)
	{
		OGRE_LOCK_AUTO_MUTEX;
		return mField--;
	}

	T operator+=(const T &add)
	{
		OGRE_LOCK_AUTO_MUTEX;
		mField += add;
		return mField;
	}

	T operator-=(const T &sub)
	{
		OGRE_LOCK_AUTO_MUTEX;
		mField -= sub;
		return mField;
	}

	protected:

	OGRE_AUTO_MUTEX;

	volatile T mField;

};
/** @} */
/** @} */
#endif
