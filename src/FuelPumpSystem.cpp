#include <Arduino.h>
#include "FuelPumpSystem.h"

void FuelPumpSystem::init() {
    state = READY;
    prevState = READY;

    input.init();

    fuelAmount = 0;
    fuelRate = 0.05;
    pricePerGallon = 4.35;
    totalCost = 0;
    lastUpdateTime = millis();
}

void FuelPumpSystem::update() {
    input.update();
    handleStateEntry();

    switch(state) {
        case READY:
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
                totalCost = fuelAmount * pricePerGallon;

                Serial.print("Fuel dispensed: ");
                Serial.print(fuelAmount);
                Serial.println(" gallons");
                Serial.print("Total Cost: $");
                Serial.println(totalCost);
            }

            if(input.stopPressed()) {
                state = COMPLETE;
            }
            break;
        }
        
        case COMPLETE:
            state = READY;
            break;
    }
}

void FuelPumpSystem::handleStateEntry() {
    if(state != prevState) {
        switch(state) {
            case READY:
                Serial.println("STATE: READY");
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