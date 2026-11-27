#include "mbed.h"
#include <ctime>
#include <cstdio>
#include <string>

#include "../temperature_controller/temperature_controller.hpp"

// LCD Function Prototypes 
void clr_lcd(void); 
void init_lcd(void); 
void print_lcd(const char *string); 
void shift_out(int data); 
void write_cmd(int cmd); 
void write_data(char c);  
void write_4bit(int data); 
void start_lcd();
void update_lcd();

DigitalOut CS(D10); 