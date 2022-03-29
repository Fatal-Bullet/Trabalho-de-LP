#include <stdio.h> // Entrada e saída padronizadas
#include <ctype.h> // Manipulação de caracteres
#include <stdlib.h> // alocação de memória
#include <time.h> // manipulação de datas e horários de modo padrão. random.

typedef struct Velha{int partida;char JogVelha[3][3];char resultado;}Partida;
int jogada_usuario(int lin,int col,char jog);
void jogada_computador(char jog,int level);
int menu();
void escolha_simb();
void inicializa_velha();
int verifica_ganhador(char jog);

int escolha_dificuldade();
void basicLevel(char simbpc);
void level_intermediario(char simbpc);
void level_avancado(char simbpc);
int defesas(char simbhu, char simbolo);
int ataques(char simbhu, char simbolo);
int nmr_partida = 1;

void jogar_novamente();
void throw_pvp();
void throw_pve();

char velha[3][3];
char jog;
int i, j;
Partida Jogo;
char *simb1;
char *simb2;
char nome_j1[50];
char nome_j2[50];

/*MAIN*/
void main(){
  int menureturn = 0;
  int dif = 0;
  menureturn = menu();

  if(menureturn == 1){
    setbuf(stdin,NULL);
    printf("Digite o seu nome: \n");
    gets (nome_j1);
    dif = escolha_dificuldade();
    escolha_simb(&simb1,&simb2);
    inicializa_velha();
    throw_pve(&simb1,&simb2,dif);
  }
  else if (menureturn == 2) {
    setbuf(stdin,NULL);
    printf("\nDigite o nome do jogador 1: ");
    gets (nome_j1);
    printf("\nDigite o nome do jogador 2: ");
    gets (nome_j2);
    escolha_simb(&simb1,&simb2);
    inicializa_velha();
    throw_pvp(&simb1,&simb2);
  }
}
/*MENU*/
int menu(){
  int escolha_menu = 0;
  char escolha_tipo ='Q';
  char saida ='Y';

  fflush(stdin); limpar o buffer
  system("cls");
  printf("\n Bem vindo ao jogo da velha!");
  printf("\n I - Jogar");
  printf("\n Qualquer número - Sair \n");
  scanf("\n%d",&escolha_menu);
  if(escolha_menu==1){
    do{
        fflush(stdin); limpar o buffer
        system("cls");
        printf("\n Escolha seu adversario: ");
        printf("\n I- Computador");
        printf("\n II- Jogador \n");
        scanf("\n%c",&escolha_tipo);
        escolha_tipo = toupper(escolha_tipo);

        switch(escolha_tipo){
        case 'I': saida='Q';return 1;
            break;
        case 'II': saida='Q';return 2;
            break;
        default: printf("Opção inválida");
            break;
        }
    }while(saida != 'Q');
}else{}
}
/*DIFICULDADE*/
int escolha_dificuldade(){
char escolha_dif;
int saida_dif = 0;

    do{
        fflush(stdin); // limpar o buffer
        system("cls");
        printf("\n Escolha a dificuldade");
        printf("\n I - Básico");
        printf("\n II - Intermediário");
        printf("\n III - Avançado\n");
        scanf("\n%c",&escolha_dif);
        escolha_dif = toupper(escolha_dif);

        switch (escolha_dif){
        case 'I': return 1; saida_dif = 1;
        break;
        case 'II': return 2; saida_dif = 1;
        break;
        case 'III': return 3; saida_dif = 1;
        break;
        default: printf("\tOpção inválida!");}}while(saida_dif != 1);}
/*INICIALIZA_VELHA*/
void inicializa_velha(){ //zera as casas da velha
  for (j = 0; j < 3; j++) { for (i = 0; i < 3; i++) { velha[i][j] = ' '; } } }
/*ESCOLHA_SIMB*/
 void escolha_simb(char *jog1, char *jog2){
    int saida_simb= 0;
    do{
        fflush(stdin); // limpar o buffer
        system("cls");
        printf("Escolha seu símbolo: 'X' ou 'O':\n");
        scanf("%c",jog1);
        *jog1 = toupper(*jog1);
        if (*jog1 == 'X') {*jog2 = 'O';saida_simb = 1;} // se o jogador 1 for X, logo jogador 2 sera O;
        else if (*jog1 == 'O') {*jog2 = 'X';saida_simb = 1;} // se não jogador 1 O, e jogador 2 X;
        else{printf("\tOpção Inválida!\n");}// se nem uma opção for validade emitir erro de opção invalida
 }while (saida_simb !=1);
 }
