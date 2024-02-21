//
// Created by Thibault PLET on 26/10/2023.
//

#ifndef COM_LILICLOUD_ARDUINOPROPERTY_BINDABLEPROPERTY_H
#define COM_LILICLOUD_ARDUINOPROPERTY_BINDABLEPROPERTY_H

#include <Bindable.h>

template<typename T>
class BindableProperty : public Bindable {
protected:
    /**
     * Property attached
     */
    Property<T> * property;

public:
    /**
     * Constructor
     */
    BindableProperty(Property<T> property) : Bindable()
    {
        this->property = property;
    }

    /**
     * Set value
     *
     * @param T value Value to store
     */
    T set(T value)
    {
        this->property->set(value);


        // Dispatch to binder if exists
        if (this->binder != NULL && this->property->isChanged()) {
            this->binder->dispatch(this);
        }

        return this->property->get();
    }

    /**
     * Get value
     */
    T get()
    {
        return this->property->get();
    }

    /**
     * Flag to indicate if value has been changed during last assignment
     */
    bool isChanged()
    {
        return this->property->isChanged();
    }

};


#endif //COM_LILICLOUD_ARDUINOPROPERTY_BINDABLEPROPERTY_H
