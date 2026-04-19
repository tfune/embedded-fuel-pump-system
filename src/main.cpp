#include <Arduino.h>
#include "GasPumpSystem.h"

GasPumpSystem gasPump;

void setup() {
    Serial.begin(9600);
    gasPump.init();
}

void loop() {
    gasPump.update();
}