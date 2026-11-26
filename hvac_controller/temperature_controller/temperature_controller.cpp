#include "temperature_controller.hpp"
#include <iostream>
#include "../button_controller/button_controller.hpp"

class Temperature {
public:
    Temperature() {}

    inline static float current_temp = 0.0f;

    static float getTemp() {
        return current_temp; 
    }

    static void setTemp() {
        //Write 0x51 to 0x90 to start temperature conversion 
        temp_sensor.write(temp_addr, &commands[0], 1, false); 
        thread_sleep_for (500);    //wait for the conversion to complete 

        //Write 0xAA to 0x90 to read the last converted temperature 
        temp_sensor.write(temp_addr, &commands[1], 1, false); 

        //Read the temperature into the read_temp array 
        temp_sensor.read(temp_addr, read_temp, 2); 

        //Convert temperature to Celsius 
        current_temp = (float((read_temp[0] << 8) | read_temp[1]) / 256); 

        //Print temperature to the serial monitor 
        printf("Temp = %d.%d\r\n", int(current_temp), int((current_temp-int(current_temp))*10)); 

    }

    static void IncreaseTemp() {

        if (fan == ON) {
            fan = OFF;
        }

        if (heating == OFF) {
            heating = ON;
        }
    }

    static void DecreaseTemp() {
        if (heating == ON) {
            heating = OFF;
        }

        if (fan == OFF) {
            fan = ON;
        }
    }

    // Monitor temperature and stop fan or heating once the 
    // desired temperature is reached 
    static void TempWatchdog (float desired_temp) {
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
        }
    }
};