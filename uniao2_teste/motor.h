#ifndef MOTOR_H_INCLUDED
#define MOTOR_H_INCLUDED


class motor
{
private:
    int pino;
// int IN1 = D4;
// int IN2 = D3;
// int ENA=D2;
public:
    motor(/* args */);

    void setup(int pin); //ENA
    void rotaciona(int value);
};



#endif