#pragma once
#include <Arduino.h>
#include <Adafruit_SSD1306.h>

class Display {
public:
    void init();

    // different member function for each state
    void showReadyScreen();
    void showFuelSelectionScreen();
    void showPumpingScreen(float fuel, float cost);
    void showCompleteScreen(bool cancelled, float fuel, float price, float total);

private:
    Adafruit_SSD1306 oled;
};