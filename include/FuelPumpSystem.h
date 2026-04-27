#pragma once
#include "InputHandler.h"
#include "Display.h"

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

    // modules
    InputHandler input; // handles all keypad input
    Display display;    // handles OLED output

    // timing
    unsigned long lastUpdateTime;

    // fuel + pricing
    float fuelAmount;
    float fuelRate;

    float regPrice;
    float premPrice;
    float dieselPrice;
    float selectedPrice;
    float totalCost;

    // runs once on state change
    void handleStateEntry();

    // flag for cancelled transaction
    bool wasCancelled;
};