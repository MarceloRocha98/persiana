#ifndef MOTOR_H_INCLUDED
#define MOTOR_H_INCLUDED


class motor
{
private:
    int pin;

public:
    motor(/* args */);

    void setup(int pin);
    void rotaciona(int value);
};



#endif