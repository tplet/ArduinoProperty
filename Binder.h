//
// Created by Thibault PLET on 22/10/2023.
//

#ifndef COM_LILICLOUD_ARDUINOPROPERTY_BINDER_H
#define COM_LILICLOUD_ARDUINOPROPERTY_BINDER_H

class Bindable;

class Binder {
protected:


public:

    /**
     * Constructor
     */
    Binder();

    virtual void dispatch(Bindable * bindable) = 0;

    /**
     * Bind bindable
     */
    virtual void bind(Bindable * bindable);

    /**
     * Unbind bindable
     */
    virtual void unbind(Bindable * bindable);
};

#endif //COM_LILICLOUD_ARDUINOPROPERTY_BINDER_H
