#pragma once
#include <Arduino.h>

// Controls MOSFET-based pump operation
class PumpDriver {
public:
    // Initializes pump control hardware
    void init(uint8_t pin);

    // Enables pump output
    void start();

    // Disables pump output
    void stop();

    // Returns current pump operating state
    bool isRunning();

private:
    // MOSFET control output pin
    uint8_t controlPin;

    // Current pump operating state
    bool running = false;
};