//
// Created by Thibault PLET on 22/10/2023.
//

#ifndef COM_LILICLOUD_ARDUINOPROPERTY_BINDER_H
#define COM_LILICLOUD_ARDUINOPROPERTY_BINDER_H

#ifndef COM_LILICLOUD_ARDUINOPROPERTY_BINDABLE_H
#include <Bindable.h>
#endif

class Bindable;

class Binder {
protected:


public:

    /**
     * Constructor
     */
    Binder()
    {
    }

    void dispatch(Bindable * bindable)
    {
        // Nothing to do in base class
    }

    /**
     * Bind bindable
     */
    void bind(Bindable * bindable)
    {
        bindable->setBinder(this);
    }

    /**
     * Unbind bindable
     */
    void unbind(Bindable * bindable)
    {
        Binder * binder = bindable->getBinder();
        if (binder != NULL && binder == *this) {
            bindable->setBinder(NULL);
        }
    }
};

#endif //COM_LILICLOUD_ARDUINOPROPERTY_BINDER_H
