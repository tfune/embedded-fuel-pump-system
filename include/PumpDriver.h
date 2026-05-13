#pragma once
#include <Arduino.h>

class PumpDriver {
public:
    void init(uint8_t pin); // configures hardware
    void start(); // turns pump on
    void stop(); // turns pump off (safely)

    bool isRunning(); // queries pump state

private:
    uint8_t controlPin;
    bool running = false;
};