// HVAC Controller built for NUCLEO_WL55JC

#include "mbed.h"
#include "lcd_controller/lcd_controller.hpp"
#include "buzzer_controller/buzzer_controller.hpp"
#include "buzzer_controller/tunes.hpp"
#include "button_controller/button_controller.hpp"
#include "button_controller/button_controller_heat.cpp"
#include "button_controller/button_controller_cool.cpp"
#include "temperature_controller/temperature_controller.hpp"         

/* 
Summary of active pins:
- D2    DigitalOut for a fan  
- D3    increase temperature button 
- D4    heater LED (dummy for a real heater) 
- D5    decrease temperature button 
- D7    button User Control (when alarm goes on, user takes control and stops it)
- D9    buzzer


*/
// main() runs in its own thread in the OS
int main()
{ 
    DigitalIn user_control_button(D7, PullUp);

    fan = OFF;      // Make sure the fan OFF at the start by assigning the pin to a value of the HVAC flag
    heating = OFF;  // represented by the red LED that lights up when heating is ON

    MbedInterruptPin d3_pin(D3);
    ButtonHeat button_heat(d3_pin);

    ButtonCool button_cool;

    CS=1;
    init_lcd();  //initialise the LCD 
    clr_lcd();   //Clear the LCD 
    update_lcd();
    
    init_buzzer(D9);
    signal_ptr = &Welcome;
    play_signal(signal_ptr);

    while (true) {
        ThisThread::sleep_for(1000ms);
        update_lcd();
        TempWatchdog (current_temp); 

        if (alarm_flag && user_control_button.read() == 0) {
            stop_signal();
        }
    }
}

