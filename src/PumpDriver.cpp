#include "PumpDriver.h"

// initialize pump control hardware
void PumpDriver::init(uint8_t pin) {
    controlPin = pin;
    pinMode(controlPin, OUTPUT);
    stop();
}

// enable pump
void PumpDriver::start() {
    digitalWrite(controlPin, HIGH);
    running = true;
}

// disable pump
void PumpDriver::stop() {
    digitalWrite(controlPin, LOW);
    running = false;
}

// return current pump state
bool PumpDriver::isRunning() {
    return running;
}