/*throw_PVP*/

void throw_pvp(char *simb1, char *simb2){
    int l = 0;
    int i = 0;
    int returnValue;
    int vez = 0;
    int throw = 0;
    int verifica1 = 0;
    int verifica2 = 0;
    int nmr_partida = 1;
    char escolha;
    char saida;
    int erro;

    do{
    fflush(stdin); // limpar o buffer
    system("cls");
    printf(" \t      1   2   3 \n\n");
    printf("\t 1    %c | %c | %c \n",velha[0][0], velha[0][1], velha[0][2]);
    printf("\t     ---=---=--- \n");
    printf("\t 2    %c | %c | %c \n",velha[1][0], velha[1][1], velha[1][2]);
    printf("\t     ---=---=--- \n");
    printf("\t 3    %c | %c | %c \n",velha[2][0], velha[2][1], velha[2][2]);
    fflush(stdin); // limpar o buffer
    printf("\nInsira a linha desejada: ");
    scanf("%d",&i);
    printf("\nInsira a coluna desejada: ");
    scanf("%d",&l);

       if(vez%2==0){jog = *simb1;i = i-1;l = l-1;
        returnValue = jogada_usuario(i,l,jog);
            if(returnValue == 0){
              verifica1 = verifica_ganhador(jog);
              if (verifica1 == 1) {
                fflush(stdin); // // limpar o buffer
                system("cls");
                printf(" \t      1   2   3 \n\n");
                printf("\t 1    %c | %c | %c \n",velha[0][0], velha[0][1], velha[0][2]);
                printf("\t     ---=---=--- \n");
                printf("\t 2    %c | %c | %c \n",velha[1][0], velha[1][1], velha[1][2]);
                printf("\t     ---=---=--- \n");
                printf("\t 3    %c | %c | %c \n",velha[2][0], velha[2][1], velha[2][2]);
                printf("\n\tParabéns %c você venceu! \n",jog);
                Jogo.partida = nmr_partida;
                Jogo.resultado = jog;
                for (j = 0; j < 3; j++) {
                    for (i = 0; i < 3; i++) {
                        Jogo.JogVelha[i][j] = velha[i][j];
                    }}
                printf("%d",erro);
                break;
              }
                throw++;
                vez++;

            }else if(returnValue == 1){
                printf("\tPosição inválida!\n");
            }
            else{printf("\tPosição já ocupada!\n");}
       }
       else{jog = *simb2; i = i-1; l = l-1;
        returnValue = jogada_usuario(i,l,jog);
             if(returnValue == 0){ verifica2 = verifica_ganhador(jog);
               if (verifica2 == 1) {
                 fflush(stdin); // limpar o buffer
                 system("cls");
                 printf(" \t      1   2   3 \n\n");
                 printf("\t 1    %c | %c | %c \n",velha[0][0], velha[0][1], velha[0][2]);
                 printf("\t     ---=---=--- \n");
                 printf("\t 2    %c | %c | %c \n",velha[1][0], velha[1][1], velha[1][2]);
                 printf("\t     ---=---=--- \n");
                 printf("\t 3    %c | %c | %c \n",velha[2][0], velha[2][1], velha[2][2]);
                 printf("\n\tParabéns %c você venceu! \n",jog);
                Jogo.partida = nmr_partida;
                Jogo.resultado = jog;
                for (j = 0; j < 3; j++) {
                    for (i = 0; i < 3; i++) {
                        Jogo.JogVelha[i][j] = velha[i][j];
                    }
                    }
                printf("%d",erro);
                 break;
               }
                throw++;
                vez++;}
            else if(returnValue == 1){printf("\tPosição inválida!\n");}
            else{printf("\tPosição já ocupada!\n");}
       }
    }while(throw < 9);
    if (verifica1 == 0 && verifica2 == 0) {
      system("cls");
      printf(" \t      1   2   3 \n\n");
      printf("\t 1    %c | %c | %c \n",velha[0][0], velha[0][1], velha[0][2]);
      printf("\t     ---=---=--- \n");
      printf("\t 2    %c | %c | %c \n",velha[1][0], velha[1][1], velha[1][2]);
      printf("\t     ---=---=--- \n");
      printf("\t 3    %c | %c | %c \n",velha[2][0], velha[2][1], velha[2][2]);
      printf("\n\t# Deu VELHA!! #\n");
        Jogo.partida = nmr_partida;
        Jogo.resultado = 'V';
        for (j = 0; j < 3; j++) {
            for (i = 0; i < 3; i++) {
                    Jogo.JogVelha[i][j] = velha[i][j];
                    }}
       printf("%d",erro);}
    jogar_novamente();}
