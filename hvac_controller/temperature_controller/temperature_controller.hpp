#pragma once

#include <cstdint>

#ifndef UNIT_TEST
#include "mbed.h"
#endif

constexpr int OFF = 0;
constexpr int ON = 1;

inline constexpr int temp_addr = 0x90;
inline uint8_t commands[] = {0x51, 0xAA};
inline char read_temp[2];

class Temperature;

#ifndef UNIT_TEST
inline I2C temp_sensor(I2C_SDA, I2C_SCL);
inline BufferedSerial pc(USBTX, USBRX, 9600);
inline DigitalOut fan(D2);
inline DigitalOut heating(D4);
#else
inline int fan = OFF;
inline int heating = OFF;
#endif