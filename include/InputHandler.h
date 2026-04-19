#pragma once

class InputHandler {
public:
    InputHandler(int startPin, int stopPin, int fuelPin);

    void init();
    void update();

    bool startPressed();
    bool stopPressed();
    bool fuelPressed();

private:
    int startPin;
    int stopPin;
    int fuelPin;
};