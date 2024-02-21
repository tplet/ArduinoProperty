//
// Created by Thibault PLET on 22/10/2023.
//

#include <Binder.h>
#include <Bindable.h>

/**
 * Constructor
 */
Binder::Binder()
{
}

/**
 * Bind bindable
 */
void Binder::bind(Bindable * bindable)
{
    bindable->setBinder(this);
}

/**
 * Unbind bindable
 */
void Binder::unbind(Bindable * bindable)
{
    Binder * binder = bindable->getBinder();
    if (binder != nullptr) {
        bindable->setBinder(nullptr);
    }
}
