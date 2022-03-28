#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

typedef struct Velha
 {
    int partida;
    char JogVelha[3][3];
    char resultado;
 }Partida;

int jogada_usuario(
  int lin, 
  int col, 
  char jog
);
// int jogada_usuario(int lin, int col, char jog)
// : esta função preenche a posição informada pelos
// parâmetros lin (linha) e col (coluna) com ‘X’ ou ‘O’ que são passados para a função através de
// parâmetro jog. A função retorna um dos seguintes valores:

// 0 – se a jogada é válida
// 1 – se a posição informada é inválida
// 2 – se a posição informada já está preenchida

void jogada_computador(
  char jog, 
  int nivel
  );
// 2.void jogada_computador(char jog, int nivel)
// : esta função realiza a jogada do computador. O
// parâmetro  jog   define   se   o  computador   é   ‘X’  ou   ‘O’  e   o   parâmetro   nível   define   se  a  jogada   do
// computador   é   de   nível   básico,   intermediário   ou   avançado.   Você   deve   criar   uma   função   para
// jogada nível básico do computador; outra função para a jogada nível intermediário do computador;
// e   outra   função   para   a   jogada   nível   avançado   do   computador.   Estas   funções   deverão   ser
// chamadas dentro desta função jogada_computador.
int menu();

// 3.int menu( )
// : esta função retorna 1 se o usuário quer jogar contra o computador ou 2 caso o
// usuário queira jogar contra outro usuário. Caso o usuário queira jogar contra o computador ele
// também deve escolher o nível da jogada do computador: básico, intermediário ou avançado.
void escolha_simb();

// 4. void escola_simb(char *jog1, char *jog2)
// : esta função define via entrada do usuário quem é
// o jogador ‘X’ e quem é o jogador ‘O’

void inicializa_velha();// 5. void inicializa_velha( )
// : esta função inicializa a matriz do jogo da velha com vazio.

int verifica_ganhador(char jog);
// 6. int verifica_ganhador(char jog)
// : esta função retorna 1 se o jogador ganhou e zero caso
// contrário. O parâmetro jog conterá ‘X’ ou ‘O’.

void grava_arquivo();
// 7. Criar uma função que grava em um arquivo txt as informações abaixo, no seguinte formato:
// Nome do Jogador 1; símbolo; Nome do Jogador 2; símbolo.
// Exemplo: Maria; X; José; 0.
int grava_binario(
  char nome_arquivo,
  struct Velha Partida
  );
// 8. Criar uma função que grava em um arquivo binário uma partida do Jogo da Velha. Os dados
// devem ser gravados utilizando a seguinte estrutura:
// typedef struct Velha
// {
//      int partida; /*número da partida (Ex: primeira(1), segunda(2), terceira(3), ....,
//                                                         partida)*/
//      char JogVelha[3][3]; // Tabuleiro do jogo. Armazenará as jogadas
//      char resultado; // Resultado da Partida: X, 0 ou V(equivale a Velha - empate)
// } Partida;
// A função deve ter como entrada os seguintes parâmetros: (1) parâmetro string com o nome
// do arquivo; (2) parâmetro Partida com os dados da partida. A função retorna 1 se a gravação
// for um sucesso e zero caso contrário.
// Os jogadores podem jogar quantas partidas desejarem. Ao final de cada partida esta função
// deve ser chamada para gravar os dados da partida no arquivo.
void le_binario();
// 9. Criar uma função que lê do arquivo binário os dados de uma determinada partida. A função
// deve ter como entrada os seguintes parâmetros: (1) parâmetro string com o nome do arquivo; (2)
// parâmetro inteiro com o número da partida a ser lida. A função retorna o registro com os dados da
// partida que foi lida.
void imprimir_partida();
// 10.   Criar   uma   função   que   imprime   na   tela   todas   as   partidas   (tabuleiros   com   as   respectivas
// jogadas   e   quem   ganhou)   e   o   placar   final   (Ex:   Maria   10   X   José   5)  A  Maria   foi   a   campeã   do
// Campeonato de Jogo da Velha!!!

int escolha_dificuldade();
void nivel_basico(char simbpc);
void nivel_intermediario(char simbpc);
void nivel_avancado(char simbpc);
int defesas(char simbhu, char simbolo);
int ataques(char simbhu, char simbolo);
int nmr_partida = 1;

void jogar_novamente();
void jogadas_pvp();
void jogadas_pve();

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
    jogadas_pve(&simb1,&simb2,dif);


  }else if (menureturn == 2) {
    setbuf(stdin,NULL);
    printf("\nDigite o nome do jogador 1: ");
    gets (nome_j1);
    printf("\nDigite o nome do jogador 2: ");
    gets (nome_j2);
    escolha_simb(&simb1,&simb2);
    inicializa_velha();
    jogadas_pvp(&simb1,&simb2);
  }

}

