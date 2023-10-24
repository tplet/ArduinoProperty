//
// Created by Thibault PLET on 24/10/2023.
//

#ifndef COM_LILICLOUD_ARDUINOPROPERTY_BINDABLE_H
#define COM_LILICLOUD_ARDUINOPROPERTY_BINDABLE_H

#ifndef COM_LILICLOUD_ARDUINOPROPERTY_BINDER_H
#include <Binder.h>
#endif

class Binder;

class Bindable {
protected:
    /**
     * Optional binder linked to property and used to be alerted when property value change
     */
    Binder * binder = NULL;
public:
    /**
     * Constructor
     */
    Bindable()
    {
        
    }

    /**
     * Attach binder to this property
     */
    void setBinder(Binder * binder)
    {
        this->binder = binder;
    }

    /**
     * Get Binder attached
     */
    Binder * getBinder()
    {
        return this->binder;
    }

};


#endif //COM_LILICLOUD_ARDUINOPROPERTY_BINDABLE_H
