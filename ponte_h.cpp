// pont_h.cpp

#include "ponte_h.h"


ponte_h::ponte_h()
{

}

void ponte_h::setup(int pinSentido)
{
    pin = pinSentido;
    pinMode(pinSentido, OUTPUT);
}
void ponte_h::horario(/* args */)
{
    digitalWrite(pin,LOW);

}

void ponte_h::ant_horario()
{
    digitalWrite(pin,HIGH);

}

// end pont_h.cpp
