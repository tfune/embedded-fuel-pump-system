#include <Arduino.h>
#include "FuelPumpSystem.h"

void FuelPumpSystem::init() {
    // initialize states
    state = READY;
    prevState = COMPLETE; // force initial state entry handling

    // initialize system modules
    input.init();
    display.init();

    // initialize pump control output
    pinMode(pumpControlPin, OUTPUT);
    digitalWrite(pumpControlPin, LOW);

    // initialize flow sensor interrupt
    flowSensor.init(flowSensorPin);

    // initialize fuel pricing
    regPrice = 4.399f;
    premPrice = 4.999f;
    dieselPrice = 6.399f;

    // initialize transaction data
    fuelAmount = 0.0f;
    selectedPrice = 0.0f;
    totalCost = 0.0f;

    lastUpdateTime = millis();
}

// main system update loop
void FuelPumpSystem::update() {
    // poll user input
    input.update();

    // global exit handling
    if(input.exitPressed()) {
        wasCancelled = true;
        digitalWrite(pumpControlPin, LOW);
        state = COMPLETE;
    }

    // execute one-time state entry actions
    handleStateEntry();

    // main state machine
    switch(state) {
        // ready state
        case READY:
            digitalWrite(pumpControlPin, LOW);

            if(input.startPressed()) {
                state = FUEL_SELECTION;
            }
            break;
        
        // fuel selection state
        case FUEL_SELECTION:
            digitalWrite(pumpControlPin, LOW);

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
        
        // pumping state
        case PUMPING: {
            // pump only runs while trigger is held
            if(input.pumpHeld()) {
                digitalWrite(pumpControlPin, HIGH);
            }  else {
                    digitalWrite(pumpControlPin, LOW);
            }

            // get fuel amount from flow sensor
            fuelAmount = flowSensor.getFuelAmount();

            // calculate running total
            totalCost = fuelAmount * selectedPrice;

            // periodically refresh OLED display
            if(millis() - lastUpdateTime >= 100) {
                lastUpdateTime = millis();
                display.showPumpingScreen(fuelAmount, totalCost);
            }

            // complete transaction
            if(input.stopPressed()) {
                digitalWrite(pumpControlPin, LOW);
                wasCancelled = false;
                state = COMPLETE;
            }
            break;
        }
        
        // complete state
        case COMPLETE:
            digitalWrite(pumpControlPin, LOW);

            // reset system for next transaction
            if(input.startPressed()) {
                flowSensor.reset();

                fuelAmount = 0.0f;
                selectedPrice = 0.0f;
                totalCost = 0.0;

                wasCancelled = false;

                state = READY;
            }
            break;
    }
}

// execute one-time logic when entering a new state
void FuelPumpSystem::handleStateEntry() {
    // state has changed
    if(state != prevState) {
        switch(state) {
            case READY:
                display.showReadyScreen();
                break;
            
            case FUEL_SELECTION:
                display.showFuelSelectionScreen();
                break;

            case PUMPING: 
                display.showPumpingScreen(fuelAmount, totalCost);
                break;

            case COMPLETE:
                display.showCompleteScreen(wasCancelled, fuelAmount, selectedPrice, totalCost);
                break;
        }

        // update previous state tracker
        prevState = state;
    }
}