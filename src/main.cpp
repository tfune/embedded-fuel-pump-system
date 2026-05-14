#include <Arduino.h>
#include "FuelPumpSystem.h"

// Main fuel pump system controller instance
FuelPumpSystem fuelPump;

void setup() {
    Serial.begin(9600);

    // Initialize all system hardware and drivers
    fuelPump.init();
}

void loop() {
    // Execute one iteration of the application state machine
    fuelPump.update();
}