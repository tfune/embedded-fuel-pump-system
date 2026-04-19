#include <Arduino.h>
#include "InputHandler.h"

InputHandler::InputHandler(int start, int stop, int fuel)
    : startPin(start), stopPin(stop), fuelPin(fuel) {}

void InputHandler::init() {
    pinMode(startPin, INPUT_PULLUP);
    pinMode(stopPin, INPUT_PULLUP);
    pinMode(fuelPin, INPUT_PULLUP);
}

void InputHandler::update() {
    // debounce logic (will do later)
}

bool InputHandler::startPressed() {
    return digitalRead(startPin) == LOW;
}

bool InputHandler::stopPressed() {
    return digitalRead(stopPin) == LOW;
}

bool InputHandler::fuelPressed() {
    return digitalRead(fuelPin) == LOW;
}