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
    // digitalWrite(pino, HIGH);
     analogWrite(pino,1024);
    delay_ms(100*value);
     analogWrite(pino,0);
    // digitalWrite(pino, LOW);
}




//end motor.cpp