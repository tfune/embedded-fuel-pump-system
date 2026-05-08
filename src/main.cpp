#include <Arduino.h>
#include <Keypad.h>
#include "FuelPumpSystem.h"

// global instance of fuel pump system
FuelPumpSystem fuelPump;

void setup() {
    Serial.begin(9600);

    // initialize all hardware + system modules
    fuelPump.init();
}

void loop() {
    // run one iteration of the state machine
    fuelPump.update();
}