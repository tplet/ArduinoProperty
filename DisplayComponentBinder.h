//
// Created by Thibault PLET on 22/10/2023.
//

#ifndef COM_LILICLOUD_ARDUINOPROPERTY_DISPLAYCOMPONENTBINDER_H
#define COM_LILICLOUD_ARDUINOPROPERTY_DISPLAYCOMPONENTBINDER_H

#include <Binder.h>
#include <DisplayComponent.h>

class DisplayComponentBinder : Binder {
protected:
    /**
     * Display component to dispatch
     */
    DisplayComponent * displayComponent;

public:

    /**
     * Constructor
     */
    DisplayComponentBinder(DisplayComponent * displayComponent)
    {
        this->displayComponent = displayComponent;
    }

    void dispatch(Property * property)
    {
        // Re-draw display component
        this->displayComponent->draw();
    }
};

#endif //COM_LILICLOUD_ARDUINOPROPERTY_DISPLAYCOMPONENTBINDER_H
