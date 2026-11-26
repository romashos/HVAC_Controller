#include "button_controller.hpp"
#include "../temperature_controller/temperature_controller.hpp"

class ButtonCool {
private:
    InterruptIn fan_on{D3};

public:
    ButtonCool() {
        fan_on.fall(mbed::callback(this, &ButtonCool::ISR));
    }

    // Responds to the press of Cool button, and sets fan status ON
    void ISR() {
        if (fan == OFF) {
            fan = ON;
        }
    }
};