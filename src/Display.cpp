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

void Display::showReadyScreen() {
    oled.clearDisplay();

    oled.setCursor(0,0);
    oled.println("Welcome to Trevor's");
    oled.print("Gas Station!");

    oled.setCursor(0, 24);
    oled.print("Press A to Start");

    oled.display();
}

void Display::showFuelSelectionScreen() {
    oled.clearDisplay();

    oled.setCursor(0, 0);
    oled.print("Select Fuel:");

    oled.setCursor(0, 16);
    oled.print("1: Regular");

    oled.setCursor(0, 24);
    oled.print("2: Premium");

    oled.setCursor(0, 32);
    oled.print("3: Diesel");

    oled.display();
}

void Display::showPumpingScreen(float fuel, float cost) {
    oled.clearDisplay();

    oled.setCursor(0,0);
    oled.print("PUMPING");

    oled.setCursor(0, 16);
    oled.print("Fuel: ");
    oled.print(fuel);

    oled.setCursor(0, 24);
    oled.print("Cost: $");
    oled.println(cost);

    oled.setCursor(0, 40);
    oled.print("Press B to Stop");

    oled.display();
}

 void Display::showCompleteScreen(bool cancelled, float fuel, float price, float total) {
    oled.clearDisplay();

    oled.setCursor(0, 0);
    if(cancelled) {
        oled.print("Transaction Cancelled");
    }
    else {
        oled.print("Transaction Complete");
    }

    oled.setCursor(0, 16);
    oled.print("Gallons: ");
    oled.print(fuel);

    oled.setCursor(0, 24);
    oled.print("Price/Gallon: $");
    oled.print(price);

    oled.setCursor(0, 32);
    oled.print("Total: $");
    oled.print(total);

    oled.setCursor(0, 48);
    oled.print("Press A to Restart");

    oled.display();
 }