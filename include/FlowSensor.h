#pragma once

#include <Arduino.h>

// Handles flow sesnor pulse counting and fuel volume calculation
class FlowSensor {
public: 
    // Initializes the flow sensor input and interrupt handler
    void init(uint8_t pin);

    // Returns the calculated fuel volume in ounces
    float getFuelAmount();

    // Returns the current pulse count snapshot
    unsigned long getPulseCount();

    // Resets the pulse counter for a new transaction
    void reset();

private:
    // Shared pulse counter updated by the ISR
    static volatile unsigned long pulseCount;

    // Flow sensor input pin
    uint8_t sensorPin;

    // Sensor calibration factor in pulses per ounce
    float calibrationFactor = 7.125f;

    // Interrupt service routine for pulse detection
    static void pulseISR();
};