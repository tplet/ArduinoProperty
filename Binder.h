//
// Created by Thibault PLET on 22/10/2023.
//

#ifndef COM_LILICLOUD_ARDUINOPROPERTY_BINDER_H
#define COM_LILICLOUD_ARDUINOPROPERTY_BINDER_H

#include <Property.h>

class Binder {
protected:


public:

    /**
     * Constructor
     */
    Binder()
    {
    }

    void dispatch(Property * property)
    {
        // Nothing to do in base class
    }

    /**
     * Bind property
     */
    void bind(Property * property)
    {
        property->setBinder(this);
    }

    /**
     * Unbind property
     */
    void unbind(Property * Property)
    {
        Binder * binder = property->getBinder();
        if (binder != NULL && binder == *this) {
            property->setBinder(NULL);
        }
    }
};

#endif //COM_LILICLOUD_ARDUINOPROPERTY_BINDER_H
