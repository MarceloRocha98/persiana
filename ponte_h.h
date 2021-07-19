#ifndef PONTE_H_INCLUDED
#define PONTE_H_INCLUDED

class ponte_h
{
private:
    int pin;


public:
    ponte_h();

    void setup(int pinSentido);
    void horario();
    void ant_horario();
};



#endif