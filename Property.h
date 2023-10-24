//
// Created by Thibault PLET on 28/05/2016.
//

#ifndef COM_LILICLOUD_ARDUINOPROPERTY_PROPERTY_H
#define COM_LILICLOUD_ARDUINOPROPERTY_PROPERTY_H

#include <Bindable.h>

template<typename T>
class Property : public Bindable {
protected:
    /**
     * Value stored
     */
    T value;

    /**
     * Flag to indicate if value has been changed during last assignment
     */
    bool changed;

public:
    /**
     * Constructor
     */
    Property() : Bindable()
    {
        this->changed = true;
    }

    /**
     * Constructor
     *
     * @param T initValue Init value to affect on init
     */
    Property(T initValue) : Bindable()
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

};


#endif //COM_LILICLOUD_ARDUINOPROPERTY_PROPERTY_H
