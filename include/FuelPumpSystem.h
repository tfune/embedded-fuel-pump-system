#pragma once
#include "InputHandler.h"

// system states
enum State {
    READY,
    FUEL_SELECTION,
    PUMPING,
    COMPLETE
};

class FuelPumpSystem {
public:
    void init(); // initialize system state
    void update(); // run state machine

private:
    // state tracking
    State state;
    State prevState;

    // handles all user input
    InputHandler input;

    // timing + fuel simulation
    unsigned long lastUpdateTime;
    float fuelAmount;
    float fuelRate;

    // pricing
    float pricePerGallon;
    float totalCost;

    // runs once on state change
    void handleStateEntry();
};