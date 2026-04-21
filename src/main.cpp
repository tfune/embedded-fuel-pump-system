#include <Arduino.h>
#include <Keypad.h>
#include "FuelPumpSystem.h"

FuelPumpSystem fuelPump; // main system interface

void setup() {
    Serial.begin(9600); // initialize serial output
    fuelPump.init(); // initialize system
}

void loop() {
    fuelPump.update(); // run main system loop
}