//
// Created by Thibault PLET on 17/01/2020.
//

#ifndef COM_OSTERES_OSTIMER_H
#define COM_OSTERES_OSTIMER_H

class OsTimer {
public:
    /**
     * Constructor
     *
     */
    OsTimer()
    {
        this->reset();
    }

    /**
     * Destructor
     */
    ~OsTimer()
    {
        // Nothing
    }
    
    /**
     * Start
     */
    void start()
    {
        this->reset();
        this->startTime = millis();
        this->started = true;
    }

    /**
     * Stop
     */
    void stop()
    {
        this->stopTime = millis();
        this->started = false;
        this->completed = true;
    }

    /**
     * Get diff
     */
    unsigned long getDuration()
    {
        return this->stopTime - this->startTime;
    }

    /**
     * Get current duration since start
     */
    unsigned long getCurrentDuration()
    {
        return this->started ? millis() - this->startTime : 0;
    }

    /**
     * Flag to indicate if timer is started
     */
    bool isStarted()
    {
        return this->started;
    }

    /**
     * Flag to indicate if timer is completed
     */
    bool isCompleted()
    {
        return this->completed;
    }

        /**
     * Reset
     */
    void reset()
    {
        this->startTime = 0;
        this->stopTime = 0;
        this->started = false;
        this->completed = false;
    }

protected:
    /**
     * Start
     */
    unsigned long startTime;

    /**
     * Stop
     */
    unsigned long stopTime;

    /**
     * Flag for started timer
     */
    bool started;

    /**
     * Flag for completed timer
     */
    bool completed;
};

#endif //COM_OSTERES_OSTIMER_H
