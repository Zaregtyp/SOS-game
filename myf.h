//MUITO IMPORTANTE DE POR PORTOTYPES

typedef enum { VAZIO=' ', LETRA_O='O', LETRA_S='S'} cell;
typedef enum { JOGADOR1=1, JOGADOR2=0} num_player;
typedef unsigned color;
typedef struct {
        cell  V[8][8];  // Array bidimensional [8][8] com o valor de cada célula (VAZIO, LETRA_S ou LETRA_O)
        char  L[8][8];  // Array bidimensional [8][8] com as ligações de cada célula (1+2+4+8+16+32+64+128) - se existe ou não
        color C[8][8];  // Array bidimensional [8][8] com as cores das ligações de cada célula (1+2+4+8+16+32+64+128) - qual a cor (jogador)
        num_player P[8][8]; // Array bidimensional [8][8] com a indicação de qual o jogador que jogou a letra
        num_player turn;   // inteiro que designa quem é a vez do próximo a jogar (JOGADOR1 ou JOGADOR2)
        int countJ1;    // número de sequências SOS completadas pelo Jogagor 1 até ao momento (0 ou mais)
        int countJ2;    // número de sequências SOS completadas pelo Jogagor 2 até ao momento (0 ou mais)
        } sos;

#include "prototypes.h"

typedef int byte;   // cria um novo tipo chamado byte que é o mesmo que int