/*throw_PVE*/
void throw_pve(
  char *simb1,
  char *simb2,
  int dif
){
    int l = 0;
    int i = 0;
    int returnValue;
    int vez = 0;
    int throw = 0;
    int verifica1 = 0;
    int verifica2 = 0;
    int level = 0;
    level = dif;

    do{
    fflush(stdin); // limpar o buffer
    system("cls");
    printf(" \t      1   2   3 \n\n");
    printf("\t 1    %c | %c | %c \n",velha[0][0], velha[0][1], velha[0][2]);
    printf("\t     ---=---=--- \n");
    printf("\t 2    %c | %c | %c \n",velha[1][0], velha[1][1], velha[1][2]);
    printf("\t     ---=---=--- \n");
    printf("\t 3    %c | %c | %c \n",velha[2][0], velha[2][1], velha[2][2]);
       if(vez%2==0){
         fflush(stdin); // limpar o buffer
         printf("\nInsira a linha desejada: ");
         scanf("%d",&i);
         printf("\nInsira a coluna desejada: ");
         scanf("%d",&l);
        jog = *simb1;
        i = i-1;
        l = l-1;
        returnValue = jogada_usuario(i,l,jog);
            if(returnValue == 0){
              verifica1 = verifica_ganhador(jog);
              if (verifica1 == 1) {
                system("cls");
                printf(" \t      1   2   3 \n\n");
                printf("\t 1    %c | %c | %c \n",velha[0][0], velha[0][1], velha[0][2]);
                printf("\t     ---=---=--- \n");
                printf("\t 2    %c | %c | %c \n",velha[1][0], velha[1][1], velha[1][2]);
                printf("\t     ---=---=--- \n");
                printf("\t 3    %c | %c | %c \n",velha[2][0], velha[2][1], velha[2][2]);
                printf("\n\tParabéns %c você venceu! \n",jog);
                break;
                }throw++;vez++;}
            else if(returnValue == 1){ printf("\tPosição inválida!\n");}
            else{printf("\tPosição já ocupada!\n");}}
            else if(vez%2==1){ jog = *simb2;
        jogada_computador(jog, level);
               verifica2 = verifica_ganhador(jog);
               if (verifica2 == 1) {
                 system("cls");
                 printf(" \t      1   2   3 \n\n");
                 printf("\t 1    %c | %c | %c \n",velha[0][0], velha[0][1], velha[0][2]);
                 printf("\t     ---=---=--- \n");
                 printf("\t 2    %c | %c | %c \n",velha[1][0], velha[1][1], velha[1][2]);
                 printf("\t     ---=---=--- \n");
                 printf("\t 3    %c | %c | %c \n",velha[2][0], velha[2][1], velha[2][2]);
                 printf("\n\tVocê foi perdeu! GAME OVER! \n");
                 break;
               }
                throw++;
                vez++;
       }
    }while(throw < 9);
    if (verifica1 == 0 && verifica2 == 0) { //se nem o primeiro e nem o segundo jogador venceram, entao houve empate
      system("cls");
      printf(" \t      1   2   3 \n\n");
      printf("\t 1    %c | %c | %c \n",velha[0][0], velha[0][1], velha[0][2]);
      printf("\t     ---=---=--- \n");
      printf("\t 2    %c | %c | %c \n",velha[1][0], velha[1][1], velha[1][2]);
      printf("\t     ---=---=--- \n");
      printf("\t 3    %c | %c | %c \n",velha[2][0], velha[2][1], velha[2][2]);
      printf("\n\t# Deu VELHA!! #\n");
    }
    jogar_novamente();
}
/*JOGADA_USUARIO*/
int jogada_usuario(int lin, int col, char jog){
    if(lin < 0 || col < 0 || lin > 2 || col > 2){ return 1;} // verifica se o jogador mandou um valor possivel
    else if(velha[lin][col] != ' '){ return 2;} //verifica se a casa esta dispolevel para throw
    else{ velha[lin][col] = jog; return 0;}} //se jogar cumpriu os requisitos de jogada entao preenche a casa
