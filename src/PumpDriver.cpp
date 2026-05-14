#include "PumpDriver.h"

// Initialize pump control hardware
void PumpDriver::init(uint8_t pin) {
    controlPin = pin;
    pinMode(controlPin, OUTPUT);
    stop();
}

// Enable MOSFET output to power pump
void PumpDriver::start() {
    digitalWrite(controlPin, HIGH);
    running = true;
}

// Disable MOSFET output to stop pump
void PumpDriver::stop() {
    digitalWrite(controlPin, LOW);
    running = false;
}

// Return current pump operating state
bool PumpDriver::isRunning() {
    return running;
}