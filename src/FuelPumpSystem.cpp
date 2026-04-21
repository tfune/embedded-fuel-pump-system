#include <Arduino.h>
#include "FuelPumpSystem.h"

void FuelPumpSystem::init() {
    // initialize states
    state = READY;
    prevState = COMPLETE; // force initial state entry (triggers state print)

    input.init(); // initialize input handler

    // initialize simulation + pricing
    fuelAmount = 0;
    fuelRate = 0.05;
    pricePerGallon = 4.35;
    totalCost = 0;
    lastUpdateTime = millis();
}

void FuelPumpSystem::update() {
    input.update(); // poll user input
    handleStateEntry(); // handle one-time state transitions

    switch(state) {
        case READY:
            // wait for user to start transaction
            if(input.startPressed()) {
                state = FUEL_SELECTION;
            }
            break;
        
        case FUEL_SELECTION:
            // wait for fuel selection input
            if(input.fuelPressed()) {
                state = PUMPING;
            }
            break;
        
        case PUMPING: {
            unsigned long now = millis();

            // periodically update fuel dispensed and cost
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

            // stop pumping on user input
            if(input.stopPressed()) {
                state = COMPLETE;
            }
            break;
        }
        
        case COMPLETE:
            // reset system for next transaction
            state = READY;
            break;
    }
}

void FuelPumpSystem::handleStateEntry() {
    // execute once when entering a new state
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
                fuelAmount = 0; // reset fuel for new session
                break;

            case COMPLETE:
                Serial.println("STATE: COMPLETE");
                break;
        }

        prevState = state; // update state tracker
    }
}