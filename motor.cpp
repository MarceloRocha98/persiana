//motor.cpp
#include "motor.h"

motor::motor(/* args */)
{
}

void motor::setup(int pin)
{
    pino = pin;
    pinMode(pin, OUTPUT); 
}
void motor::rotaciona(int value)
{
    digitalWrite(pino, HIGH);
    delay_ms(100*value);
    digitalWrite(pino, LOW);
}




//end motor.cpp