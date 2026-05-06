#include "InputHandler.h"

void InputHandler::init() {
    // initialize events
    startEvent = false;
    stopEvent = false;
    exitEvent = false;
    fuel1Event = false;
    fuel2Event = false;
    fuel3Event = false; 

    // initialize pump button
    pinMode(pumpButtonPin, INPUT_PULLUP);
    pumpState = false;
}

void InputHandler::update() {
    // reset one-cycle events
    startEvent = false;
    stopEvent = false;
    exitEvent = false;
    fuel1Event = false;
    fuel2Event = false;
    fuel3Event = false;

    // read pump button (continuous input)
    pumpState = (digitalRead(pumpButtonPin) == LOW);

    // read key; exit if no input
    char key = keypad.getKey();
    if(!key) return;

    // system control mapping
    if(key == 'A') startEvent = true;
    if(key == 'B') stopEvent = true;
    if(key == 'D') exitEvent = true;

    // fuel selection mapping
    if(key == '1') fuel1Event = true;
    if(key == '2') fuel2Event = true;
    if(key == '3') fuel3Event = true;
}

// event getters
bool InputHandler::startPressed() { return startEvent; }
bool InputHandler::stopPressed() { return stopEvent; }
bool InputHandler::exitPressed() { return exitEvent; }

bool InputHandler::fuel1Pressed() { return fuel1Event; }
bool InputHandler::fuel2Pressed() { return fuel2Event; }
bool InputHandler::fuel3Pressed() { return fuel3Event; }

// continuous pump button
bool InputHandler::pumpHeld() {
    return pumpState;
}