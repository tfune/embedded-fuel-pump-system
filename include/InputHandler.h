#pragma once
#include <Arduino.h>
#include <Keypad.h>

class InputHandler {
public:
    void init();
    void update();

    bool startPressed();
    bool stopPressed();
    bool fuelPressed();

    String getInputBuffer();
    void clearBuffer();

private:
    static const byte ROWS = 4;
    static const byte COLS = 4;

    char keys[ROWS][COLS] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}
    };

    byte rowPins[ROWS] = {22, 23, 24, 25};
    byte colPins[COLS] = {26, 27, 28, 29};

    Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

    char lastKey = 0;

    String inputBuffer = "";

    bool startEvent = false;
    bool fuelEvent = false;
    bool stopEvent = false;
};