#ifndef ENCODER_H_INCLUDED
#define ENCODER_H_INCLUDED
byte Encoder_C1Last;
int pulse_number;
boolean direction_m;

class encoder
{
private:
    int pin_C1;
    int pin_C2;

public:
    encoder(/* args */);

    void setup(int pin1,int pin2);
    int obtem_rotacao();
};



#endif