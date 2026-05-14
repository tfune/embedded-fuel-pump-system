#pragma once

#include <Arduino.h>
#include <Keypad.h>

// Handles keypad input and pump trigger events
class InputHandler {
public:
    // Initializes keypad and button input hardware
    void init();

    // Polls all inputs and updates event states
    void update();

    // System control input events
    bool startPressed();
    bool stopPressed();
    bool exitPressed();

    // Fuel selection input events
    bool fuel1Pressed();
    bool fuel2Pressed();
    bool fuel3Pressed();

    // Returns true while the pump trigger is held
    bool pumpHeld();

private:
    // Keypad dimensions
    static const byte ROWS = 4;
    static const byte COLS = 4;

    // Keypad character layout
    char keys[ROWS][COLS] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}
    };

    // Arduino GPIO pin mapping for keypad rows and columns
    byte rowPins[ROWS] = {22, 23, 24, 25};
    byte colPins[COLS] = {26, 27, 28, 29};

    // keypad driver instance
    Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

    // Pump trigger button input pin
    static const int pumpButtonPin = 37;

    // Current trigger button state
    bool pumpState = false;

    // One-cycle keypad event flags
    bool startEvent = false;
    bool stopEvent = false;
    bool exitEvent = false;
    bool fuel1Event = false;
    bool fuel2Event = false;
    bool fuel3Event = false;
};