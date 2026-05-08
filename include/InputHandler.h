#pragma once
#include <Arduino.h>
#include <Keypad.h>

// Handles keypad input and pump trigger button events
class InputHandler {
public:
    void init(); // initialize input hardware
    void update(); // poll all inputs and update event states

    // system control events
    bool startPressed();
    bool stopPressed();
    bool exitPressed();

    // fuel selection events
    bool fuel1Pressed();
    bool fuel2Pressed();
    bool fuel3Pressed();

    // pump trigger state
    bool pumpHeld();

private:
    // keypad dimensions
    static const byte ROWS = 4;
    static const byte COLS = 4;

    // keypad layout
    char keys[ROWS][COLS] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}
    };

    // Arduino pin mapping
    byte rowPins[ROWS] = {22, 23, 24, 25};
    byte colPins[COLS] = {26, 27, 28, 29};

    // keypad object
    Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

    // pump trigger button
    static const int pumpButtonPin = 37;
    bool pumpState = false;

    // one-cycle keypad event flags
    bool startEvent = false;
    bool stopEvent = false;
    bool exitEvent = false;
    bool fuel1Event = false;
    bool fuel2Event = false;
    bool fuel3Event = false;
};