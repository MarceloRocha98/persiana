#ifndef LDR_H_INCLUDED
#define LDR_H_INCLUDED

class ldr
{
private:
    int pino;

public:
    ldr(/* args */);

    void setup(int pin); // A0
    int obtem_luminosidade(void);
};


#endif