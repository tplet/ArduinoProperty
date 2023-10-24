//
// Created by Thibault PLET on 24/10/2023.
//

#include <Bindable.h>

/**
 * Constructor
 */
Bindable::Bindable()
{
    
}

/**
 * Attach binder to this property
 */
void Bindable::setBinder(Binder * binder)
{
    this->binder = binder;
}

/**
 * Get Binder attached
 */
Binder * Bindable::getBinder()
{
    return this->binder;
}

