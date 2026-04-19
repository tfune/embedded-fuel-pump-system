#include <Arduino.h>
#include "display.h"

void Display::init() {
    Serial.println("Display ready");
}

void Display::showIdle() {
    Serial.println("State: IDLE");
}

void Display::showMessage(const char* msg) {
    Serial.println(msg);
}