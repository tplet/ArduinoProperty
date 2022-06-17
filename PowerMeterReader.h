//
// Created by Thibault PLET on 02/04/2020.
//

#ifndef COM_OSTERES_AUTOMATION_ARDUINO_COMPONENT_POWERMETERREADER_H
#define COM_OSTERES_AUTOMATION_ARDUINO_COMPONENT_POWERMETERREADER_H

class PowerMeterReader {
public:
    /**
     * Constructor
     *
     * @param pinCLK         Pin connected to CLK
     * @param pinMISO        Pin connected to MISO
     */
    PowerMeterReader(unsigned int pinCLK, unsigned int pinMISO)
    {
        // Init
        this->pinCLK = pinCLK;
        this->pinMISO = pinMISO;

        // Set the CLK-pin (D5) to input
        pinMode(this->pinCLK, INPUT);
        //Set the MISO-pin (D5) to input
        pinMode(this->pinMISO, INPUT);
    }

    /**
     * Destructor
     */
    ~PowerMeterReader()
    {
        // Nothing
    }

    /**
     * Get tension
     */
    unsigned int getTension()
    {
        return this->tension;
    }

    /**
     * Get power
     */
    unsigned long getPower()
    {
        return this->power;
    }

    /**
     * Get current
     */
    float getCurrent()
    {
        return this->current;
    }

    /**
     * Get CLK pin
     */
    unsigned int getPinCLK()
    {
        return this->pinCLK;
    }

    /**
     * Get MISO pin
     */
    unsigned int getPinMISO()
    {
          return this->pinMISO;
    }

    /**
     * Read process
     * 
     * @return bool True if value has been read, false if need to wait next call
     */
    bool read()
    {
        // If currently reading, wait for finish
        if (!this->reading) {
            return false;
        }

        bool readReturn = false;
        float U = 0;    //voltage
        float P = 0;    //power        

        this->countBits = 0;  //CLK-interrupt increments CountBits when new bit is received
        while (this->countBits <40){}  //skip the uninteresting 5 first bytes
        
        this->countBits = 0;
        this->ba = 0;
        this->bb = 0;
        
        while (this->countBits<24) {  //Loop through the next 3 Bytes (6-8) and save byte 6 and 7 in Ba and Bb
            if (this->nextBit == true) { //when rising edge on CLK is detected, NextBit = true in in interrupt. 
                if (this->countBits < 9) {  //first Byte/8 bits in Ba
                    this->ba = (this->ba << 1);  //Shift Ba one bit to left and store MISO-value (0 or 1) (see http://arduino.cc/en/Reference/Bitshift)
                    //read MISO-pin, if high: make Ba[0] = 1
                    if (digitalRead(this->pinMISO) == HIGH) {
                        this->ba |= (1<<0);  //changes first bit of Ba to "1"
                    }   //doesn't need "else" because BaBb[0] is zero if not changed.
                    this->nextBit = false; //reset NextBit in wait for next CLK-interrupt
                }
                else if (this->countBits < 17) {  //bit 9-16 is byte 7, stor in Bb
                    this->bb = this->bb << 1;  //Shift Ba one bit to left and store MISO-value (0 or 1)
                    //read MISO-pin, if high: make Ba[0] = 1
                    if (digitalRead(this->pinMISO) == HIGH) {
                        this->bb |= (1<<0);  //changes first bit of Bb to "1"
                    }
                    this->nextBit = false;  //reset NextBit in wait for next CLK-interrupt
                }
            }
        }
        
        if (this->bb != 3) { //if bit Bb is not 3, we have reached the important part, U is allready in Ba and Bb and next 8 Bytes will give us the Power. 
            this->antal += 1;  //increment for mean value calculations
          
            //Voltage = 2*(Ba+Bb/255)
            U = 2.0*( (float)this->ba + (float)this->bb / 255.0 ); 
          
            /*
             * Power part
             */
            this->countBits = 0;
            while (this->countBits < 40) {}//Start reading the next 8 Bytes by skipping the first 5 uninteresting ones
          
            this->countBits = 0;
            this->ba = 0;
            this->bb = 0;
            this->bc = 0;
            
            while (this->countBits < 24) {  //store byte 6, 7 and 8 in Ba and Bb & Bc. 
                if (this->nextBit == true) {
                    if (this->countBits < 9) {
                        this->ba = (this->ba << 1);  //Shift Ba one bit to left and store MISO-value (0 or 1)
                        //read MISO-pin, if high: make Ba[0] = 1
                        if (digitalRead(this->pinMISO) == HIGH) {
                            this->ba |= (1<<0);  //changes first bit of Ba to "1"
                        } 
                        this->nextBit = false;
                    }
                    else if (this->countBits < 17) {
                        this->bb = this->bb << 1;  //Shift Ba one bit to left and store MISO-value (0 or 1)
                        //read MISO-pin, if high: make Ba[0] = 1
                        if (digitalRead(this->pinMISO) == HIGH) {
                            this->bb |= (1<<0);  //changes first bit of Bb to "1"
                        }
                        this->nextBit = false;
                    }
                    else {
                        this->bc = this->bc << 1;  //Shift Bc one bit to left and store MISO-value (0 or 1)
                        //read MISO-pin, if high: make Bc[0] = 1
                        if (digitalRead(this->pinMISO) == HIGH) {
                            this->bc |= (1<<0);  //changes first bit of Bc to "1"
                        }
                        this->nextBit = false;
                    }
                }
            }
          
            //Power = (Ba*255+Bb)/2
            this->ba = 255 - this->ba;
            this->bb = 255 - this->bb;
            this->bc = 255 - this->bc; 
            P = ( (float)this->ba * 255 + (float)this->bb + (float)this->bc / 255.0 ) / 2;
          
            // Voltage mean
            this->readData[0] = (U + this->readData[0] * ( (float)this->antal - 1 ) ) / (float)this->antal;
            // Current mean
            this->readData[1] = ( P / U + this->readData[1] * ( (float)this->antal - 1 ) ) / (float)this->antal;
            // Power mean
            this->readData[2] = ( P + this->readData[2] * ( (float)this->antal - 1 ) ) / (float)this->antal;
      
            //Serial.print("U: ");
            //Serial.println(U,1);
            if (U > 250){
              U = this->oldTension;
            }
            if (P > 4000){
              P = 0;
            }

            // Update main properties
            this->power = P;
            this->tension = U;
            this->current = U == 0 ? 0 : P / U;
            
            //if (this->antal == 10) { //every 10th 70-package = every ~10s
                //transmit ReadData-array to nRF or Wifi-module here:
                //transmission function here...
                // In class case, transmit values when method return true

                // Reset readData array
                this->readData[0] = 0;
                this->readData[1] = 0;
                this->readData[2] = 0;
        
                // Reset mean-value counter
                this->antal = 0;
            //}
            
            this->reading = false;  //reset sync variable to make sure next reading is in sync. 
            
            readReturn = true;
        }
        
        if (this->bb == 0) {  //If Bb is not 3 or something else than 0, something is wrong! 
            this->reading = false;
        }

        return readReturn;
    }

