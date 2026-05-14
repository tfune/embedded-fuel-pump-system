#pragma once

#include "InputHandler.h"
#include "Display.h"
#include "FlowSensor.h"
#include "PumpDriver.h"

// Fuel pump system operating states
enum State {
    READY,
    FUEL_SELECTION,
    PUMPING,
    COMPLETE,
    ERROR
};

// System fault classifications
enum ErrorType {
    NO_ERROR,
    TIMEOUT_ERROR,
    FLOW_ERROR
};

// Main application controller and state machine
class FuelPumpSystem {
public:
    // Initializes system hardware, drivers, and transaction state
    void init();

    // Executes one cycle of the system state machine
    void update();

private:
    // Handles one-time actions when entering a new state
    void handleStateEntry();

    // State machine tracking
    State state;
    State prevState;

    // Hardware interface modules
    InputHandler input;
    Display display;
    FlowSensor flowSensor;
    PumpDriver pump;

    // Display update timing
    unsigned long lastUpdateTime;

    // Pump runtime timeout protection
    unsigned long pumpStartTime = 0;
    const unsigned long MAX_PUMP_TIME = 30000;

    // Flow fault detection timing
    unsigned long lastFlowCheckTime = 0;
    unsigned long previousPulseCount = 0;
    const unsigned long FLOW_CHECK_INTERVAL = 1000;

    // Fuel transaction data
    float fuelAmount = 0.0f;
    float regPrice = 0.0f;
    float premPrice = 0.0f;
    float dieselPrice = 0.0f;
    float selectedPrice = 0.0f;
    float totalCost = 0.0f;

    // Transaction status
    bool wasCancelled;

    // Current system fault
    ErrorType currentError = NO_ERROR;

    // Hardware pin assignments
    const int pumpControlPin = 47;
    const int flowSensorPin = 2;
};