#include <Arduino.h>
#include "FuelPumpSystem.h"

void FuelPumpSystem::init() {
    // initialize states
    state = READY;
    prevState = COMPLETE; // force initial state entry handling

    // initialize system modules
    input.init();
    display.init();
    pump.init(pumpControlPin);
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
        pump.stop();
        state = COMPLETE;
    }

    // execute one-time state entry actions
    handleStateEntry();

    // main state machine
    switch(state) {
        // ready state
        case READY:
            pump.stop();

            if(input.startPressed()) {
                state = FUEL_SELECTION;
            }
            break;
        
        // fuel selection state
        case FUEL_SELECTION:
            pump.stop();

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
                // start timeout timer when pump first activates
                if(!pump.isRunning()) {
                    pumpStartTime = millis();

                    // initialize flow fault tracking
                    previousPulseCount = flowSensor.getPulseCount();
                    lastFlowCheckTime = millis();
                }

                pump.start();
            }  else {
                    pump.stop();
            }

            // automatic timeout protection
            if(pump.isRunning() && 
                millis() - pumpStartTime >= MAX_PUMP_TIME)
            {
                pump.stop();
                currentError = TIMEOUT_ERROR;
                state = ERROR;
                break;
            }

            // detect pump running without flow pulses
            if(pump.isRunning() &&
                millis() - lastFlowCheckTime >= FLOW_CHECK_INTERVAL)
            {
                lastFlowCheckTime = millis();
                unsigned long currentPulseCount = flowSensor.getPulseCount();

                // enter error state if no new pulses
                if(currentPulseCount == previousPulseCount) {
                    pump.stop();
                    currentError = FLOW_ERROR;
                    state = ERROR;
                    break;
                }

                // update previous pulse snapshot
                previousPulseCount = currentPulseCount;
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
                pump.stop();
                wasCancelled = false;
                state = COMPLETE;
            }
            break;
        }
        
        // complete state
        case COMPLETE:
            pump.stop();

            // reset system for next transaction
            if(input.startPressed()) {
                flowSensor.reset();

                fuelAmount = 0.0f;
                selectedPrice = 0.0f;
                totalCost = 0.0;

                wasCancelled = false;
                currentError = NO_ERROR;

                state = READY;
            }
            break;

        case ERROR:
            pump.stop();

            // reset system after fault
            if(input.startPressed()) {
                flowSensor.reset();

                fuelAmount = 0.0f;
                selectedPrice = 0.0f;
                totalCost = 0.0;

                wasCancelled = false;
                currentError = NO_ERROR;

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

            case ERROR:
                if(currentError == TIMEOUT_ERROR) {
                    display.showErrorScreen("Pump Timeout");
                } else if(currentError == FLOW_ERROR) {
                    display.showErrorScreen("No Flow Detected");
                } else {
                    display.showErrorScreen("Unknown Fault");
                }
                break;
        }

        // update previous state tracker
        prevState = state;
    }
}