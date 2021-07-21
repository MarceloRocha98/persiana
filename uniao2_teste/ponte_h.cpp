// pont_h.cpp

#include "ponte_h.h"
#include <Arduino.h>

ponte_h::ponte_h()
{

}

void ponte_h::setup(int pinSentido1,int pinSentido2)
{
    pinIN1 = pinSentido1;
    pinIN2 = pinSentido2;
    pinMode(pinIN1, OUTPUT);
    pinMode(pinIN2, OUTPUT);
}
void ponte_h::horario(/* args */)
{
    digitalWrite(pinIN1, HIGH);
    digitalWrite(pinIN2, LOW);

}

void ponte_h::ant_horario()
{
    digitalWrite(pinIN1, LOW);
    digitalWrite(pinIN2, HIGH);

}

// end pont_h.cpp
