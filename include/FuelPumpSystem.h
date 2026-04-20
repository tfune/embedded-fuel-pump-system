#pragma once
#include "InputHandler.h"

enum State {
    IDLE,
    FUEL_SELECTION,
    PUMPING,
    COMPLETE
};

class FuelPumpSystem {
public:
    void init();
    void update();

private:
    State state;
    State prevState;
    InputHandler input = InputHandler(2, 3, 4);

    unsigned long lastUpdateTime;
    float fuelAmount;
    float fuelRate;
    void handleStateEntry();
};