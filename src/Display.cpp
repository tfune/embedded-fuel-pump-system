#include <Arduino.h>
#include "display.h"

void Display::init() {
    Serial.println("Display ready");
}

void Display::showReady() {
    Serial.println("State: READY");
}

void Display::showMessage(const char* msg) {
    Serial.println(msg);
}