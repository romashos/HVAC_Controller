#include "button_controller.hpp"
#include "../temperature_controller/temperature_controller.hpp"

class ButtonHeat {
public:
    explicit ButtonHeat(IInterruptPin& fan_off_pin);
    void ISR();

private:
    IInterruptPin& fan_off_;
};

ButtonHeat::ButtonHeat(IInterruptPin& fan_off_pin)
    : fan_off_(fan_off_pin) {
    fan_off_.on_fall([this]() { this->ISR(); });
}

void ButtonHeat::ISR() {
    if (fan == ON) {
        fan = OFF;
    }
}
