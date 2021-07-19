//ldr.cpp
#include "ldr.h"

ldr::ldr(/* args */)
{
}

void ldr::setup(int pin)
{
    pino = pin;
    pinMode(pin,OUTPUT);
}

int ldr::obtem_luminosidade(void)
{
    int valor = analogRead(pino);
    return valor;
}


//end ldr.cpp