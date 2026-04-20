#pragma once

enum State {
    IDLE,
    FUEL_SELECTION,
    PUMPING,
    COMPLETE
};

class GasPumpSystem {
public:
    void init();
    void update();

private:
    State state;
};