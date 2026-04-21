#include "InputHandler.h"

void InputHandler::init() {
    inputBuffer = "";
    lastKey = 0;
}

void InputHandler::update() {
    // Reset events every cycle
    startEvent = false;
    fuelEvent = false;
    stopEvent = false;

    char key = keypad.getKey();
    if(!key) return;
    lastKey = key;

    // Event Mapping
    if(key == 'A') startEvent = true;
    if(key == 'B') fuelEvent = true;
    if(key == 'C') stopEvent = true;

    // Input Buffer
    if(key >= '0' && key <= '9') {
        inputBuffer += key;
    }

    if(key == '*') {
        inputBuffer = "";
    }
}

bool InputHandler::startPressed() {
    return startEvent;
}

bool InputHandler::fuelPressed() {
    return fuelEvent;
}

bool InputHandler::stopPressed() {
    return stopEvent;
}

String InputHandler::getInputBuffer() {
    return inputBuffer;
}

void InputHandler::clearBuffer() {
    inputBuffer = "";
}