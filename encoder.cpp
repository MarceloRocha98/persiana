//encoder.cpp
#include "encoder.h"

encoder::encoder(/* args */)
{
}

void encoder::setup(int pin1,int pin2)
{
    pin_C1 = pin1;
    pin_C2 = pin2;

  pinMode(pin_C1,  INPUT);                //Configura entrada C1 para leitura do encoder
  pinMode(pin_C2,  INPUT);                //Configura entrada C2 para leitura do encoder
  attachInterrupt(0, obtem_rotacao, CHANGE);   //Interrupção externa 0 por mudança de estado
}

int encoder::obtem_rotacao()
{


  int Lstate = digitalRead(pin_C1);       //Lê estado de pin_C1 e armazena em Lstate
  
  if(!Encoder_C1Last && Lstate)               //Encoder_C1Last igual a zero e Lstate diferente de zero?
  {                                           //Sim...
    int val = digitalRead(pin_C2);        //Lê estado de pin_C2 e armazena em val
    
    if(!val && direction_m) direction_m = false;      //Sentido reverso
    
    else if(val && !direction_m) direction_m = true;  //Sentido direto
    
  } //end if 
 
  Encoder_C1Last = Lstate;                    //Encoder_C1Last recebe o valor antigo

  if(!direction_m)  pulse_number++;           //incrementa número do pulso se direction limpa
  else              pulse_number--;           //senão decrementa

  

    return pulse_number;
}

//end encoder.cpp
