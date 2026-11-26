#pragma once

#include <functional>

#ifndef UNIT_TEST
#include "mbed.h"
#endif

/* enum HvacMode {
    ON = 1,
    OFF = 0
}; */

// Preset the variable fan to non-working state at the start of the program
// This is important because the value of the variable fan allows to turn ON/OFF the fan.
// inline HvacMode fan = OFF;

/////////////////////////////////////////// TESTING

class IInterruptPin {
public:
    virtual ~IInterruptPin() = default;
    virtual void on_fall(std::function<void()> cb) = 0;
};

///////////////////////////////////////////

#ifndef UNIT_TEST
class MbedInterruptPin : public IInterruptPin {
public:
    explicit MbedInterruptPin(PinName pin) : pin_(pin) {}

    void on_fall(std::function<void()> cb) override {
        cb_ = std::move(cb);
        pin_.fall(mbed::callback(this, &MbedInterruptPin::handle_fall));
    }

private:
    void handle_fall() {
        if (cb_) {
            cb_();
        }
    }

    InterruptIn pin_;
    std::function<void()> cb_;
};

class ButtonHeat;
class ButtonCool;

#endif