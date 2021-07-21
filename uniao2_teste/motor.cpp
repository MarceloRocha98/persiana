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
}
void motor::rotaciona(int value)
{
    // digitalWrite(pino, HIGH);
     digitalWrite(pino, HIGH);
     delay(100*value); 
     digitalWrite(pino, LOW);

    // digitalWrite(pino, LOW);
}




//end motor.cpp