#include "motor.cpp"
#include "ponte_h.cpp"

#define pinMotor 5
#define pinDir 0

motor motor;
ponte_h ponte_h;

void setup()
{
    motor.setup(pinMotor);
    ponte_h.setup(pinDir);

}

void teste()
{
    ponte_h.horario();
    motor.rotaciona(30);
    ponte_h.ant_horario();
    motor.rotaciona(30);
}

void loop()
{
    teste();
}