//
// Created by Thibault PLET on 09/09/2020.
//

#ifndef COM_OSTERES_AUTOMATION_MEMORY_ANIMATEDPROPERTY_H
#define COM_OSTERES_AUTOMATION_MEMORY_ANIMATEDPROPERTY_H

#include <Property.h>

template<typename T>
class AnimatedProperty : public Property<T> {
public:

    /**
     * Constructor
     */
    AnimatedProperty() : Property<T>()
    {
    }

    /**
     * Constructor
     *
     * @param T initValue Init value to affect on init
     */
    AnimatedProperty(T initValue, float speedValue) : Property<T>(initValue)
    {
        this->speed = speedValue;
    }

    /**
     * Set current value directly
     */
    virtual void setCurrentValue(T value)
    {
        this->set(value);
    }

    /**
     * Get current value
     */
    virtual T getCurrentValue()
    {
        return this->get();
    }

    /**
     * Set target value
     */
    virtual void setTargetValue(T value)
    {
        this->targetValue = value;
    }

    /**
     * Get target value
     */
    virtual T getTargetValue()
    {
        return this->targetValue;
    }

    /**
     * Get speed (between 0 and 1)
     */
    virtual float getSpeed()
    {
        return this->speed;
    }
    
    /**
     * Set speed (between 0 and 1)
     */
    virtual void setSpeed(float value)
    {
        this->speed = value;
    }

    /**
     * Animate if needed and return current value
     */
    virtual T animate()
    {
        T v = this->get();
        if (this->targetValue != v) {
            v += ceil(speed * ((signed int)this->targetValue - (signed int)v));
            this->set(v);
    
            if (abs((signed int)this->targetValue - (signed int)v) <= 1) {
                this->set(this->targetValue);
            }
        }
    }

protected:
    /**
     * Target value. It's the value targeted during animation.
     * At the animation end, value = targetValue
     */
    T targetValue;

    /**
     * Animation flag
     * Enable during animation.
     */
    bool animated = false;

    /**
     * Speed for animate
     * Value should be between 0 (excluded) and 1
     */
    float speed = 0.1;
};

#endif //COM_OSTERES_AUTOMATION_MEMORY_ANIMATEDPROPERTY_H
