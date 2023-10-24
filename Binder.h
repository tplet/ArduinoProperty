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

    void dispatch(Bindable * bindable);

    /**
     * Bind bindable
     */
    void bind(Bindable * bindable);

    /**
     * Unbind bindable
     */
    void unbind(Bindable * bindable);
};

#endif //COM_LILICLOUD_ARDUINOPROPERTY_BINDER_H
