#include <Arduino.h>
#include "FuelPumpSystem.h"

void FuelPumpSystem::init() {
    state = IDLE;
    prevState = IDLE;
    input.init();

    fuelAmount = 0;
    fuelRate = 0.05;
    lastUpdateTime = millis();
}

void FuelPumpSystem::update() {
    handleStateEntry();

    switch(state) {
        case IDLE:
            if(input.startPressed()) {
                state = FUEL_SELECTION;
            }
            break;
        
        case FUEL_SELECTION:
            if(input.fuelPressed()) {
                state = PUMPING;
            }
            break;
        
        case PUMPING: {
            unsigned long now = millis();

            // Update fuel dispensed every 500 ms
            if(now - lastUpdateTime >= 500) {
                lastUpdateTime = now;
                fuelAmount += fuelRate;

                Serial.print("Fuel dispensed: ");
                Serial.println(fuelAmount);
            }

            if(input.stopPressed()) {
                state = COMPLETE;
            }
            break;
        }
        
        case COMPLETE:
            state = IDLE;
            break;
    }
}

void FuelPumpSystem::handleStateEntry() {
    if(state != prevState) {
        switch(state) {
            case IDLE:
                Serial.println("STATE: IDLE");
                break;
            
            case FUEL_SELECTION:
                Serial.println("STATE: FUEL_Selection");
                break;

            case PUMPING: 
                Serial.println("STATE: PUMPING");
                fuelAmount = 0;
                break;

            case COMPLETE:
                Serial.println("STATE: COMPLETE");
                break;
        }

        prevState = state;
    }
}