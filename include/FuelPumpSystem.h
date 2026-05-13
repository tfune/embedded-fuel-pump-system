#pragma once
#include "InputHandler.h"
#include "Display.h"
#include "FlowSensor.h"
#include "PumpDriver.h"

// fuel pump system states
enum State {
    READY,
    FUEL_SELECTION,
    PUMPING,
    COMPLETE
};

// main application state machine
class FuelPumpSystem {
public:
    // initialize system hardware and variables
    void init();

    // execute one cycle of the system state machine
    void update();

private:
    // state machine tracking tracking
    State state;
    State prevState;

    // handle one-time state entry actions
    void handleStateEntry();

    // system modules
    InputHandler input; // handles all keypad input
    Display display;    // handles OLED output
    FlowSensor flowSensor; // handles flow sensor
    PumpDriver pump; // controls diaphragm pump

    // timing
    unsigned long lastUpdateTime;

    // fuel transaction data
    float fuelAmount = 0.0f;
    float regPrice = 0.0f;
    float premPrice = 0.0f;
    float dieselPrice = 0.0f;
    float selectedPrice = 0.0f;
    float totalCost = 0.0f;

    // true if transaction exited before completion
    bool wasCancelled;

    // MOSFET gate control pin
    const int pumpControlPin = 47;

    // interrupt-capable flow sensor pin
    const int flowSensorPin = 2;
};