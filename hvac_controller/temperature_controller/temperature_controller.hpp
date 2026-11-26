#include "mbed.h"

I2C temp_sensor(I2C_SDA, I2C_SCL);      //Configure I2C interface 

BufferedSerial pc(USBTX, USBRX, 9600);  
const int temp_addr = 0x90;             //I2C address of temperature sensor DS1631 
char commands[] = {0x51, 0xAA}; 
char read_temp[2]; 

class Temperature; 

constexpr int OFF = 0;
constexpr int ON = 1;

inline DigitalOut fan(D2);
inline DigitalOut heating(D4);