/*VERIFICA_GANHADOR*/
  int verifica_ganhador(char jog){ // verifica todas as possiveis vitorias em um jogo
  if (velha[0][0] == jog && velha[0][1] == jog && velha[0][2] == jog) {return 1;}
  else if (velha[1][0] == jog && velha[1][1] == jog && velha[1][2] == jog) {return 1;}
  else if (velha[2][0] == jog && velha[2][1] == jog && velha[2][2] == jog) {return 1;}
  else if (velha[0][0] == jog && velha[1][0] == jog && velha[2][0] == jog) {return 1;}
  else if (velha[0][1] == jog && velha[1][1] == jog && velha[2][1] == jog) {return 1;}
  else if (velha[0][2] == jog && velha[1][2] == jog && velha[2][2] == jog) {return 1;}
  else if (velha[0][2] == jog && velha[1][1] == jog && velha[2][0] == jog) {return 1;}
  else if (velha[0][0] == jog && velha[1][1] == jog && velha[2][2] == jog) {return 1;}
  else{return 0;}}
/*JOGADA_COMPUTADOR*/
void jogada_computador(
  char jog,
  int level
){
  char simbpc;
  simbpc = jog;

  if (level == 1) {
    basicLevel(simbpc); //faz jogada e printa na tela
    system("cls");
    printf(" \t      1   2   3 \n\n");
    printf("\t 1    %c | %c | %c \n",velha[0][0], velha[0][1], velha[0][2]);
    printf("\t     ---=---=--- \n");
    printf("\t 2    %c | %c | %c \n",velha[1][0], velha[1][1], velha[1][2]);
    printf("\t     ---=---=--- \n");
    printf("\t 3    %c | %c | %c \n",velha[2][0], velha[2][1], velha[2][2]);
  }else if (level == 2) {
    level_intermediario(simbpc); //faz jogada e printa na tela
    printf(" \t      1   2   3 \n\n");
    printf("\t 1    %c | %c | %c \n",velha[0][0], velha[0][1], velha[0][2]);
    printf("\t     ---=---=--- \n");
    printf("\t 2    %c | %c | %c \n",velha[1][0], velha[1][1], velha[1][2]);
    printf("\t     ---=---=--- \n");
    printf("\t 3    %c | %c | %c \n",velha[2][0], velha[2][1], velha[2][2]);
  }else if (level == 3) {
    level_avancado(simbpc); //faz jogada e printa na tela
    printf(" \t      1   2   3 \n\n");
    printf("\t 1    %c | %c | %c \n",velha[0][0], velha[0][1], velha[0][2]);
    printf("\t     ---=---=--- \n");
    printf("\t 2    %c | %c | %c \n",velha[1][0], velha[1][1], velha[1][2]);
    printf("\t     ---=---=--- \n");
    printf("\t 3    %c | %c | %c \n",velha[2][0], velha[2][1], velha[2][2]);
  }else{
    printf("\tERROR level NAO DECIDIDO!!\n");
  }
}
/*level_BASICO*/
void basicLevel(
  char simbpc
  ){
  int lin;
  int col;
  char simbolo;
  simbolo = simbpc;

  srand((unsigned)time(NULL)); lin = rand()%3; //level basico apenas joga randomicamente
  srand((unsigned)time(NULL)); col = rand()%3;
  if (velha[lin][col] == ' ') {velha[lin][col] = simbolo;}
  else{do {
      srand((unsigned)time(NULL));lin = rand()%3;
      srand((unsigned)time(NULL));col = rand()%3;
    } while(velha[lin][col] != ' '); velha[lin][col] = simbolo; }
}
/*level_INTERMEDIARIO*/
void level_intermediario(char simbpc){
  int lin;
  int col;
  char simbolo;
  char simbhu;
  int retdef;
  simbolo = simbpc;
  if (simbpc == 'X') {simbhu = 'O';}
  else if(simbpc == 'O'){simbhu = 'X';}

  retdef = defesas(simbhu, simbolo);
  if (retdef == 2) { //se defesa nao foi bem sucedida entao tenta random
    srand((unsigned)time(NULL)); lin = rand()%3;
    srand((unsigned)time(NULL)); col = rand()%3;
    if (velha[lin][col] == ' ') {velha[lin][col] = simbpc;}
    else{
      do {srand((unsigned)time(NULL)); lin = rand()%3;
          srand((unsigned)time(NULL)); col = rand()%3; }
      while(velha[lin][col] != ' '); velha[lin][col] = simbpc;}}}
