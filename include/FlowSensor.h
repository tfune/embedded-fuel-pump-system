#pragma once
#include <Arduino.h>

class FlowSensor {
public: 
    void init(uint8_t pin);
    float getFuelAmount();
    void reset();

private:
    static volatile unsigned long pulseCount;
    uint8_t sensorPin;
    float calibrationFactor = 6.0f;
    static void pulseISR();
};