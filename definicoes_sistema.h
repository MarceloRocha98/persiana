#ifndef DEFINICOES_SISTEMA_H_INCLUDED
#define DEFINICOES_SISTEMA_H_INCLUDED

#define true  1
#define false 0


#define NUM_ESTADOS 5
#define NUM_EVENTOS 15

// ESTADOS
#define ESPERA                 0
#define OPERACAO_AUTOMATICA    1
#define OPERACAO_MANUAL        2
#define CONFIGURACAO_HORARIOS  3
#define OPERACAO_HORARIOS      4

// EVENTOS
#define NENHUM_EVENTO -1
#define S00  0
#define S01  1
#define S02  2
#define S03  3

#define S10  4
#define S11  5
#define S12  6
#define S13  7

#define S20  8
#define S21  9
#define S22  10

#define S30  11
#define S31  12
#define S32  13
#define S33  14

// ACOES
#define NENHUMA_ACAO -1
#define A0  0
#define A1  1
#define A2  2
#define A3  3



#endif // DEFINICOES_SISTEMA_H_INCLUDED
