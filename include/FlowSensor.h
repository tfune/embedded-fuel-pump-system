#pragma once
#include <Arduino.h>

class FlowSensor {
public: 
    void init(uint8_t pin);
    float getFuelAmount();
    unsigned long getPulseCount();
    void reset();

private:
    static volatile unsigned long pulseCount;
    uint8_t sensorPin;
    float calibrationFactor = 7.125f;
    static void pulseISR();
};