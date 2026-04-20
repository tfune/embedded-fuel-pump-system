#include <Arduino.h>
#include "FuelPumpSystem.h"

void FuelPumpSystem::init() {
    state = IDLE;
    input.init();
}

void FuelPumpSystem::update() {
    switch(state) {
        case IDLE:
            // waiting for user input
            if(input.startPressed()) {
                state = FUEL_SELECTION;
                Serial.println("State -> FUEL_Selection");
            }
            break;
        
        case FUEL_SELECTION:
            // user selects fuel type
            if(input.fuelPressed()) {
                state = PUMPING;
                Serial.println("State -> PUMPING");
            }
            break;
        
        case PUMPING:
            // simulate fuel flow
            if(input.stopPressed()) {
                state = COMPLETE;
                Serial.println("State -> COMPLETE");
            }
            break;
        
        case COMPLETE:
            // show final receipt
            state = IDLE;
            Serial.println("State -> IDLE");
            break;
    }
}