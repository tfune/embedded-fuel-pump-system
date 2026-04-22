#pragma once
#include <Arduino.h>
#include <Adafruit_SSD1306.h>

class Display {
public:
    void init();
    void showState(const String& state);
    void showFuel(float fuel, float cost);

private:
    Adafruit_SSD1306 oled;
};