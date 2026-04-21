#pragma once
#include <Arduino.h>
#include <Keypad.h>

class InputHandler {
public:
    void init(); // initialize input system
    void update(); // poll keypad and update state

    // event checks (true for one update cycle)
    bool startPressed();
    bool stopPressed();
    bool fuelPressed();

    // numeric input handling
    String getInputBuffer();
    void clearBuffer();

private:
    // keypad dimensions
    static const byte ROWS = 4;
    static const byte COLS = 4;

    // key layout
    char keys[ROWS][COLS] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}
    };

    // hardwire pin mapping
    byte rowPins[ROWS] = {22, 23, 24, 25};
    byte colPins[COLS] = {26, 27, 28, 29};

    Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

    // internal state
    char lastKey;
    String inputBuffer;

    // one-cycle event flags
    bool startEvent = false;
    bool fuelEvent = false;
    bool stopEvent = false;
};