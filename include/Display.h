#pragma once
#include <Arduino.h>
#include <Adafruit_SSD1306.h>

// Handles all OLED screen rendering for fuel pump system
class Display {
public:
    // initialize OLED display
    void init();

    // state screens
    void showReadyScreen();
    void showFuelSelectionScreen();
    void showPumpingScreen(float fuel, float cost);
    void showCompleteScreen(bool cancelled, float fuel, float price, float total);

private:
    // OLED display object
    Adafruit_SSD1306 oled;
};