/*MENU*/

int menu(){
  int escolha_menu = 0;
  char escolha_tipo ='Q';
  char saida ='Y';

  fflush(stdin);
  system("clear");
  printf("\n Bem vindo ao jogo da velha!");
  printf("\n I - Jogar");
  printf("\n Qualquer número - Sair \n");
  scanf("\n%d",&escolha_menu);
  if(escolha_menu==1){
    do{

        fflush(stdin);
        system("clear");
        printf("\n Escolha seu adversario: ");
        printf("\n I- Computador");
        printf("\n II- Jogador \n");

        scanf("\n%c",&escolha_tipo);
        escolha_tipo = toupper(escolha_tipo);

        switch(escolha_tipo){
        case 'I':
            saida='Q';
            return 1;
            break;

        case 'II':
            saida='Q';
            return 2;
            break;

        default:
            printf("Opção inválida");
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

        fflush(stdin);
        system("clear");
        printf("\n Escolha a dificuldade");
        printf("\n I - Básico");
        printf("\n II - Intermediário");
        printf("\n III - Avançado\n");
        scanf("\n%c",&escolha_dif);
        escolha_dif = toupper(escolha_dif);

        switch (escolha_dif){
        case 'I':
            return 1;
            saida_dif = 1;
        break;

        case 'II':
            return 2;
            saida_dif = 1;
        break;

        case 'III':
            return 3;
            saida_dif = 1;
        break;

        default:
            printf("\tOpção inválida!");

               }

        }while(saida_dif !=1);
}

/*INICIALIZA_VELHA*/

void inicializa_velha(){ //zera as casas da velha
  for (j = 0; j < 3; j++) {
    for (i = 0; i < 3; i++) {
      velha[i][j] = ' ';
    }
  }

}


/*ESCOLHA_SIMB*/

 void escolha_simb(char *jog1, char *jog2){
    int saida_simb= 0;

    do{
        fflush(stdin);
        system("clear");
        printf("Escolha seu símbolo: 'X' ou 'O':\n");
        scanf("%c",jog1);
        *jog1 = toupper(*jog1);
        if (*jog1 == 'X') {
            *jog2 = 'O';
            saida_simb = 1;
        }else if (*jog1 == 'O') {
            *jog2 = 'X';
            saida_simb = 1;
        }else{
            printf("\tOpção Inválida!\n");
    }

 }while (saida_simb !=1);

 }

/*JOGADAS_PVP*/

void jogadas_pvp(char *simb1, char *simb2){
    int l = 0;
    int i = 0;
    int retorno_val;
    int vez = 0;
    int jogadas = 0;
    int verifica1 = 0;
    int verifica2 = 0;
    int nmr_partida = 1;
    char escolha;
    char saida;
    int erro;
    grava_arquivo();


    do{
    fflush(stdin);
    system("clear");
    printf(" \t      1   2   3 \n\n");
    printf("\t 1    %c | %c | %c \n",velha[0][0], velha[0][1], velha[0][2]);
    printf("\t     ---=---=--- \n");
    printf("\t 2    %c | %c | %c \n",velha[1][0], velha[1][1], velha[1][2]);
    printf("\t     ---=---=--- \n");
    printf("\t 3    %c | %c | %c \n",velha[2][0], velha[2][1], velha[2][2]);
    fflush(stdin);
    printf("\nInsira a linha desejada: ");
    scanf("%d",&i);
    printf("\nInsira a coluna desejada: ");
    scanf("%d",&l);



       if(vez%2==0){
        jog = *simb1;
        i = i-1;
        l = l-1;
        retorno_val = jogada_usuario(i,l,jog);
            if(retorno_val == 0){
              verifica1 = verifica_ganhador(jog);
              if (verifica1 == 1) {
                fflush(stdin);
                system("clear");
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

                erro = grava_binario('b',Jogo);
                printf("%d",erro);
                break;
              }
                jogadas++;
                vez++;

            }else if(retorno_val == 1){
                printf("\tPosição inválida!\n");
            }else{
                printf("\tPosição já ocupada!\n");
            }
       }else{
        jog = *simb2;
        i = i-1;
        l = l-1;
        retorno_val = jogada_usuario(i,l,jog);
             if(retorno_val == 0){
               verifica2 = verifica_ganhador(jog);
               if (verifica2 == 1) {
                    fflush(stdin);
                 system("clear");
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
                erro = grava_binario('b',Jogo);
                printf("%d",erro);

                 break;
               }
                jogadas++;
                vez++;

            }else if(retorno_val == 1){
                printf("\tPosição inválida!\n");
            }else{
                printf("\tPosição já ocupada!\n");
            }
       }

    }while(jogadas < 9);

    if (verifica1 == 0 && verifica2 == 0) {
      system("clear");
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
                    }
                    }
       erro = grava_binario('b',Jogo);
       printf("%d",erro);

    }
    jogar_novamente();
}
/*JOGADAS_PVE*/

