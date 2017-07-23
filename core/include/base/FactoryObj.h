#ifndef _FactoryObj_H__
#define _FactoryObj_H__

#include "utils/include/prerequisites.h"

	/** Abstract factory class. Does nothing by itself, but derived classes can add
        functionality.
    */
    template< typename T > class FactoryObj
    {
    public:
        virtual ~FactoryObj() {}

        /** Returns the factory type.
            @return
                The factory type.
        */
        virtual const String& getType() const = 0;

        /** Creates a new object.
        @param name Name of the object to create
        @return
            An object created by the factory. The type of the object depends on
            the factory.
        */
        virtual T* createInstance( const String& name ) = 0;    
        /** Destroys an object which was created by this factory.
        @param ptr Pointer to the object to destroy
        */
        virtual void destroyInstance( T* ) = 0;    
    };
#endif
