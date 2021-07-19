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
    digitalWrite(pin, HIGH);
    delay_ms(100*value);
    digitalWrite(pin, LOW);
}




//end motor.cpp