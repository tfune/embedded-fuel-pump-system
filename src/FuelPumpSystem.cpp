#include <Arduino.h>
#include "FuelPumpSystem.h"

// Initialize system hardware, drivers, and transaction state
void FuelPumpSystem::init() {
    state = READY;
    prevState = COMPLETE; // Forces initial display state

    input.init();
    display.init();
    pump.init(pumpControlPin);
    flowSensor.init(flowSensorPin);

    regPrice = 4.399f;
    premPrice = 4.999f;
    dieselPrice = 6.399f;

    fuelAmount = 0.0f;
    selectedPrice = 0.0f;
    totalCost = 0.0f;

    wasCancelled = false;
    currentError = NO_ERROR;

    lastUpdateTime = millis();
}

// Execute one state machine cycle
void FuelPumpSystem::update() {
    input.update();

    // Allow user to cancel the current transaction
    if(input.exitPressed()) {
        wasCancelled = true;
        pump.stop();
        state = COMPLETE;
    }

    handleStateEntry();

    switch(state) {
        case READY:
            pump.stop();

            if(input.startPressed()) {
                state = FUEL_SELECTION;
            }
            break;
        
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
        
        case PUMPING: {
            // Run pump only while trigger is held
            if(input.pumpHeld()) {
                // Start timeout and flow monitoring when pump first activates
                if(!pump.isRunning()) {
                    pumpStartTime = millis();

                    previousPulseCount = flowSensor.getPulseCount();
                    lastFlowCheckTime = millis();
                }

                pump.start();
            }  else {
                    pump.stop();
            }

            // Stop pump if maximum runtime is exceeded
            if(pump.isRunning() && 
                millis() - pumpStartTime >= MAX_PUMP_TIME)
            {
                pump.stop();
                currentError = TIMEOUT_ERROR;
                state = ERROR;
                break;
            }

            // Detect pump operation without flow sensor pulse activity
            if(pump.isRunning() &&
                millis() - lastFlowCheckTime >= FLOW_CHECK_INTERVAL)
            {
                lastFlowCheckTime = millis();
                unsigned long currentPulseCount = flowSensor.getPulseCount();

                if(currentPulseCount == previousPulseCount) {
                    pump.stop();
                    currentError = FLOW_ERROR;
                    state = ERROR;
                    break;
                }

                previousPulseCount = currentPulseCount;
            }

            fuelAmount = flowSensor.getFuelAmount();
            totalCost = fuelAmount * selectedPrice;

            // Refresh OLED at fixed interval
            if(millis() - lastUpdateTime >= 100) {
                lastUpdateTime = millis();
                display.showPumpingScreen(fuelAmount, totalCost);
            }

            if(input.stopPressed()) {
                pump.stop();
                wasCancelled = false;
                state = COMPLETE;
            }
            break;
        }

        case COMPLETE:
            pump.stop();

            if(input.startPressed()) {
                flowSensor.reset();

                fuelAmount = 0.0f;
                selectedPrice = 0.0f;
                totalCost = 0.0f;

                wasCancelled = false;
                currentError = NO_ERROR;

                state = READY;
            }
            break;

        case ERROR:
            pump.stop();

            if(input.startPressed()) {
                flowSensor.reset();

                fuelAmount = 0.0f;
                selectedPrice = 0.0f;
                totalCost = 0.0f;

                wasCancelled = false;
                currentError = NO_ERROR;

                state = READY;
            }

            break;
    }
}

// Handle one-time display updates when entering a new state
void FuelPumpSystem::handleStateEntry() {
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

        prevState = state;
    }
}