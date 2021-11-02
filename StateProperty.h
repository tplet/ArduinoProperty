//
// Created by Thibault PLET on 07/10/2021.
//

#ifndef COM_OSTERES_ARDUINOPROPERTY_STATEPROPERTY_H
#define COM_OSTERES_ARDUINOPROPERTY_STATEPROPERTY_H

#include <Property.h>

template<typename T>
class StateProperty : public Property<T> {
protected:
    /**
     * Address to where contained data in EEProm
     */
    uint8_t address;

    /**
     * Flag to indicate if needed to force to read value from memory next time
     */
    bool forceReading;
public:
    /**
     * Constructor
     * 
     * @param uint8_t address Address to stored data in EEProm. Be sure that this address not already used!
     */
    StateProperty(uint8_t address) : Property<T>()
    {
        this->construct(address);
    }

    /**
     * Constructor
     * Be careful, when init value specified, can erase current stored value
     *
     * @param uint8_t address Address to stored data in EEProm. Be sure that this address not already used!
     */
    StateProperty(uint8_t address, T initValue) : Property<T>(initValue)
    {
        this->construct(address);
    };

    /**
     * Common method for constructor
     * 
     * @param uint8_t address Address to stored data in EEProm. Be sure that this address not already used!
     */
    void construct(uint8_t address)
    {
        this->forceReading = true;
        this->setAddress(address);
    }

    /**
     * Get address
     */
    uint8_t getAddress()
    {
        return this->address;
    }

    /**
     * Set address
     * Be sure for this operation and that this address not already used! Data will be lost!
     */
    void setAddress(uint8_t address)
    {
        this->address = address;
        // Next time we read value, force refresh from memory
        this->forceReading = true;
    }

    /**
     * Set value
     *
     * @param T value Value to store
     */
    T set(T value) {
        // Parent
        Property<T>::set(value);

        if (this->isChanged()) {
            saveState(this->getAddress(), this->value);
            this->forceReading = false;
        }

        return this->value;
    }

    /**
     * Get value
     */
    T get() {
        if (this->isForceReading()) {
            this->value = loadState(this->getAddress());
            this->forceReading = false;
        }

        return Property<T>::get();
    }

    /**
     * Flag to indicate if needed to force to read value from memory next time
     */
    bool isForceReading()
    {
        return this->forceReading;
    }

    /**
     * Force reading property from memory next time to read
     */
    void setForceReading(bool force)
    {
        this->forceReading = force;
    }
};

#endif //COM_OSTERES_ARDUINOPROPERTY_STATEPROPERTY_H
