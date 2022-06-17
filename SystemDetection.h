//
// Created by Thibault PLET on 02/04/2020.
//

#ifndef COM_OSTERES_AUTOMATION_ARDUINO_COMPONENT_SYSTEMDETECTION_H
#define COM_OSTERES_AUTOMATION_ARDUINO_COMPONENT_SYSTEMDETECTION_H

#include <DataBuffer.h>

class SystemDetection {
public:
    /**
     * Constructor
     *
     * @param delayOn         Delay before considering system on
     * @param delayOff        Delay before considering sytem off
     * @param delayOffConfirm Delay before considering system off confirmation (after system off detection)
     * @param powerStepOn     Power step (watt) to consider system on
     * @param powerStepOff    Power step (watt) to consider system off
     */
    SystemDetection(
      unsigned long delayOn = 1000, 
      unsigned long delayOff = 1000, 
      unsigned long delayOffConfirm = 1000,
      unsigned int powerStepOn = 10,
      unsigned int powerStepOff = 10
    ) {
        // Init
        this->watchDogOn = new DataBuffer(delayOn, 0, false);
        this->watchDogOff = new DataBuffer(delayOff, 0, false);
        this->watchDogOffConfirm = new DataBuffer(delayOffConfirm, 0, false);
        this->powerStepOn = powerStepOn;
        this->powerStepOff = powerStepOff;
    }

    /**
     * Destructor
     */
    ~SystemDetection()
    {
        delete this->watchDogOn;
        delete this->watchDogOff;
        delete this->watchDogOffConfirm;
    }

    /**
     * Flag for system on
     */
    bool isOn()
    {
        return this->on;
    }

    /**
     * Flag for system off
     */
    bool isOff()
    {
        return !this->on;
    }

    /**
     * Detect system
     * 
     * @return bool True if system detection changed! (on or off, use isOn or isOff to know)
     */
    bool detect(unsigned long power)
    {
        bool changed = false;
        
        // Outside de system cycle
        if (this->isOff()) {
            // Detect ON
            if (power > this->powerStepOn) {
                // Start detection
                if (!this->watchDogOn->isStarted()) {
                    this->watchDogOn->startBuffer();
                }
                // Detection end, if watchDog outdated
                else if (this->watchDogOn->isOutdated()) {
                    this->watchDogOn->stopBuffer();
                    // System detected!
                    this->on = true;
                    changed = true;
                }
            } 
            // Stop detection
            else if (this->watchDogOn->isStarted()) {
                this->watchDogOn->stopBuffer();
            }
        }
        // Inside de system cycle
        else {
            // Outside off confirm period
            if (!this->watchDogOffConfirm->isStarted()) {
                // Detect OFF
                if (power < this->powerStepOff) {
                    // Start detection
                    if (!this->watchDogOff->isStarted()) {
                        this->watchDogOff->startBuffer();
                    }
                    // Detection end, if watchDog outdated
                    else if (this->watchDogOff->isOutdated()) {
                        this->watchDogOff->stopBuffer();
                        // End system! Waiting for some time now!
                        this->watchDogOffConfirm->startBuffer();
                    }
                } 
                // Stop detection
                else if (this->watchDogOff->isStarted()) {
                    this->watchDogOff->stopBuffer();
                }
            }
            // If watch dog off confirm outdated
            else if (this->watchDogOffConfirm->isStarted() && this->watchDogOffConfirm->isOutdated()) {
                this->watchDogOffConfirm->stopBuffer();
                // End system!
                this->on = false;
                changed = true;
            }
        }

        return changed;
    }
    
    
protected:
    
    /**
     * Limit interval before system considering as on
     */
    DataBuffer * watchDogOn;

    /**
     * Limit interval before system considering as off
     */
    DataBuffer * watchDogOff;

    /**
     * Limit interval before system off confirmed (after off detection)
     */
    DataBuffer * watchDogOffConfirm;

    /**
     * Power step (watt) to consider system on
     */
    unsigned int powerStepOn;

    /**
     * Power step (watt) to consider system off
     */
    unsigned int powerStepOff;

    /**
     * Flag to indicate if system is on
     */
    bool on = false;
};

#endif //COM_OSTERES_AUTOMATION_ARDUINO_COMPONENT_SYSTEMDETECTION_H
