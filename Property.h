//
// Created by Thibault PLET on 28/05/2016.
//

#ifndef COM_LILICLOUD_ARDUINOPROPERTY_PROPERTY_H
#define COM_LILICLOUD_ARDUINOPROPERTY_PROPERTY_H

#include <Binder.h>

template<typename T>
class Property {
protected:
    /**
     * Value stored
     */
    T value;

    /**
     * Flag to indicate if value has been changed during last assignment
     */
    bool changed;

    /**
     * Optional binder linked to property and used to be alerted when property value change
     */
    Binder * binder = NULL;
public:
    /**
     * Constructor
     */
    Property()
    {
        this->changed = true;
    }

    /**
     * Constructor
     *
     * @param T initValue Init value to affect on init
     */
    Property(T initValue)
    {
        this->set(initValue);
        this->changed = true;
    }

    /**
     * Set value
     *
     * @param T value Value to store
     */
    T set(T value)
    {
        if (this->value != value) {
            this->changed = true;
            this->value = value;

            // Dispatch to binder if exists
            if (this->binder != NULL) {
                this->binder->dispatch(this);
            }
        } else {
            this->changed = false;
        }

        return this->value;
    }

    /**
     * Get value
     */
    T get()
    {
        return this->value;
    }

    /**
     * Flag to indicate if value has been changed during last assignment
     */
    bool isChanged()
    {
        return this->changed;
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


#endif //COM_LILICLOUD_ARDUINOPROPERTY_PROPERTY_H
