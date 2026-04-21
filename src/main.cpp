#include <Arduino.h>
#include <Keypad.h>
#include "FuelPumpSystem.h"

FuelPumpSystem fuelPump;

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {22, 23, 24, 25};
byte colPins[COLS] = {26, 27, 28, 29};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
    Serial.begin(9600);
    fuelPump.init();
}

void loop() {
    fuelPump.update();

    char key = keypad.getKey();

    if(key) {
        Serial.print("Pressed: ");
        Serial.println(key);
    }
}