/*level_AVANCADO*/
void level_avancado(char simbpc){
  int lin;
  int col;
  int aux = 0;
  int retdef = 0;
  int retatq = 0;
  char simbolo;
  char simbhu;
  simbolo = simbpc;
       if (simbpc == 'X') { simbhu = 'O';}//se o simbolo do PC é um ex: X, player fica com o outro ex: O
  else if(simbpc == 'O'){ simbhu = 'X';}
  do { if (velha[1][1] == ' ') { velha[1][1] = simbpc;break;} //se o meio esta livre entao joga nele
    else if(
             velha[0][0] == ' ' || velha[0][1] == ' ' || velha[0][2] == ' ' ||
             velha[1][0] == ' ' || velha[1][1] == ' ' || velha[1][2] == ' ' ||
             velha[2][0] == ' ' || velha[2][1] == ' ' || velha[2][2] == ' '
             ){ retatq = ataques(simbhu, simbolo); //se houver casas vazias, tenta ataque
             if (retatq == 1) { break;} //se houve ataque bem sucedido entao termina o dowhile
        else if (retatq == 2) { retdef = defesas(simbhu, simbolo);//caso nao haja lugar bom para ataque, entao tenta defender
             if (retdef == 1) { //se houve defesa bem sucedida entao termina o dowhile
            break;}
            else if(retdef == 2){
                 if (velha[0][0] == simbhu && velha[1][1] == ' ' && velha[2][0] != simbhu && velha[0][2] != simbhu) {
                 if (velha[2][2] == ' ') {velha[2][2] = simbpc; break;}}
            else if (velha[0][2] == simbhu && velha[1][1] == ' ' && velha[0][0] != simbhu && velha[2][2] != simbhu) {
                 if (velha[2][0] == ' ') {velha[2][0] = simbpc;break;}}
            else if (velha[2][0] == simbhu && velha[1][1] == ' ' && velha[0][0] != simbhu && velha[2][2] != simbhu) {
                 if (velha[0][2] == ' ') {velha[0][2] = simbpc;break;}}
            else if (velha[2][2] == simbhu && velha[1][1] == ' ' && velha[0][2] != simbhu && velha[2][0] != simbhu) {
                 if (velha[0][0] == ' ') { velha[0][0] = simbpc;break;} }
            else if(velha[1][1] == simbpc){ //se o meio ja foi preenchido pelo pc
                 if (velha[0][0] == simbhu && velha[2][2] == simbhu && velha[2][0] != simbhu && velha[0][2] != simbhu) { //defesa contra throw nas pontas
                 if (velha[0][1] == ' ') {velha[0][1] = simbpc; break;}
            else if (velha[2][1] == ' ') {velha[2][1] = simbpc; break;}
            else if (velha[1][2] == ' ') {velha[1][2] = simbpc;break;}
            else if (velha[1][0] == ' ') {velha[1][0] = simbpc;break;}}
            else if (velha[2][0] == simbhu && velha[0][2] == simbhu && velha[0][0] != simbhu && velha[2][2] != simbhu) { //defesa contra throw nas pontas
                 if (velha[0][1] == ' ') { velha[0][1] = simbpc; break;}
            else if (velha[2][1] == ' ') {velha[2][1] = simbpc;break;}
            else if (velha[1][2] == ' ') {velha[1][2] = simbpc; break;}
            else if (velha[1][0] == ' ') {velha[1][0] = simbpc;break;}}
                else{ srand((unsigned)time(NULL)); lin = rand()%3;
                      srand((unsigned)time(NULL)); col = rand()%3;
                 if (velha[lin][col] == ' ') { velha[lin][col] = simbpc; aux = 1;} //se houver casa vazia nos indices escolhidos randomicamente, entao joga
                else{ //se nao houver casa vazia nos indices escolhidos randomicamente, entao randomiza novamente
                  do {  srand((unsigned)time(NULL)); lin = rand()%3;
                        srand((unsigned)time(NULL)); col = rand()%3;} 
                  while(velha[lin][col] != ' '); velha[lin][col] = simbpc; aux = 1;}}}
            else if (velha[1][1] == simbhu) { //se o player jogou no meio, entao joga nos cantos
                 if (velha[0][0] == ' ') {velha[0][0] = simbpc;aux = 1;}
            else if (velha[0][2] == ' ') {velha[0][2] = simbpc; aux = 1;}
            else if (velha[2][0] == ' ') { velha[2][0] = simbpc; aux = 1; }
            else if (velha[2][2] == ' ') { velha[2][2] = simbpc;aux = 1;}
            else{ srand((unsigned)time(NULL)); lin = rand()%3;
                  srand((unsigned)time(NULL)); col = rand()%3;
                 if (velha[lin][col] == ' ') { velha[lin][col] = simbpc; aux = 1; } //se houver casa vazia nos indices escolhidos randomicamente, entao joga
                else{ //se nao houver casa vazia nos indices escolhidos randomicamente, entao randomiza novamente
                  do { srand((unsigned)time(NULL)); lin = rand()%3;
                       srand((unsigned)time(NULL)); col = rand()%3;
                  }
                  while(velha[lin][col] != ' '); velha[lin][col] = simbpc;aux = 1;}}}}} break;}
  } while(aux != 1); //se ja terminou jogada, entao para dowhile
}
/*DEFESAS*/
int defesas(
  char simbhu,
  char simbolo
){
  int lin;
  int col;
  int aux = 0;
  int ret = 0;
  char simbdef;
  char simbhudef;
  simbdef = simbolo;
  simbhudef = simbhu;

do { //verifica todas casas com possibilidades de defesa
  if (velha[0][0] == simbhudef && velha[0][2] == simbhudef && velha[0][1] == ' ') {velha[0][1] = simbdef;aux = 1;ret = 1;}
  else if (velha[1][0] == simbhudef && velha[1][2] == simbhudef && velha[1][1] == ' ') {velha[1][1] = simbdef;aux = 1;ret = 1;}
  else if (velha[2][0] == simbhudef && velha[2][2] == simbhudef && velha[2][1] == ' ') {velha[2][1] = simbdef;aux = 1;ret = 1;}
  else if (velha[0][0] == simbhudef && velha[2][0] == simbhudef && velha[1][0] == ' ') {velha[1][0] = simbdef;aux = 1;ret = 1;}
  else if (velha[1][0] == simbhudef && velha[2][1] == simbhudef && velha[1][1] == ' ') {velha[1][1] = simbdef;aux = 1;ret = 1;}
  else if (velha[0][2] == simbhudef && velha[2][2] == simbhudef && velha[1][2] == ' ') {velha[1][2] = simbdef;aux = 1;ret = 1;}
  else if (velha[2][0] == simbhudef && velha[2][1] == simbhudef && velha[2][2] == ' ') {velha[2][2] = simbdef;aux = 1;ret = 1;}
  else if (velha[1][0] == simbhudef && velha[1][1] == simbhudef && velha[1][2] == ' ') {velha[1][2] = simbdef;aux = 1;ret = 1;}
  else if (velha[0][0] == simbhudef && velha[0][1] == simbhudef && velha[0][2] == ' ') {velha[0][2] = simbdef;aux = 1;ret = 1;}
  else if (velha[0][2] == simbhudef && velha[0][1] == simbhudef && velha[0][0] == ' ') {velha[0][0] = simbdef;aux = 1;ret = 1;}
  else if (velha[1][1] == simbhudef && velha[1][2] == simbhudef && velha[1][0] == ' ') {velha[1][0] = simbdef;aux = 1;ret = 1;}
  else if (velha[2][1] == simbhudef && velha[2][2] == simbhudef && velha[2][0] == ' ') {velha[2][0] = simbdef;aux = 1;ret = 1;}
  else if (velha[0][0] == simbhudef && velha[2][2] == simbhudef && velha[1][1] == ' ') {velha[1][1] = simbdef;aux = 1;ret = 1;}
  else if (velha[0][2] == simbhudef && velha[2][0] == simbhudef && velha[1][1] == ' ') {velha[1][1] = simbdef;aux = 1;ret = 1;}
  else if (velha[0][0] == simbhudef && velha[1][0] == simbhudef && velha[2][0] == ' ') {velha[2][0] = simbdef;aux = 1;ret = 1;}
  else if (velha[0][1] == simbhudef && velha[1][1] == simbhudef && velha[2][1] == ' ') {velha[2][1] = simbdef;aux = 1;ret = 1;}
  else if (velha[0][2] == simbhudef && velha[1][2] == simbhudef && velha[2][2] == ' ') {velha[2][2] = simbdef;aux = 1;ret = 1;}
  else if (velha[1][0] == simbhudef && velha[2][0] == simbhudef && velha[0][0] == ' ') {velha[0][0] = simbdef;aux = 1;ret = 1;}
  else if (velha[1][1] == simbhudef && velha[2][1] == simbhudef && velha[0][1] == ' ') {velha[0][1] = simbdef;aux = 1;ret = 1;}
  else if (velha[1][2] == simbhudef && velha[2][2] == simbhudef && velha[0][2] == ' ') {velha[0][2] = simbdef;aux = 1;ret = 1;}
  else if (velha[2][0] == simbhudef && velha[1][1] == simbhudef && velha[0][2] == ' ') {velha[0][2] = simbdef;aux = 1;ret = 1;}
  else if (velha[0][2] == simbhudef && velha[1][1] == simbhudef && velha[2][0] == ' ') { velha[2][0] = simbdef; aux = 1; ret = 1; }
  else if (velha[2][2] == simbhudef && velha[1][1] == simbhudef && velha[0][0] == ' ') { velha[0][0] = simbdef; aux = 1; ret = 1; }
  else if (velha[0][0] == simbhudef && velha[1][1] == simbhudef && velha[2][2] == ' ') { velha[2][2] = simbdef; aux = 1; ret = 1; }
  else{ aux = 1;ret = 2;}}
  while(aux != 1);

  if (ret == 1) {return 1; }//se retorna 1, entao houve defesa possivel
  else if (ret == 2) {return 2; }// se retorna 2, nao houve defesa possivel
}
/*ATAQUES*/
int ataques(
  char simbhu,
  char simbolo
){
  int lin; col; aux = 0; ret = 0;
  char simbataq; simbhudef;
  simbataq = simbolo;
  simbhudef = simbhu;

  do { //verifica todas as possibilidades de ataque disponiveis
    if (velha[0][0] == simbataq && velha[0][2] == simbataq && velha[0][1] == ' ') {velha[0][1] = simbataq;aux = 1; ret = 1;}
    else if (velha[1][0] == simbataq && velha[1][2] == simbataq && velha[1][1] == ' ') {velha[1][1] = simbataq;aux = 1;ret = 1;}
    else if (velha[2][0] == simbataq && velha[2][2] == simbataq && velha[2][1] == ' ') {velha[2][1] = simbataq;aux = 1;ret = 1;}
    else if (velha[0][0] == simbataq && velha[2][0] == simbataq && velha[1][0] == ' ') {velha[1][0] = simbataq;aux = 1;ret = 1;}
    else if (velha[1][0] == simbataq && velha[2][1] == simbataq && velha[1][1] == ' ') {velha[1][1] = simbataq;aux = 1;ret = 1;}
    else if (velha[0][2] == simbataq && velha[2][2] == simbataq && velha[1][2] == ' ') {velha[1][2] = simbataq;aux = 1;ret = 1;}
    else if (velha[2][0] == simbataq && velha[2][1] == simbataq && velha[2][2] == ' ') {velha[2][2] = simbataq;aux = 1;ret = 1;}
    else if (velha[1][0] == simbataq && velha[1][1] == simbataq && velha[1][2] == ' ') {velha[1][2] = simbataq;aux = 1;ret = 1;}
    else if (velha[0][0] == simbataq && velha[0][1] == simbataq && velha[0][2] == ' ') {velha[0][2] = simbataq;aux = 1;ret = 1;}
    else if (velha[0][2] == simbataq && velha[0][1] == simbataq && velha[0][0] == ' ') {velha[0][0] = simbataq;aux = 1;ret = 1;}
    else if (velha[1][1] == simbataq && velha[1][2] == simbataq && velha[1][0] == ' ') {velha[1][0] = simbataq;aux = 1;ret = 1;}
    else if (velha[2][1] == simbataq && velha[2][2] == simbataq && velha[2][0] == ' ') {velha[2][0] = simbataq;aux = 1;ret = 1;}
    else if (velha[0][0] == simbataq && velha[2][2] == simbataq && velha[1][1] == ' ') {velha[1][1] = simbataq;aux = 1;ret = 1;}
    else if (velha[0][2] == simbataq && velha[2][0] == simbataq && velha[1][1] == ' ') {velha[1][1] = simbataq;aux = 1;ret = 1;}
    else if (velha[0][0] == simbataq && velha[1][0] == simbataq && velha[2][0] == ' ') {velha[2][0] = simbataq;aux = 1;ret = 1;}
    else if (velha[0][1] == simbataq && velha[1][1] == simbataq && velha[2][1] == ' ') {velha[2][1] = simbataq;aux = 1;ret = 1;}
    else if (velha[0][2] == simbataq && velha[1][2] == simbataq && velha[2][2] == ' ') {velha[2][2] = simbataq;aux = 1;ret = 1;}
    else if (velha[1][0] == simbataq && velha[2][0] == simbataq && velha[0][0] == ' ') {velha[0][0] = simbataq;aux = 1;ret = 1;}
    else if (velha[1][1] == simbataq && velha[2][1] == simbataq && velha[0][1] == ' ') {velha[0][1] = simbataq;aux = 1;ret = 1;}
    else if (velha[1][2] == simbataq && velha[2][2] == simbataq && velha[0][2] == ' ') {velha[0][2] = simbataq;aux = 1;ret = 1;}
    else if (velha[2][0] == simbataq && velha[1][1] == simbataq && velha[0][2] == ' ') {velha[0][2] = simbataq;aux = 1;ret = 1;}
    else if (velha[0][2] == simbataq && velha[1][1] == simbataq && velha[2][0] == ' ') {velha[2][0] = simbataq;aux = 1;ret = 1;}
    else if (velha[2][2] == simbataq && velha[1][1] == simbataq && velha[0][0] == ' ') {velha[0][0] = simbataq;aux = 1;ret = 1;}
    else if (velha[0][0] == simbataq && velha[1][1] == simbataq && velha[2][2] == ' ') {velha[2][2] = simbataq;aux = 1;ret = 1;}
    else{ aux = 1; ret = 2;} }
    while(aux != 1);

       if (ret == 1) { return 1; } // se houve ataques bem sucedidos, entao retorna 1
  else if (ret == 2) { return 2;  }} // se nao houve ataques bem sucedidos, entao retorna 2
/*JOGAR_NOVAMENTE*/
void jogar_novamente(){
  char option;
  int saida;
  do { fflush(stdin); // limpar o buffer
  printf("\n Você deseja jogar novamente? S/N: ");
  printf("S - para sim\n ");
  printf("N - Caso deseje sair.\n");
  fflush(stdin); // limpar o buffer
  scanf("%c",&option);
  option = toupper(option);
  switch (option) { 
    case 'S': main(); saida = 1;break;
    case 'N': system("cls");printf("\n\tObrigado por testestar o jogar!!\n"); saida = 1; break;}
    } while(saida != 1);}
