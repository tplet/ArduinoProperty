//
// Created by Thibault PLET on 17/01/2020.
//

#ifndef COM_OSTERES_AUTOMATION_ARDUINO_COMPONENT_TOUCHBUTTON_H
#define COM_OSTERES_AUTOMATION_ARDUINO_COMPONENT_TOUCHBUTTON_H

#include <OsTimer.h>

class TouchButton {
public:
    //constants declarations
    static const unsigned int STATUS_NONE = 0;
    static const unsigned int STATUS_PRESS = 1;
    static const unsigned int STATUS_SHORT_CLICK = 2;
    static const unsigned int STATUS_LONG_CLICK = 3;
    static const unsigned int STATUS_LONG_PRESS = 4;

    /**
     * Constructor
     *
     * @param pin                 Pin button (digital input)
     * @param shortPressDelay     Delay for short click, in milliseconds
     * @param longPressDelay      Delay for long click, in milliseconds.
     */
    TouchButton(byte pin, unsigned long shortPressDelay = 250, unsigned long longPressDelay = 500)
    {
        // Init
        this->pin = pin;
        this->shortPressDelay = shortPressDelay;
        this->longPressDelay = longPressDelay;
        this->timer = new OsTimer();
        this->status = TouchButton::STATUS_NONE;
        this->stateChanged = false;
        this->clicked = false;
    }

    /**
     * Destructor
     */
    ~TouchButton()
    {
        delete this->timer;
    }

    /**
     * Flag to indicate if button is currently pressed
     */
    bool isPressed()
    {
        unsigned int pressed = digitalRead(pin);

        return pressed == 1;
    }

    /**
     * Flag to indicate if state changed on last process
     */
    bool isStateChanged()
    {
        return this->stateChanged;
    }

    /**
     * Flag to indicate if touch out
     */
    bool hasClicked()
    {
        return this->clicked;
    }

    /**
     * Get status
     */
    unsigned int getStatus()
    {
        return this->status;
    }

    /**
     * Consume status
     */
    void consume()
    {
        this->status = TouchButton::STATUS_NONE;
        this->timer->reset();
        this->stateChanged = false;
    }
    
    /**
     * Process touch button
     */
    void process()
    {
        // Complete timer
        processTimer();

        // Check timer (press and unpress)
        bool clicked = false;
        unsigned long diff;
        unsigned int localStatus;
        if (this->timer->isCompleted()) {
            // Check timer duration
            diff = this->timer->getDuration();

            // Short
            if (diff >= this->shortPressDelay && diff < this->longPressDelay) {
                clicked = true;
                localStatus = TouchButton::STATUS_SHORT_CLICK;
            }
            // Long
            if (diff >= this->longPressDelay) {
                clicked = true;
                localStatus = TouchButton::STATUS_LONG_CLICK;
            }
          
            this->timer->reset();
        }

        if (this->timer->isStarted()) {
            // Check duration since start
            diff = this->timer->getCurrentDuration();
            if (diff >= this->longPressDelay) {
                localStatus = TouchButton::STATUS_LONG_PRESS;
            } else {
                localStatus = TouchButton::STATUS_PRESS;
            }
        }
        else if (!clicked) {
            localStatus = TouchButton::STATUS_NONE;
        }
        this->clicked = clicked;

        // Status changed ?
        this->stateChanged = localStatus != this->status;
        this->status = localStatus;
    }

    
protected:
    /**
     * Process timer
     */
    void processTimer()
    {
        // If pressed
        if (this->isPressed() && !this->timer->isStarted()) {
            this->timer->start();
        }
        // Else, if timer started
        else if (!this->isPressed() && this->timer->isStarted()) {
            this->timer->stop();
        }
    }

    unsigned int status;
    bool stateChanged;
    bool clicked;
    unsigned long shortPressDelay;
    unsigned long longPressDelay;
    byte pin;
    OsTimer * timer;
};

#endif //COM_OSTERES_AUTOMATION_ARDUINO_COMPONENT_TOUCHBUTTON_H