    /**
     * Function that triggers whenever CLK-pin is rising (goes high)
     */
    void riseCLK_ISR()
    {
        //if we are trying to find the sync-time (CLK goes high for 1-2ms)
        if (this->reading == false) {
            this->clkHighCount = 0;
            //Register how long the ClkHigh is high to evaluate if we are at the part wher clk goes high for 1-2 ms
            while (digitalRead(this->pinCLK) == HIGH) {
                this->clkHighCount += 1;
                delayMicroseconds(30);  //can only use delayMicroseconds in an interrupt. 
            }
            // if the Clk was high between 1 and 2 ms than, its a start of a SPI-transmission
            if (this->clkHighCount >= 33 && this->clkHighCount <= 67) {
                this->reading = true;
            }
        }
        else { //we are in sync and logging CLK-highs
            //increment an integer to keep track of how many bits we have read. 
            this->countBits += 1; 
            this->nextBit = true;
        }
    }

protected:

    /*
     * All variables that is changed in the interrupt function must be volatile to make sure changes are saved. 
     */

     /**
      * Store MISO-byte 1
      */
    volatile int ba = 0;

    /**
     * Store MISO-byte 2
     */
    volatile int bb = 0;

    /**
     * Store MISO-byte 3
     */
    volatile int bc = 0;

    /**
     * Count read bits
     */
    volatile long countBits = 0;
  
    /**
     * Number of read values (to calculate mean)
     */
    volatile int antal = 0;
  
    /**
     * Number of CLK-highs (find start of a Byte)
     */
    volatile long clkHighCount = 0;
  
    /**
     * As long as we ar in SPI-sync
     */
    volatile boolean inSync = false;
  
    /**
     * A new bit is detected
     */
    volatile boolean nextBit = true;
  
      
    /**
     * Reading flag to prevent one read at time
     */
    bool reading = false;

    /**
     * CLK pin
     */
    unsigned int pinCLK;

    /**
     * MISO pin
     */
    unsigned int pinMISO;

    /**
     * Array to hold mean values of [U,I,P]
     */
    float readData[3] = {0, 0, 0};

    /**
     * Previous registered voltage
     */
    unsigned int oldTension;
    
    /**
     * Tension read
     */
    volatile unsigned int tension = 0;

    /**
     * Power read
     */
    volatile unsigned long power = 0;

    /**
     * Current read
     */
    volatile float current = 0;

};

#endif //COM_OSTERES_AUTOMATION_ARDUINO_COMPONENT_POWERMETERREADER_H
