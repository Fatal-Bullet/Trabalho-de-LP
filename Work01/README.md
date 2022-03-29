Jogo da velha


Requisitos obrigatorios 
```c
// codgio em C: jogo da velha




#include <stdio.h> // Entrada e saída padronizadas
#include <ctype.h> // Manipulação de caracteres
#include <stdlib.h> //
#include <time.h> //

typedef struct Old
 {
    int match;
    char result;
    char hash[3][3];
 } Match;

 int jogada_usuario(
  int lin,
  int col,
  char jog
);

void jogada_computador(
  char jog,
  int nivel
);

int menu();

void choice();

void inicializa_velha();

int difficulty(); // dificuldade
void nivel_basico( // 
	char simbpc
);
void intermediary(
	char simbpc
);
void advanced(
	char simbpc
);

int nmr_partida = 1;

void playAgain();
void jogadas_pvp();
void jogadas_pve();

char oldGameMatriz[3][3];
char game;
int i, j;
Match Game;
char *simb1;
char *simb2;
char PlayerName1[50];
char PlayerName2[50];
```
