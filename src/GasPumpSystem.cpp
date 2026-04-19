#include <Arduino.h>
#include "GasPumpSystem.h"

void GasPumpSystem::init() {
    state = IDLE;
}

void GasPumpSystem::update() {
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