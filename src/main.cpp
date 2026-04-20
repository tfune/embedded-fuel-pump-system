#include <Arduino.h>
#include "FuelPumpSystem.h"

FuelPumpSystem fuelPump;

void setup() {
    Serial.begin(9600);
    fuelPump.init();
}

void loop() {
    fuelPump.update();
}