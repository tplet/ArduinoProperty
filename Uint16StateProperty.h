//
// Created by Thibault PLET on 14/10/2021.
//

#ifndef COM_OSTERES_ARDUINOPROPERTY_UINT16STATEPROPERTY_H
#define COM_OSTERES_ARDUINOPROPERTY_UINT16STATEPROPERTY_H

#include <StateProperty.h>

class Uint16StateProperty : public StateProperty<uint16_t> {
public:
    /**
     * Constructor
     * 
     * @param uint8_t address Address to stored data in EEProm. Be sure that this address not already used!
     */
    Uint16StateProperty(uint8_t address) : StateProperty<uint16_t>(address)
    {
        
    }

    /**
     * Constructor
     * Be careful, when init value specified, can erase current stored value
     *
     * @param uint8_t address Address to stored data in EEProm. Be sure that this address not already used!
     */
    Uint16StateProperty(uint8_t address, uint16_t initValue) : StateProperty<uint16_t>(address, initValue)
    {
        
    };
    
    /**
     * Set value
     *
     * @param uint16_t value Value to store
     */
    uint16_t set(uint16_t value) {
        // Parent
        Property<uint16_t>::set(value);

        if (this->isChanged()) {

            saveState(this->getAddress(), highByte(this->value));
            saveState(this->getAddress()+1, lowByte(this->value));
            this->forceReading = false;
        }

        return this->value;
    }

    /**
     * Get value
     */
    uint16_t get() {
        if (this->isForceReading()) {
            this->value = word(loadState(this->getAddress()), loadState(this->getAddress()+1));
            this->forceReading = false;
        }

        return Property<uint16_t>::get();
    }
};

#endif //COM_OSTERES_ARDUINOPROPERTY_UINT16STATEPROPERTY_H
