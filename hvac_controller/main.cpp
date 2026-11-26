// HVAC Controller built for NUCLEO_WL55JC

#include "mbed.h"
#include "lcd_controller/lcd_controller.hpp"
#include "buzzer_controller/buzzer_controller.hpp"
#include "buzzer_controller/tunes.hpp"
#include "button_controller/button_controller.hpp"
#include "button_controller/button_controller_heat.cpp"
#include "temperature_controller/temperature_controller.hpp"

namespace {
    constexpr PinName BUZZER_PIN = D9;  //for piezo sounder 
    }             

// main() runs in its own thread in the OS
int main()
{ 
    fan = OFF;      // Make sure the fan OFF at the start by assigning the pin to a value of the HVAC flag
    heating = OFF;  // represented by the red LED that lights up when heating is ON

    MbedInterruptPin d3_pin(D3);
    ButtonHeat button_heat(d3_pin);

    CS=1;
    init_lcd();  //initialise the LCD 
    clr_lcd();   //Clear the LCD 
    start_lcd();
    
    init_buzzer(BUZZER_PIN);
    signal_ptr = &Welcome;
    play_signal(signal_ptr);

    while (true) {

    }
}