void jogadas_pve(
  char *simb1, 
  char *simb2, 
  int dif
){
    int l = 0;
    int i = 0;
    int retorno_val;
    int vez = 0;
    int jogadas = 0;
    int verifica1 = 0;
    int verifica2 = 0;
    int nivel = 0;
    nivel = dif;

    do{
    fflush(stdin);
    system("clear");
    printf(" \t      1   2   3 \n\n");
    printf("\t 1    %c | %c | %c \n",velha[0][0], velha[0][1], velha[0][2]);
    printf("\t     ---=---=--- \n");
    printf("\t 2    %c | %c | %c \n",velha[1][0], velha[1][1], velha[1][2]);
    printf("\t     ---=---=--- \n");
    printf("\t 3    %c | %c | %c \n",velha[2][0], velha[2][1], velha[2][2]);




       if(vez%2==0){
         fflush(stdin);
         printf("\nInsira a linha desejada: ");
         scanf("%d",&i);
         printf("\nInsira a coluna desejada: ");
         scanf("%d",&l);
        jog = *simb1;
        i = i-1;
        l = l-1;
        retorno_val = jogada_usuario(i,l,jog);
            if(retorno_val == 0){
              verifica1 = verifica_ganhador(jog);
              if (verifica1 == 1) {
                system("clear");
                printf(" \t      1   2   3 \n\n");
                printf("\t 1    %c | %c | %c \n",velha[0][0], velha[0][1], velha[0][2]);
                printf("\t     ---=---=--- \n");
                printf("\t 2    %c | %c | %c \n",velha[1][0], velha[1][1], velha[1][2]);
                printf("\t     ---=---=--- \n");
                printf("\t 3    %c | %c | %c \n",velha[2][0], velha[2][1], velha[2][2]);
                printf("\n\tParabéns %c você venceu! \n",jog);
                break;
              }
                jogadas++;
                vez++;

            }else if(retorno_val == 1){
                printf("\tPosição inválida!\n");
            }else{
                printf("\tPosição já ocupada!\n");
            }
       }else if(vez%2==1){
        jog = *simb2;
        jogada_computador(jog, nivel);
               verifica2 = verifica_ganhador(jog);
               if (verifica2 == 1) {
                 system("clear");
                 printf(" \t      1   2   3 \n\n");
                 printf("\t 1    %c | %c | %c \n",velha[0][0], velha[0][1], velha[0][2]);
                 printf("\t     ---=---=--- \n");
                 printf("\t 2    %c | %c | %c \n",velha[1][0], velha[1][1], velha[1][2]);
                 printf("\t     ---=---=--- \n");
                 printf("\t 3    %c | %c | %c \n",velha[2][0], velha[2][1], velha[2][2]);
                 printf("\n\tVocê foi obliterado! GAME OVER! HAHAHAHA!! \n");
                 break;
               }
                jogadas++;
                vez++;
       }

    }while(jogadas < 9);


    if (verifica1 == 0 && verifica2 == 0) { //se nem o primeiro e nem o segundo jogador venceram, entao houve empate
      system("clear");
      printf(" \t      1   2   3 \n\n");
      printf("\t 1    %c | %c | %c \n",velha[0][0], velha[0][1], velha[0][2]);
      printf("\t     ---=---=--- \n");
      printf("\t 2    %c | %c | %c \n",velha[1][0], velha[1][1], velha[1][2]);
      printf("\t     ---=---=--- \n");
      printf("\t 3    %c | %c | %c \n",velha[2][0], velha[2][1], velha[2][2]);
      printf("\n\t# Deu VELHA!! #\n");
      printf("\n\t## QUE PENA NAO É MESMO?? ##\n");
    }
    jogar_novamente();
}

/*JOGADA_USUARIO*/

int jogada_usuario(int lin, int col, char jog){

    if(lin < 0 || col < 0 || lin > 2 || col > 2){ // verifica se o jogador mandou um valor possivel
        return 1;
    }else if(velha[lin][col] != ' '){ //verifica se a casa esta disponivel para jogadas
        return 2;
    }else{
        velha[lin][col] = jog; //se jogar cumpriu os requisitos de jogada entao preenche a casa
        return 0;

    }



}

