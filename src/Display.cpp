#include "Display.h"
#include <Wire.h>

// OLED display dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Initialize OLED display hardware
void Display::init() {
    oled = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

    // Halt system if display initialization fails
    if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("OLED init failed");

        while (true);
    }

    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(SSD1306_WHITE);
}

// Display ready state screen
void Display::showReadyScreen() {
    oled.clearDisplay();

    oled.setCursor(0,0);
    oled.println("Welcome to Trevor's");
    oled.print("Gas Station!");

    oled.setCursor(0, 24);
    oled.print("Press A to Start");

    oled.display();
}

// Display fuel selection screen
void Display::showFuelSelectionScreen() {
    oled.clearDisplay();

    oled.setCursor(0, 0);
    oled.print("Select Fuel:");

    oled.setCursor(0, 16);
    oled.println("1: Regular");
    oled.println("2: Premium");
    oled.print("3: Diesel");

    oled.display();
}

// Display active fueling information
void Display::showPumpingScreen(float fuel, float cost) {
    oled.clearDisplay();

    oled.setCursor(0,0);
    oled.println("Press button to");
    oled.print("begin fueling");

    oled.setCursor(0, 24);
    oled.print("Fuel: ");
    oled.print(fuel);
    oled.println(" oz");

    oled.print("Cost: $");
    oled.print(cost);

    oled.setCursor(0, 48);
    oled.print("Press B to Stop");

    oled.display();
}

// Display completed transaction summary
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
    oled.print("Ounces: ");
    oled.print(fuel);

    oled.setCursor(0, 24);
    oled.print("Price/Ounce: $");
    oled.print(price);

    oled.setCursor(0, 32);
    oled.print("Total: $");
    oled.print(total);

    oled.setCursor(0, 48);
    oled.print("Press A to Restart");

    oled.display();
 }

 // Display system fault message
 void Display::showErrorScreen(const char* errorMessage) {
    oled.clearDisplay();

    oled.setCursor(0, 0);
    oled.println("SYSTEM ERROR");

    oled.setCursor(0, 16);
    oled.println(errorMessage);

    oled.setCursor(0, 48);
    oled.print("Press A to Reset");

    oled.display();
 }