#include "InputHandler.h"

void InputHandler::init() {
    inputBuffer = "";
    lastKey = '\0';
}

void InputHandler::update() {
    // reset one-cycle events
    startEvent = false;
    fuelEvent = false;
    stopEvent = false;

    // read key; exit if no input
    char key = keypad.getKey();
    if(!key) return;
    lastKey = key;

    // map keys to events
    if(key == 'A') startEvent = true;
    if(key == 'B') fuelEvent = true;
    if(key == 'C') stopEvent = true;

    // build numeric input
    if(key >= '0' && key <= '9') {
        inputBuffer += key;
    }

    // clear input
    if(key == '*') {
        inputBuffer = "";
    }
}

// event getters
bool InputHandler::startPressed() { return startEvent; }
bool InputHandler::fuelPressed() { return fuelEvent; }
bool InputHandler::stopPressed() { return stopEvent; }

// input buffer access
String InputHandler::getInputBuffer() { return inputBuffer; }
void InputHandler::clearBuffer() { inputBuffer = ""; }