//
// Created by Thibault PLET on 24/10/2023.
//

#ifndef COM_LILICLOUD_ARDUINOPROPERTY_BINDABLE_H
#define COM_LILICLOUD_ARDUINOPROPERTY_BINDABLE_H

#include <Binder.h>

class Bindable {
protected:
    /**
     * Optional binder linked to property and used to be alerted when property value change
     */
    Binder * binder = nullptr;
public:
    /**
     * Constructor
     */
    Bindable();

    /**
     * Attach binder to this property
     */
    virtual void setBinder(Binder * binder);

    /**
     * Get Binder attached
     */
    virtual Binder * getBinder();

};


#endif //COM_LILICLOUD_ARDUINOPROPERTY_BINDABLE_H