/*VERIFICA_GANHADOR*/

int verifica_ganhador(char jog){

  // verifica todas as possiveis vitorias em um jogo
  if (velha[0][0] == jog && velha[0][1] == jog && velha[0][2] == jog) {
    return 1;
  }else if (velha[1][0] == jog && velha[1][1] == jog && velha[1][2] == jog) {
    return 1;
  }else if (velha[2][0] == jog && velha[2][1] == jog && velha[2][2] == jog) {
    return 1;
  }else if (velha[0][0] == jog && velha[1][0] == jog && velha[2][0] == jog) {
    return 1;
  }else if (velha[0][1] == jog && velha[1][1] == jog && velha[2][1] == jog) {
    return 1;
  }else if (velha[0][2] == jog && velha[1][2] == jog && velha[2][2] == jog) {
    return 1;
  }else if (velha[0][2] == jog && velha[1][1] == jog && velha[2][0] == jog) {
    return 1;
  }else if (velha[0][0] == jog && velha[1][1] == jog && velha[2][2] == jog) {
    return 1;
  }else{
    return 0;
  }
}

/*JOGADA_COMPUTADOR*/
void jogada_computador(
  char jog, 
  int nivel
){
  char simbpc;
  simbpc = jog;

  if (nivel == 1) {
    nivel_basico(simbpc); //faz jogada e printa na tela
    system("clear");
    printf(" \t      1   2   3 \n\n");
    printf("\t 1    %c | %c | %c \n",velha[0][0], velha[0][1], velha[0][2]);
    printf("\t     ---=---=--- \n");
    printf("\t 2    %c | %c | %c \n",velha[1][0], velha[1][1], velha[1][2]);
    printf("\t     ---=---=--- \n");
    printf("\t 3    %c | %c | %c \n",velha[2][0], velha[2][1], velha[2][2]);
  }else if (nivel == 2) {
    nivel_intermediario(simbpc); //faz jogada e printa na tela
    printf(" \t      1   2   3 \n\n");
    printf("\t 1    %c | %c | %c \n",velha[0][0], velha[0][1], velha[0][2]);
    printf("\t     ---=---=--- \n");
    printf("\t 2    %c | %c | %c \n",velha[1][0], velha[1][1], velha[1][2]);
    printf("\t     ---=---=--- \n");
    printf("\t 3    %c | %c | %c \n",velha[2][0], velha[2][1], velha[2][2]);
  }else if (nivel == 3) {
    nivel_avancado(simbpc); //faz jogada e printa na tela
    printf(" \t      1   2   3 \n\n");
    printf("\t 1    %c | %c | %c \n",velha[0][0], velha[0][1], velha[0][2]);
    printf("\t     ---=---=--- \n");
    printf("\t 2    %c | %c | %c \n",velha[1][0], velha[1][1], velha[1][2]);
    printf("\t     ---=---=--- \n");
    printf("\t 3    %c | %c | %c \n",velha[2][0], velha[2][1], velha[2][2]);
  }else{
    printf("\t##ERROR1337 NIVEL NAO DECIDIDO!!##\n");
  }

}

