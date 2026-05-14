#include "InputHandler.h"

// Initialize input hardware
void InputHandler::init() {
    pinMode(pumpButtonPin, INPUT_PULLUP);
}

// Poll all user inputs and update event flags
void InputHandler::update() {
    // Reset one-cycle keypad events
    startEvent = false;
    stopEvent = false;
    exitEvent = false;

    fuel1Event = false;
    fuel2Event = false;
    fuel3Event = false;

    // Read continuous pump trigger state
    pumpState = (digitalRead(pumpButtonPin) == LOW);

    // Read keypad input
    char key = keypad.getKey();

    // Exit if no key was pressed
    if(!key) return;

    // System control key mappings
    if(key == 'A') startEvent = true;
    if(key == 'B') stopEvent = true;
    if(key == 'D') exitEvent = true;

    // Fuel selection key mappings
    if(key == '1') fuel1Event = true;
    if(key == '2') fuel2Event = true;
    if(key == '3') fuel3Event = true;
}

// Return system control event states
bool InputHandler::startPressed() { return startEvent; }
bool InputHandler::stopPressed() { return stopEvent; }
bool InputHandler::exitPressed() { return exitEvent; }

// Return fuel selection event states
bool InputHandler::fuel1Pressed() { return fuel1Event; }
bool InputHandler::fuel2Pressed() { return fuel2Event; }
bool InputHandler::fuel3Pressed() { return fuel3Event; }

// Return current pump trigger state
bool InputHandler::pumpHeld() {
    return pumpState; // returns true when trigger button is held
}