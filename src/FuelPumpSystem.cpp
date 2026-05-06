#include <Arduino.h>
#include "FuelPumpSystem.h"

// pulse counter updated by interrupt
volatile unsigned long flowPulseCount = 0;

// calibration factor
float calibrationFactor = 8.625;

// interrupt service routine
void flowPulseISR() {
    flowPulseCount++;
}

void FuelPumpSystem::init() {
    // initialize states
    state = READY;
    prevState = COMPLETE; // force initial state entry (triggers state print)

    input.init(); // initialize input handler
    display.init(); // initialize OLED display

    // initialize pump pin
    pinMode(pumpControlPin, OUTPUT);
    digitalWrite(pumpControlPin, LOW);

    // initialize flow sensor
    pinMode(flowSensorPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(flowSensorPin), flowPulseISR, RISING);

    // reset counters
    flowPulseCount = 0;
    fuelAmount = 0;
    selectedPrice = 0;
    totalCost = 0;

    // initialize pricing
    regPrice = 4.399;
    premPrice = 4.999;
    dieselPrice = 6.399;

    lastUpdateTime = millis();
}

void FuelPumpSystem::update() {
    input.update(); // poll user input

    // GLOBAL EXIT: works in any state
    if(input.exitPressed()) {
        wasCancelled = true;
        digitalWrite(pumpControlPin, LOW);
        state = COMPLETE;
    }

    handleStateEntry(); // handle one-time state transitions

    switch(state) {
        case READY:
            // pump off
            digitalWrite(pumpControlPin, LOW);

            // wait for user to start transaction
            if(input.startPressed()) {
                state = FUEL_SELECTION;
            }
            break;
        
        case FUEL_SELECTION:
            // pump off
            digitalWrite(pumpControlPin, LOW);

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
            // only pump when button is held
            if(input.pumpHeld()) {
                digitalWrite(pumpControlPin, HIGH);
            }  else {
                    digitalWrite(pumpControlPin, LOW);
            }

            // flow sensor calculation
            fuelAmount = flowPulseCount / calibrationFactor;
            totalCost = fuelAmount * selectedPrice;

            // update OLED display
            display.showPumpingScreen(fuelAmount, totalCost);

            // stop pumping on user input
            if(input.stopPressed()) {
                digitalWrite(pumpControlPin, LOW);
                wasCancelled = false;
                state = COMPLETE;
            }
            break;
        }
        
        case COMPLETE:
            // pump off
            digitalWrite(pumpControlPin, LOW);

            // wait for user to restart
            if(input.startPressed()) {
                flowPulseCount = 0;
                fuelAmount = 0;
                selectedPrice = 0;
                totalCost = 0;
                state = READY;
            }
            break;
    }
}

void FuelPumpSystem::handleStateEntry() {
    // execute once when entering a new state
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

        prevState = state; // update state tracker
    }
}