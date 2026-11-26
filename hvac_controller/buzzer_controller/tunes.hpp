// tunes.hpp
// This is a collection of sound signals 
// Each signal is stored as a struct

#pragma once

struct Signal{    
    char name[17];   //the signal name 
    int length;      //no of notes in signal 
    float freq[30];  //frequency array 
    float beat[30];   //beat array 
    }; 

struct Signal *signal_ptr;  //points to selected signal 

struct Signal Welcome={ 
    .name="Welcome", 
    .length=11,         
    .freq={659,554,659,554,440,494,554,587,494,659,554,440},
    .beat={2,2,2,2,2,1,1,2,2,2,2,4}
    }; 

struct Signal ButtonPressed = {
    .name = "Button Pressed",
    .length = 2,
    .freq = 600.0f,
    .beat = 0.5f
};

struct Signal Alarm = {
    .name = "Alarm",
    .length = 4,
    .freq = 1200.0f,
    .beat = 0.25f
    //.repeats = 3,
    //.active = false
};