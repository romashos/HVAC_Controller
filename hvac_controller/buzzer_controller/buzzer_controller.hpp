#include "mbed.h"
#include "tunes.hpp"

inline bool alarm_flag = false;

void init_buzzer(PinName pin);
void play_signal(Signal *signal_ptr);
void stop_signal();