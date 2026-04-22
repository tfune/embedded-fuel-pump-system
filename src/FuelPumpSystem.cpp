#include <Arduino.h>
#include "FuelPumpSystem.h"

void FuelPumpSystem::init() {
    // initialize states
    state = READY;
    prevState = COMPLETE; // force initial state entry (triggers state print)

    input.init(); // initialize input handler
    display.init(); // initialize OLED display

    // initialize simulation + pricing
    fuelAmount = 0;
    fuelRate = 0.05;
    regPrice = 4.35;
    premPrice = 4.95;
    dieselPrice = 6.45;
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
            if(input.fuel1Pressed()) {
                selectedPrice = regPrice;
                state = PUMPING;
            }

            else if(input.fuel2Pressed()) {
                selectedPrice = premPrice;
                state = PUMPING;
            }

            else if(input.fuel3Pressed()) {
                selectedPrice = dieselPrice;
                state = PUMPING;
            }
            break;
        
        case PUMPING: {
            unsigned long now = millis();

            // periodically update fuel dispensed and cost
            if(now - lastUpdateTime >= 500) {
                lastUpdateTime = now;

                fuelAmount += fuelRate;
                totalCost = fuelAmount * selectedPrice;

                // Update OLED with live data
                display.showFuel(fuelAmount, totalCost);
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
                display.showState("READY");
                break;
            
            case FUEL_SELECTION:
                display.showState("SELECT FUEL");
                break;

            case PUMPING: 
                display.showState("PUMPING");
                
                // reset values when starting pump
                fuelAmount = 0;
                totalCost = 0;
                break;

            case COMPLETE:
                display.showState("Complete");
                break;
        }

        prevState = state; // update state tracker
    }
}