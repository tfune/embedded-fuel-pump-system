#include "FlowSensor.h"

// Shared ISR pulse counter
volatile unsigned long FlowSensor::pulseCount = 0;

// Interrupt service routine for flow sensor pulses
void FlowSensor::pulseISR() {
    pulseCount++;
}

// Initialize flow sensor input and interrupt handling
void FlowSensor::init(uint8_t pin) {
    sensorPin = pin;

    pinMode(sensorPin, INPUT_PULLUP);

    attachInterrupt(
        digitalPinToInterrupt(sensorPin),
        pulseISR,
        RISING
    );
}

// Return calculated fuel volume in ounces
float FlowSensor::getFuelAmount() {
    unsigned long pulseSnapshot;

    // Atomically copy ISR-updated pulse count
    noInterrupts();
    pulseSnapshot = pulseCount;
    interrupts();

    return pulseSnapshot / calibrationFactor;
}

// Return current pulse count snapshot
unsigned long FlowSensor::getPulseCount() {
    unsigned long pulseSnapshot;

    // Atomically copy ISR-updated pulse count
    noInterrupts();
    pulseSnapshot = pulseCount;
    interrupts();

    return pulseSnapshot;
}

// Reset pulse count for next transaction
void FlowSensor::reset() {
    noInterrupts();
    pulseCount = 0;
    interrupts();
}