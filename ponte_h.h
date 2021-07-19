#ifndef PONTE_H_INCLUDED
#define PONTE_H_INCLUDED

class ponte_h
{
private:
    int pinS1;
    int pinS2;

public:
    ponte_h();

    void setup(int pinSentido1,int pinSentido2);
    void horario();
    void ant_horario();
};



#endif