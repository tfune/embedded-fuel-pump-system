#pragma once
#include "InputHandler.h"

enum State {
    READY,
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
    InputHandler input;

    unsigned long lastUpdateTime;
    float fuelAmount;
    float fuelRate;
    float pricePerGallon;
    float totalCost;
    void handleStateEntry();
};