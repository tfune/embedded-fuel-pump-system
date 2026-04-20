#include <Arduino.h>
#include "FuelPumpSystem.h"

FuelPumpSystem fuelPump;

void setup() {
    Serial.begin(9600);
    fuelPump.init();

    pinMode(2, INPUT_PULLUP);
}

void loop() {
    fuelPump.update();
}