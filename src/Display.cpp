#include "Display.h"
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

void Display::init() {
    oled = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

    if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("OLED init failed");
        while (true);
    }

    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(SSD1306_WHITE);
}

void Display::showState(const String& state) {
    oled.clearDisplay();

    oled.setCursor(0,0);
    oled.print("STATE: ");
    oled.println(state);

    oled.display();
}

void Display::showFuel(float fuel, float cost) {
    oled.clearDisplay();

    // Top (yellow)
    oled.setCursor(0,0);
    oled.print("STATE: PUMPING");

    // Bottom (blue)
    oled.setCursor(0, 30);
    oled.print("Fuel: ");
    oled.println(fuel);

    oled.print("Cost: $");
    oled.println(cost);

    oled.display();
}