/*NIVEL_BASICO*/
void nivel_basico(
  char simbpc
  ){
  int lin;
  int col;
  char simbolo;
  simbolo = simbpc;

  srand((unsigned)time(NULL)); //nivel basico apenas joga randomicamente
  lin = rand()%3;
  srand((unsigned)time(NULL));
  col = rand()%3;
  if (velha[lin][col] == ' ') {
    velha[lin][col] = simbolo;
  }else{
    do {
      srand((unsigned)time(NULL));
      lin = rand()%3;
      srand((unsigned)time(NULL));
      col = rand()%3;
    } while(velha[lin][col] != ' ');
    velha[lin][col] = simbolo;
  }


}
/*NIVEL_INTERMEDIARIO*/
void nivel_intermediario(char simbpc){
  int lin;
  int col;
  char simbolo;
  char simbhu;
  int retdef;
  simbolo = simbpc;
  if (simbpc == 'X') {
    simbhu = 'O';
  }else if(simbpc == 'O'){
    simbhu = 'X';
  }

  retdef = defesas(simbhu, simbolo);
  if (retdef == 2) { //se defesa nao foi bem sucedida entao tenta random
    srand((unsigned)time(NULL));
    lin = rand()%3;
    srand((unsigned)time(NULL));
    col = rand()%3;
    if (velha[lin][col] == ' ') {
      velha[lin][col] = simbpc;
    }else{
      do {
        srand((unsigned)time(NULL));
        lin = rand()%3;
        srand((unsigned)time(NULL));
        col = rand()%3;
      } while(velha[lin][col] != ' ');
      velha[lin][col] = simbpc;
    }
  }


}
/*NIVEL_AVANCADO*/
void nivel_avancado(char simbpc){
  int lin;
  int col;
  int aux = 0;
  int retdef = 0;
  int retatq = 0;
  char simbolo;
  char simbhu;
  simbolo = simbpc;
  if (simbpc == 'X') { //se o simbolo do PC é um, player fica com o outro
    simbhu = 'O';
  }else if(simbpc == 'O'){
    simbhu = 'X';
  }
  do {
    if (velha[1][1] == ' ') { //se o meio esta livre entao joga nele
      velha[1][1] = simbpc;
      break;
    }else if(velha[0][0] == ' ' || velha[0][1] == ' ' || velha[0][2] == ' ' ||
             velha[1][0] == ' ' || velha[1][1] == ' ' || velha[1][2] == ' ' ||
             velha[2][0] == ' ' || velha[2][1] == ' ' || velha[2][2] == ' '){
      retatq = ataques(simbhu, simbolo); //se houver casas vazias, tenta ataque
        if (retatq == 1) { //se houve ataque bem sucedido entao termina o dowhile
          break;
        }else if (retatq == 2) { //caso nao haja lugar bom para ataque, entao tenta defender
          retdef = defesas(simbhu, simbolo);
          if (retdef == 1) { //se houve defesa bem sucedida entao termina o dowhile
            break;
          }else if(retdef == 2){
           if (velha[0][0] == simbhu && velha[1][1] == ' ' && velha[2][0] != simbhu && velha[0][2] != simbhu) {
              if (velha[2][2] == ' ') {
                velha[2][2] = simbpc;
                break;
              }
            }else if (velha[0][2] == simbhu && velha[1][1] == ' ' && velha[0][0] != simbhu && velha[2][2] != simbhu) {
              if (velha[2][0] == ' ') {
                velha[2][0] = simbpc;
                break;
              }
            }else if (velha[2][0] == simbhu && velha[1][1] == ' ' && velha[0][0] != simbhu && velha[2][2] != simbhu) {
              if (velha[0][2] == ' ') {
                velha[0][2] = simbpc;
                break;
              }
            }else if (velha[2][2] == simbhu && velha[1][1] == ' ' && velha[0][2] != simbhu && velha[2][0] != simbhu) {
              if (velha[0][0] == ' ') {
                velha[0][0] = simbpc;
                break;
              }
            }else if(velha[1][1] == simbpc){ //se o meio ja foi preenchido pelo pc
            if (velha[0][0] == simbhu && velha[2][2] == simbhu && velha[2][0] != simbhu && velha[0][2] != simbhu) { //defesa contra jogadas nas pontas
                if (velha[0][1] == ' ') {
                  velha[0][1] = simbpc;
                  break;
                }else if (velha[2][1] == ' ') {
                  velha[2][1] = simbpc;
                  break;
                }else if (velha[1][2] == ' ') {
                  velha[1][2] = simbpc;
                  break;
                }else if (velha[1][0] == ' ') {
                  velha[1][0] = simbpc;
                  break;
                }

            }else if (velha[2][0] == simbhu && velha[0][2] == simbhu && velha[0][0] != simbhu && velha[2][2] != simbhu) { //defesa contra jogadas nas pontas
                if (velha[0][1] == ' ') {
                  velha[0][1] = simbpc;
                  break;
                }else if (velha[2][1] == ' ') {
                  velha[2][1] = simbpc;
                  break;
                }else if (velha[1][2] == ' ') {
                  velha[1][2] = simbpc;
                  break;
                }else if (velha[1][0] == ' ') {
                  velha[1][0] = simbpc;
                  break;
                }

            }else{
                srand((unsigned)time(NULL));
                lin = rand()%3;
                srand((unsigned)time(NULL));
                col = rand()%3;
                if (velha[lin][col] == ' ') { //se houver casa vazia nos indices escolhidos randomicamente, entao joga
                  velha[lin][col] = simbpc;
                  aux = 1;
                }else{ //se nao houver casa vazia nos indices escolhidos randomicamente, entao randomiza novamente
                  do {
                    srand((unsigned)time(NULL));
                    lin = rand()%3;
                    srand((unsigned)time(NULL));
                    col = rand()%3;
                  } while(velha[lin][col] != ' ');
                  velha[lin][col] = simbpc;
                  aux = 1;
                }
            }
          }else if (velha[1][1] == simbhu) { //se o player jogou no meio, entao joga nos cantos
            if (velha[0][0] == ' ') {
              velha[0][0] = simbpc;
              aux = 1;
            }else if (velha[0][2] == ' ') {
              velha[0][2] = simbpc;
              aux = 1;
            }else if (velha[2][0] == ' ') {
              velha[2][0] = simbpc;
              aux = 1;
            }else if (velha[2][2] == ' ') {
              velha[2][2] = simbpc;
              aux = 1;
            }else{
                srand((unsigned)time(NULL));
                lin = rand()%3;
                srand((unsigned)time(NULL));
                col = rand()%3;
                if (velha[lin][col] == ' ') { //se houver casa vazia nos indices escolhidos randomicamente, entao joga
                  velha[lin][col] = simbpc;
                  aux = 1;
                }else{ //se nao houver casa vazia nos indices escolhidos randomicamente, entao randomiza novamente
                  do {
                    srand((unsigned)time(NULL));
                    lin = rand()%3;
                    srand((unsigned)time(NULL));
                    col = rand()%3;
                  } while(velha[lin][col] != ' ');
                  velha[lin][col] = simbpc;
                  aux = 1;
                }
            }
          }
        }


      }

      break;
    }
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
  if (velha[0][0] == simbhudef && velha[0][2] == simbhudef && velha[0][1] == ' ') {
    velha[0][1] = simbdef;
    aux = 1;
    ret = 1;
  }else if (velha[1][0] == simbhudef && velha[1][2] == simbhudef && velha[1][1] == ' ') {
    velha[1][1] = simbdef;
    aux = 1;
    ret = 1;
  }else if (velha[2][0] == simbhudef && velha[2][2] == simbhudef && velha[2][1] == ' ') {
    velha[2][1] = simbdef;
    aux = 1;
    ret = 1;
  }else if (velha[0][0] == simbhudef && velha[2][0] == simbhudef && velha[1][0] == ' ') {
    velha[1][0] = simbdef;
    aux = 1;
    ret = 1;
  }else if (velha[1][0] == simbhudef && velha[2][1] == simbhudef && velha[1][1] == ' ') {
    velha[1][1] = simbdef;
    aux = 1;
    ret = 1;
  }else if (velha[0][2] == simbhudef && velha[2][2] == simbhudef && velha[1][2] == ' ') {
    velha[1][2] = simbdef;
    aux = 1;
    ret = 1;
  }else if (velha[2][0] == simbhudef && velha[2][1] == simbhudef && velha[2][2] == ' ') {
    velha[2][2] = simbdef;
    aux = 1;
    ret = 1;
  }else if (velha[1][0] == simbhudef && velha[1][1] == simbhudef && velha[1][2] == ' ') {
    velha[1][2] = simbdef;
    aux = 1;
    ret = 1;
  }else if (velha[0][0] == simbhudef && velha[0][1] == simbhudef && velha[0][2] == ' ') {
    velha[0][2] = simbdef;
    aux = 1;
    ret = 1;
  }else if (velha[0][2] == simbhudef && velha[0][1] == simbhudef && velha[0][0] == ' ') {
    velha[0][0] = simbdef;
    aux = 1;
    ret = 1;
  }else if (velha[1][1] == simbhudef && velha[1][2] == simbhudef && velha[1][0] == ' ') {
    velha[1][0] = simbdef;
    aux = 1;
    ret = 1;
  }else if (velha[2][1] == simbhudef && velha[2][2] == simbhudef && velha[2][0] == ' ') {
    velha[2][0] = simbdef;
    aux = 1;
    ret = 1;
  }else if (velha[0][0] == simbhudef && velha[2][2] == simbhudef && velha[1][1] == ' ') {
    velha[1][1] = simbdef;
    aux = 1;
    ret = 1;
  }else if (velha[0][2] == simbhudef && velha[2][0] == simbhudef && velha[1][1] == ' ') {
    velha[1][1] = simbdef;
    aux = 1;
    ret = 1;
  }else if (velha[0][0] == simbhudef && velha[1][0] == simbhudef && velha[2][0] == ' ') {
    velha[2][0] = simbdef;
    aux = 1;
    ret = 1;
  }else if (velha[0][1] == simbhudef && velha[1][1] == simbhudef && velha[2][1] == ' ') {
    velha[2][1] = simbdef;
    aux = 1;
    ret = 1;
  }else if (velha[0][2] == simbhudef && velha[1][2] == simbhudef && velha[2][2] == ' ') {
    velha[2][2] = simbdef;
    aux = 1;
    ret = 1;
  }else if (velha[1][0] == simbhudef && velha[2][0] == simbhudef && velha[0][0] == ' ') {
    velha[0][0] = simbdef;
    aux = 1;
    ret = 1;
  }else if (velha[1][1] == simbhudef && velha[2][1] == simbhudef && velha[0][1] == ' ') {
    velha[0][1] = simbdef;
    aux = 1;
    ret = 1;
  }else if (velha[1][2] == simbhudef && velha[2][2] == simbhudef && velha[0][2] == ' ') {
    velha[0][2] = simbdef;
    aux = 1;
    ret = 1;
  }else if (velha[2][0] == simbhudef && velha[1][1] == simbhudef && velha[0][2] == ' ') {
    velha[0][2] = simbdef;
    aux = 1;
    ret = 1;
  }else if (velha[0][2] == simbhudef && velha[1][1] == simbhudef && velha[2][0] == ' ') {
    velha[2][0] = simbdef;
    aux = 1;
    ret = 1;
  }else if (velha[2][2] == simbhudef && velha[1][1] == simbhudef && velha[0][0] == ' ') {
    velha[0][0] = simbdef;
    aux = 1;
    ret = 1;
  }else if (velha[0][0] == simbhudef && velha[1][1] == simbhudef && velha[2][2] == ' ') {
    velha[2][2] = simbdef;
    aux = 1;
    ret = 1;
  }else{
    aux = 1;
    ret = 2;
  }
  } while(aux != 1);

  if (ret == 1) {
    return 1; //se retorna 1, entao houve defesa possivel
  }else if (ret == 2) {
    return 2; // se retorna 2, nao houve defesa possivel
  }
}
/*ATAQUES*/
int ataques(
  char simbhu,
  char simbolo
){
  int lin;
  int col;
  int aux = 0;
  int ret = 0;
  char simbataq;
  char simbhudef;
  simbataq = simbolo;
  simbhudef = simbhu;

  do { //verifica todas as possibilidades de ataque disponiveis
    if (velha[0][0] == simbataq && velha[0][2] == simbataq && velha[0][1] == ' ') {
      velha[0][1] = simbataq;
      aux = 1;
      ret = 1;
    }else if (velha[1][0] == simbataq && velha[1][2] == simbataq && velha[1][1] == ' ') {
      velha[1][1] = simbataq;
      aux = 1;
      ret = 1;
    }else if (velha[2][0] == simbataq && velha[2][2] == simbataq && velha[2][1] == ' ') {
      velha[2][1] = simbataq;
      aux = 1;
      ret = 1;
    }else if (velha[0][0] == simbataq && velha[2][0] == simbataq && velha[1][0] == ' ') {
      velha[1][0] = simbataq;
      aux = 1;
      ret = 1;
    }else if (velha[1][0] == simbataq && velha[2][1] == simbataq && velha[1][1] == ' ') {
      velha[1][1] = simbataq;
      aux = 1;
      ret = 1;
    }else if (velha[0][2] == simbataq && velha[2][2] == simbataq && velha[1][2] == ' ') {
      velha[1][2] = simbataq;
      aux = 1;
      ret = 1;
    }else if (velha[2][0] == simbataq && velha[2][1] == simbataq && velha[2][2] == ' ') {
      velha[2][2] = simbataq;
      aux = 1;
      ret = 1;
    }else if (velha[1][0] == simbataq && velha[1][1] == simbataq && velha[1][2] == ' ') {
      velha[1][2] = simbataq;
      aux = 1;
      ret = 1;
    }else if (velha[0][0] == simbataq && velha[0][1] == simbataq && velha[0][2] == ' ') {
      velha[0][2] = simbataq;
      aux = 1;
      ret = 1;
    }else if (velha[0][2] == simbataq && velha[0][1] == simbataq && velha[0][0] == ' ') {
      velha[0][0] = simbataq;
      aux = 1;
      ret = 1;
    }else if (velha[1][1] == simbataq && velha[1][2] == simbataq && velha[1][0] == ' ') {
      velha[1][0] = simbataq;
      aux = 1;
      ret = 1;
    }else if (velha[2][1] == simbataq && velha[2][2] == simbataq && velha[2][0] == ' ') {
      velha[2][0] = simbataq;
      aux = 1;
      ret = 1;
    }else if (velha[0][0] == simbataq && velha[2][2] == simbataq && velha[1][1] == ' ') {
      velha[1][1] = simbataq;
      aux = 1;
      ret = 1;
    }else if (velha[0][2] == simbataq && velha[2][0] == simbataq && velha[1][1] == ' ') {
      velha[1][1] = simbataq;
      aux = 1;
      ret = 1;
    }else if (velha[0][0] == simbataq && velha[1][0] == simbataq && velha[2][0] == ' ') {
      velha[2][0] = simbataq;
      aux = 1;
      ret = 1;
    }else if (velha[0][1] == simbataq && velha[1][1] == simbataq && velha[2][1] == ' ') {
      velha[2][1] = simbataq;
      aux = 1;
      ret = 1;
    }else if (velha[0][2] == simbataq && velha[1][2] == simbataq && velha[2][2] == ' ') {
      velha[2][2] = simbataq;
      aux = 1;
      ret = 1;
    }else if (velha[1][0] == simbataq && velha[2][0] == simbataq && velha[0][0] == ' ') {
      velha[0][0] = simbataq;
      aux = 1;
      ret = 1;
    }else if (velha[1][1] == simbataq && velha[2][1] == simbataq && velha[0][1] == ' ') {
      velha[0][1] = simbataq;
      aux = 1;
      ret = 1;
    }else if (velha[1][2] == simbataq && velha[2][2] == simbataq && velha[0][2] == ' ') {
      velha[0][2] = simbataq;
      aux = 1;
      ret = 1;
    }else if (velha[2][0] == simbataq && velha[1][1] == simbataq && velha[0][2] == ' ') {
      velha[0][2] = simbataq;
      aux = 1;
      ret = 1;
    }else if (velha[0][2] == simbataq && velha[1][1] == simbataq && velha[2][0] == ' ') {
      velha[2][0] = simbataq;
      aux = 1;
      ret = 1;
    }else if (velha[2][2] == simbataq && velha[1][1] == simbataq && velha[0][0] == ' ') {
      velha[0][0] = simbataq;
      aux = 1;
      ret = 1;
    }else if (velha[0][0] == simbataq && velha[1][1] == simbataq && velha[2][2] == ' ') {
      velha[2][2] = simbataq;
      aux = 1;
      ret = 1;
    }else{
      aux = 1;
      ret = 2;
      }
  } while(aux != 1);

  if (ret == 1) {
    return 1; // se houve ataques bem sucedidos, entao retorna 1
  }else if (ret == 2) {
    return 2; // se nao houve ataques bem sucedidos, entao retorna 2
  }
}


