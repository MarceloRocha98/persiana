// pont_h.cpp

#include "ponte_h.h"


ponte_h::ponte_h()
{

}

void ponte_h::setup(int pinSentido1,int pinSentido2)
{
    pinS1 = pinSentido1;
    pinS2 = pinSentido2;
    pinMode(pinSentido1, OUTPUT);
    pinMode(pinSentido2, OUTPUT);
}
void ponte_h::horario(/* args */)
{
    digitalWrite(pinS1,LOW);
    digitalWrite(pinS2,HIGH);
}

void ponte_h::ant_horario()
{
    digitalWrite(pinS1,LOW);
    digitalWrite(pinS1,HIGH);
}

// end pont_h.cpp
