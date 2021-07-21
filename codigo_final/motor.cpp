//motor.cpp
#include "motor.h"
#include <Arduino.h>

motor::motor(/* args */)
{
}

void motor::setup(int pin) // ENA
{
    pino = pin; //ENA
    pinMode(pin, OUTPUT); 
    digitalWrite(pin, HIGH);
}





//end motor.cpp