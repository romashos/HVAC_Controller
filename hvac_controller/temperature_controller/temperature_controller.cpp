#include <iostream>
#include "mbed.h"

#include "../button_controller/button_controller.hpp"
#include "../buzzer_controller/buzzer_controller.hpp"
#include "../buzzer_controller/tunes.hpp"
#include "temperature_controller.hpp"

#ifndef UNIT_TEST
float getTemp() {
    temp_sensor.write(temp_addr, reinterpret_cast<const char*>(&commands[0]), 1, false);
    thread_sleep_for(500);

    temp_sensor.write(temp_addr, reinterpret_cast<const char*>(&commands[1]), 1, false);
    temp_sensor.read(temp_addr, read_temp, 2);

    current_temp = (float((read_temp[0] << 8) | read_temp[1]) / 256);

    printf("Temp = %d.%d\r\n", int(current_temp), int((current_temp - int(current_temp)) * 10));
    return current_temp;
}

void IncreaseTemp() {

    if (fan == ON) {
        fan = OFF;
    }

    if (heating == OFF) {
        heating = ON;
    }
}

void DecreaseTemp() {
    if (heating == ON) {
        heating = OFF;
    }

    if (fan == OFF) {
        fan = ON;
    }
}

// Monitor temperature and stop fan or heating once the 
// desired temperature is reached 
void TempWatchdog (float desired_temp) {
    if (current_temp > desired_temp + 2) {
        DecreaseTemp();
    }
    else if (desired_temp - 2 >= current_temp <= desired_temp + 2) {
        // Stop all HVAC activities
            heating = OFF;
            fan = OFF;
    }
    else if (current_temp < desired_temp - 2) {
        IncreaseTemp();
    } else {
        printf ("Error: Unknown temperature");
        play_signal(&Alarm);
        alarm_flag = true;
    }
}
#endif