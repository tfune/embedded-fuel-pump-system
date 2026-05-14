#pragma once

#include <Arduino.h>
#include <Adafruit_SSD1306.h>

// Handles all OLED screen rendering for fuel pump system
class Display {
public:
    // Initializes OLED display hardware
    void init();

    // Displays the main system state screens
    void showReadyScreen();
    void showFuelSelectionScreen();
    void showPumpingScreen(float fuel, float cost);
    void showCompleteScreen(bool cancelled, float fuel, float price, float total);
    void showErrorScreen(const char* errorMessage);

private:
    // OLED display driver instance
    Adafruit_SSD1306 oled;
};