/*JOGAR_NOVAMENTE*/
void jogar_novamente(){
  char opcao;
  int saida;

  do {
  fflush(stdin);
  printf("\n Você deseja jogar novamente? S/N: ");
  printf("L - para ver jogadas\n ");
  printf("E - Caso deseje sair.\n");
  fflush(stdin);
  scanf("%c",&opcao);
  opcao = toupper(opcao);
  switch (opcao) {
    case 'S':
      main();
      saida = 1;
      break;

    case 'N':
      system("clear");
      printf("\n\tObrigado por jogar!!\n");
      printf("\n\tJogo desenvolvido por Erick Rampim e Yuri Nicolaiko.\n");
      printf("\n\t*toca-musica-dos-creditos*\n");
      saida = 1;
      break;

    case 'L':
    imprimir_partida();
    saida = 1;
    break;

    case 'E':
    saida = 1;
    break;
  }
} while(saida != 1);

}

void grava_arquivo(){

    FILE * arquivo_nome = fopen("nomes.txt","wa");

        fprintf(arquivo_nome,"%s;%c;%s;%c",nome_j1,simb1,nome_j2,simb2);

    fclose(arquivo_nome);
}

int grava_binario(char nome_arquivo,struct Velha Jogo){
    FILE * arquivo_binario;
    int x;
        if((arquivo_binario = fopen("arquivo_binario.dat","a+b"))== NULL){
           printf("Arquivo não pode ser aberto");
            return  0;
        }else{
            for(x=0;x<nmr_partida;x++){
            fwrite(&Jogo,sizeof(struct Velha),x,arquivo_binario);

            return 1;
            }
        }
    fclose(arquivo_binario);
}
 void imprimir_partida(){
    FILE * imprimir;
    int x;
    if((imprimir = fopen("arquivo_binario.dat","rb"))== NULL){
    printf("Arquivo não pode ser aberto");
    exit(0);

    }else{
    for(x=0;x<nmr_partida;x++){
    fread(&Jogo,sizeof(struct Velha),x,imprimir);

			 printf(" \t      1   2   3 \n\n");
      printf("\t 1    %c | %c | %c \n",Jogo.JogVelha[0][0], Jogo.JogVelha[0][1], Jogo.JogVelha[0][2]);
      printf("\t     ---=---=--- \n");
      printf("\t 2    %c | %c | %c \n",Jogo.JogVelha[1][0], Jogo.JogVelha[1][1], Jogo.JogVelha[1][2]);
      printf("\t     ---=---=--- \n");
      printf("\t 3    %c | %c | %c \n",Jogo.JogVelha[2][0], Jogo.JogVelha[2][1], Jogo.JogVelha[2][2]);
}

            }
  fclose(imprimir);
 }
