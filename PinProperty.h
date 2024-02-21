//
// Created by Thibault PLET on 23/04/2017.
//

#ifndef COM_OSTERES_ARDUINOPROPERTY_PINPROPERTY_H
#define COM_OSTERES_ARDUINOPROPERTY_PINPROPERTY_H

#include <Property.h>

template<typename T>
class PinProperty : public Property<T> {
protected:

    /**
     * Pin to read
     */
    unsigned int pin = 0;

    /**
     * Flag to indicate if pin is analog or digital
     */
    bool digital = false;

    /**
     * Flag t indicate if pin is input or output
     * For analog property, mandatory output
     */
    bool input = true;

public:

    /**
     * Constructor
     * Input mode
     *
     * @param pin Pin address
     * @param digital Flag to indicate if pin is digital (true) or analog (false)
     */
    PinProperty(unsigned int pin, bool digital) : Property<T>()
    {
        this->construct(pin, digital, true);
    }

    /**
     * Constructor
     *
     * @param pin Pin address
     * @param digital Flag to indicate if pin is digital (true) or analog (false)
     * @param input Flag to indicate if pin is in input mode (true) or output mode (false)
     */
    PinProperty(unsigned int pin, bool digital, bool input) : Property<T>()
    {
        this->construct(pin, digital, input);
    }

    /**
     * Constructor
     *
     * @param T initValue Initial property value
     * @param pin Pin address
     * @param digital Flag to indicate if pin is digital (true) or analog (false)
     * @param input Flag to indicate if pin is in input mode (true) or output mode (false)
     */
    PinProperty(T initValue, unsigned int pin, bool digital, bool input) : Property<T>(initValue)
    {
        this->construct(pin, digital, input);
    };

    /**
     * Common method for constructor
     *
     * @param pin Pin address
     * @param digital Flag to indicate if pin is digital (true) or analog (false)
     * @param input Flag to indicate if pin is in input mode (true) or output mode (false)
     */
    void construct(unsigned int pin, bool digital, bool input)
    {
        this->setPin(pin);
        this->setDigital(digital);
        this->setInput(input);
    }

    /**
     * Set value
     *
     * @param T value Value to store
     */
    virtual T set(T value)
    {
        // Parent
        Property<T>::set(value);

        if (this->isDigital() && !this->isInput()) {
            digitalWrite(this->getPin(), this->value);
        }

        return this->value;
    }

    /**
     * Read current pin value
     */
    virtual T read()
    {
        T v;

        if (this->isDigital()) {
            v = digitalRead(this->getPin());
        } else {
            v = analogRead(this->getPin());
        }

        // Save value
        this->set(v);

        return v;
    }

    /**
     * Flag to indicate if pin is analog or digital
     */
    virtual bool isDigital()
    {
        return this->digital;
    }

    /**
     * Define pin as digital (true) or analog (false)
     */
    virtual void setDigital(bool digital)
    {
        this->digital = digital;
    }

    /**
     * Get pin address to read
     */
    virtual unsigned int getPin()
    {
        return this->pin;
    }

    /**
     * Set pin address to read
     */
    virtual void setPin(unsigned int pin)
    {
        this->pin = pin;
    }

    /**
     * Flag to indicate if pin is in input mode (true) or output mode (false)
     * Note that for analog pin, output is mandatory
     */
    virtual bool isInput()
    {
        return this->input;
    }

    /**
     * Set pin mode as input (true) or output (false)
     * Note that for analog pin, output is mandatory
     */
    virtual void setInput(bool input)
    {
        this->input = input;

        if (this->isDigital()) {
            if (this->input) {
                pinMode(this->getPin(), INPUT);
            } else {
                T v = this->get();
                pinMode(this->getPin(), OUTPUT);
                // Reassign current value to output
                this->set(v);
            }
        }
    }
};

#endif //COM_OSTERES_ARDUINOPROPERTY_PINPROPERTY_H
