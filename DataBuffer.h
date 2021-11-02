//
// Created by Thibault PLET on 31/05/2016.
//

#ifndef COM_OSTERES_ARDUINOPROPERTY_DATABUFFER_H
#define COM_OSTERES_ARDUINOPROPERTY_DATABUFFER_H

class DataBuffer {
public:
    /**
     * Constructor
     *
     * @param bufferDelay       Delay for buffer validity, in milliseconds
     * @param firstDelay        Delay for first outdate, in milliseconds. Immediate by default.
     * @param startImmediately  Start buffer immediately
     */
    DataBuffer(unsigned long bufferDelay = 10000, unsigned long firstDelay = 0, bool startImmediately = true)
    {
        // Init
        this->bufferDelay = bufferDelay; // ms
        this->millisIncrement = 0;
        this->bufferTimePoint = millis() - bufferDelay + firstDelay;
        this->started = startImmediately;
    }

    /**
     * Destructor
     */
    ~DataBuffer()
    {
        // Nothing
    }
    
    /**
     * Start buffer
     */
    void startBuffer()
    {
        this->reset();
        this->started = true;
    }

    /**
     * Started flag
     */
    bool isStarted()
    {
        return this->started;
    }

    /**
     * Stop buffer
     */
    void stopBuffer()
    {
        this->started = false;
    }

    /**
     * Reset buffer
     */
    virtual void reset()
    {
        this->resetBufferTimePoint();
    }

    /**
     * Flag to indicate if buffer is considering as outdated
     */
    bool isOutdated()
    {
        return this->isStarted() && this->getRemain() == 0;
    }

    /**
     * Get time remain before outdate (in ms). Remain countdown stop to 0.
     */
    unsigned long getRemain()
    {
        long v = this->getBufferDelay() - (millis() + this->millisIncrement - this->bufferTimePoint);
        return v < 0 ? 0 : v;
    }

    /**
     * Move forward to the future
     */
    void moveForward(unsigned long increment)
    {
        this->millisIncrement += increment;
    }

    /**
     * Set buffer as outdated imediately
     */
    void setOutdated()
    {
        this->startBuffer();
        this->bufferTimePoint = millis() - this->getBufferDelay();
        this->millisIncrement = 0;
    }

    /**
     * Get limit delay at which buffer is considering as outdated (in milliseconds)
     */
    unsigned long getBufferDelay()
    {
        return this->bufferDelay;
    }

    /**
     * Set limit delay at which buffer is considered as outdated (in milliseconds)
     */
    void setBufferDelay(unsigned long value)
    {
        this->bufferDelay = value;
    }
protected:
    /**
     * Reset buffer time point
     */
    void resetBufferTimePoint()
    {
        this->bufferTimePoint = millis();
        this->millisIncrement = 0;
    }

    /**
     * Limit interval before buffer is considering as outdated (in milliseconds)
     */
    unsigned long bufferDelay;

    /**
     * Time point for buffer
     */
    unsigned long bufferTimePoint;

    /**
     * Millis increment to artificialy go to the future, or used to catch up sleep mode
     */
    unsigned long millisIncrement = 0;

    /**
     * Start flag
     */
    bool started;
};

#endif //COM_OSTERES_ARDUINOPROPERTY_DATABUFFER_H
