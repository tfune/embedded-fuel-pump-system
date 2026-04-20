#include <Arduino.h>
#include "FuelPumpSystem.h"

void FuelPumpSystem::init() {
    state = IDLE;
}

void FuelPumpSystem::update() {
    switch(state) {
        case IDLE:
            // waiting for user input
            break;
        
        case FUEL_SELECTION:
            // user selects fuel type
            break;
        
        case PUMPING:
            // simulate fuel flow
            break;
        
        case COMPLETE:
            // show final receipt
            break;
    }
}