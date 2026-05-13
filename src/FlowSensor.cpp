#include "FlowSensor.h"

// shared ISR pulse counter
volatile unsigned long FlowSensor::pulseCount = 0;

// interrupt service routine
void FlowSensor::pulseISR() {
    pulseCount++;
}

// initialize sensor and interrupt
void FlowSensor::init(uint8_t pin) {
    sensorPin = pin;

    pinMode(sensorPin, INPUT_PULLUP);

    attachInterrupt(
        digitalPinToInterrupt(sensorPin),
        pulseISR,
        RISING
    );
}

// safely calculate fuel amount
float FlowSensor::getFuelAmount() {
    unsigned long pulseSnapshot;

    noInterrupts();
    pulseSnapshot = pulseCount;
    interrupts();

    return pulseSnapshot / calibrationFactor;
}

// safely return current pulse count
unsigned long FlowSensor::getPulseCount() {
    unsigned long pulseSnapshot;

    noInterrupts();
    pulseSnapshot = pulseCount;
    interrupts();

    return pulseSnapshot;
}

// reset transaction data
void FlowSensor::reset() {
    noInterrupts();
    pulseCount = 0;
    interrupts();
}