#include <stdio.h> // Entrada e saída padronizadas.
#include <ctype.h> // Manipulação de caracteres.
#include <stdlib.h> // alocação de memória e  necessário p/ as funções rand() e srand().
#include <time.h> // manipulação de datas e horários de modo padrão. random.
#include <locale.h> //necessário para usar setlocale.

typedef struct oldGameBoard{int partida; char hash[3][3], resultado;} Match;
int jogada_usuario(int lin,int col,char jog);
void jogada_computador(char jog,int nivel);
int menu();
void chooseSymbols();
void inicializa_velha();
int verifica_ganhador(char jog);

int chooseDifficulty();
void basicLevel(char computerSymbol);
void intermediateLevel(char computerSymbol);
void advancedLevel(char computerSymbol);
int secondMovement(char playerSymbol, char symbol);
int InitialMove(char playerSymbol, char symbol);
int traditionalMatch = 1;

void jogar_novamente();
void throwPlayerVsPlayer();
void throwPlayerVsComputer();

int i, j;
char oldGameBoard[3][3]; char jog;
Match Game;
char *simb1; char *simb2;
char playerNameOne[50]; char playerNameTwo[50];

/*MAIN*/
void main(){
  setlocale(LC_ALL, "Portuguese");
  int menureturn = 0, dif = 0;
  menureturn = menu();

  if(menureturn == 1){ setbuf(stdin,NULL); // limpar o buffer
    printf("Digite o seu nome: \n");
    gets (playerNameOne);
    dif = chooseDifficulty();
    chooseSymbols(&simb1,&simb2);
    inicializa_velha();
    throwPlayerVsComputer(&simb1,&simb2,dif);
  }
  else if (menureturn == 2) { setbuf(stdin,NULL); // limpar o buffer
    printf("\nDigite o nome do jogador 1: ");
    gets (playerNameOne);
    printf("\nDigite o nome do jogador 2: ");
    gets (playerNameTwo);
    chooseSymbols(&simb1,&simb2);
    inicializa_velha();
    throwPlayerVsPlayer(&simb1,&simb2);
  }
}
/*MENU*/
int menu(){
  setlocale(LC_ALL, "Portuguese");
  int escolha_menu = 0;
  char escolha_tipo ='Q'; char saida ='Y';

  fflush(stdin); //limpar o buffer
  system("cls"); // limpar console
  printf("\n Bem vindo ao jogo da velha!");
  printf("\n I - Jogar");
  printf("\n Qualquer número - Sair \n");
  scanf("\n%d",&escolha_menu);
  if(escolha_menu==1){
    do{ fflush(stdin); //limpar o buffer
        system("cls"); // limpar console
        printf("\n Escolha seu adversario: ");
        printf("\n I- Computador");
        printf("\n II- Jogador \n");
        scanf("\n%c",&escolha_tipo);
        escolha_tipo = toupper(escolha_tipo);

        switch(escolha_tipo){
        case '1': saida='Q'; return 1;
            break;
        case '2': saida='Q';return 2;
            break;
        default: printf("Opção inválida");
            break;
        }
    }while(saida != 'Q');
}else{}}
/*DIFICULDADE*/
int chooseDifficulty(){
  setlocale(LC_ALL, "Portuguese");
char choosingDifficulty;
int chosenDifficulty = 0;

    do{ fflush(stdin); // limpar o buffer
        system("cls"); // limpar console
        printf("\n Escolha a dificuldade");
        printf("\n I - Básico");
        printf("\n II - Intermediário");
        printf("\n III - Avançado\n");
        scanf("\n%c",&choosingDifficulty);
        choosingDifficulty = toupper(choosingDifficulty);

        switch (choosingDifficulty){
        case '1': return 1; chosenDifficulty = 1;
        break;
        case '2': return 2; chosenDifficulty = 1;
        break;
        case '3': return 3; chosenDifficulty = 1;
        break;
        default: printf("\tOpção inválida!");}}while(chosenDifficulty != 1);}
/*INICIALIZA_VELHA*/
void inicializa_velha(){ //zera as casas da velha
setlocale(LC_ALL, "Portuguese");
  for (j = 0; j < 3; j++) { for (i = 0; i < 3; i++) { oldGameBoard[i][j] = ' '; } } }
/*chooseSymbols*/
 void chooseSymbols(char *jog1, char *jog2){
    int saida_simb= 0;
    do{ fflush(stdin); // limpar o buffer
        system("cls"); // limpar console
        printf("Escolha seu símbolo: 'X' ou 'O':\n");
        scanf("%c",jog1);
        *jog1 = toupper(*jog1);
        if (*jog1 == 'X') {*jog2 = 'O';saida_simb = 1;} // se o jogador 1 for X, logo jogador 2 sera O;
        else if (*jog1 == 'O') {*jog2 = 'X';saida_simb = 1;} // se não jogador 1 O, e jogador 2 X;
        else{printf("\tOpção Inválida!\n");}// se nem uma opção for validade emitir erro de opção invalida
 }while (saida_simb !=1);}
/*throwPlayerVsPlayer*/
void throwPlayerVsPlayer(char *simb1, char *simb2){
    int l = 0, i = 0, returnValue, turn = 0, throw = 0, checkFirst = 0, checkSegund = 0, traditionalMatch = 1;
    char escolha; char saida;
    do{ fflush(stdin); // limpar o buffer
    system("cls");
    printf(" \t      1   2   3 \n\n");
    printf("\t 1    %c | %c | %c \n",oldGameBoard[0][0], oldGameBoard[0][1], oldGameBoard[0][2]);
    printf("\t     ---=---=--- \n");
    printf("\t 2    %c | %c | %c \n",oldGameBoard[1][0], oldGameBoard[1][1], oldGameBoard[1][2]);
    printf("\t     ---=---=--- \n");
    printf("\t 3    %c | %c | %c \n",oldGameBoard[2][0], oldGameBoard[2][1], oldGameBoard[2][2]);
    fflush(stdin); // limpar o buffer
    printf("\nInsira a linha desejada: ");
    scanf("%d",&i);
    printf("\nInsira a coluna desejada: ");
    scanf("%d",&l);

       if(turn%2==0){jog = *simb1;i = i-1;l = l-1;
        returnValue = jogada_usuario(i,l,jog);
            if(returnValue == 0){ checkFirst = verifica_ganhador(jog);
              if (checkFirst == 1) {
                fflush(stdin); // // limpar o buffer
                system("cls");
                printf(" \t      1   2   3 \n\n");
                printf("\t 1    %c | %c | %c \n",oldGameBoard[0][0], oldGameBoard[0][1], oldGameBoard[0][2]);
                printf("\t     ---=---=--- \n");
                printf("\t 2    %c | %c | %c \n",oldGameBoard[1][0], oldGameBoard[1][1], oldGameBoard[1][2]);
                printf("\t     ---=---=--- \n");
                printf("\t 3    %c | %c | %c \n",oldGameBoard[2][0], oldGameBoard[2][1], oldGameBoard[2][2]);
                fflush(stdin); // limpar o buffer
                printf("\n\tParabéns %c você venceu! \n",jog);
                Game.partida = traditionalMatch;
                Game.resultado = jog;
                for (j = 0; j < 3; j++) { for (i = 0; i < 3; i++) { Game.hash[i][j] = oldGameBoard[i][j];}}
                break;
              } throw++; turn++;
            }else if(returnValue == 1){
                printf("\tPosição inválida!\n");
            }
            else{printf("\tPosição já ocupada!\n");}
       }
       else{jog = *simb2; i = i-1; l = l-1;
        returnValue = jogada_usuario(i,l,jog);
             if(returnValue == 0){ checkSegund = verifica_ganhador(jog);
               if (checkSegund == 1) {
                 fflush(stdin); // limpar o buffer
                 system("cls");
                 printf(" \t      1   2   3 \n\n");
                 printf("\t 1    %c | %c | %c \n",oldGameBoard[0][0], oldGameBoard[0][1], oldGameBoard[0][2]);
                 printf("\t     ---=---=--- \n");
                 printf("\t 2    %c | %c | %c \n",oldGameBoard[1][0], oldGameBoard[1][1], oldGameBoard[1][2]);
                 printf("\t     ---=---=--- \n");
                 printf("\t 3    %c | %c | %c \n",oldGameBoard[2][0], oldGameBoard[2][1], oldGameBoard[2][2]);
                 fflush(stdin); // limpar o buffer
                 printf("\n\tParabéns %c você venceu! \n",jog);
                Game.partida = traditionalMatch;
                Game.resultado = jog;
                for (j = 0; j < 3; j++) {
                    for (i = 0; i < 3; i++) {
                        Game.hash[i][j] = oldGameBoard[i][j];
                    }
                    }
                 break;
               }
                throw++;
                turn++;}
            else if(returnValue == 1){printf("\tPosição inválida!\n");}
            else{printf("\tPosição já ocupada!\n");}
       }
    }while(throw < 9);
    if (checkFirst == 0 && checkSegund == 0) {
      system("cls");
      printf(" \t      1   2   3 \n\n");
      printf("\t 1    %c | %c | %c \n",oldGameBoard[0][0], oldGameBoard[0][1], oldGameBoard[0][2]);
      printf("\t     ---=---=--- \n");
      printf("\t 2    %c | %c | %c \n",oldGameBoard[1][0], oldGameBoard[1][1], oldGameBoard[1][2]);
      printf("\t     ---=---=--- \n");
      printf("\t 3    %c | %c | %c \n",oldGameBoard[2][0], oldGameBoard[2][1], oldGameBoard[2][2]);
      printf("\n\t# Deu Velha!! #\n");
        Game.partida = traditionalMatch;
        Game.resultado = 'V';
        for (j = 0; j < 3; j++) {
            for (i = 0; i < 3; i++) {
                    Game.hash[i][j] = oldGameBoard[i][j];
                    }}}
    jogar_novamente();}
/*throw_PlayerXComputer*/
void throwPlayerVsComputer(char *simb1,char *simb2,int dif){
    int l = 0, i = 0, returnValue, turn = 0, throw = 0, checkFirst = 0, checkSegund = 0, nivel = 0;
    nivel = dif;
    do{ fflush(stdin); // limpar o buffer
    system("cls");
    printf(" \t      1   2   3 \n\n");
    printf("\t 1    %c | %c | %c \n",oldGameBoard[0][0], oldGameBoard[0][1], oldGameBoard[0][2]);
    printf("\t     ---=---=--- \n");
    printf("\t 2    %c | %c | %c \n",oldGameBoard[1][0], oldGameBoard[1][1], oldGameBoard[1][2]);
    printf("\t     ---=---=--- \n");
    printf("\t 3    %c | %c | %c \n",oldGameBoard[2][0], oldGameBoard[2][1], oldGameBoard[2][2]);
       if(turn%2==0){
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
              checkFirst = verifica_ganhador(jog);
              if (checkFirst == 1) {
                system("cls");
                printf(" \t      1   2   3 \n\n");
                printf("\t 1    %c | %c | %c \n",oldGameBoard[0][0], oldGameBoard[0][1], oldGameBoard[0][2]);
                printf("\t     ---=---=--- \n");
                printf("\t 2    %c | %c | %c \n",oldGameBoard[1][0], oldGameBoard[1][1], oldGameBoard[1][2]);
                printf("\t     ---=---=--- \n");
                printf("\t 3    %c | %c | %c \n",oldGameBoard[2][0], oldGameBoard[2][1], oldGameBoard[2][2]);
                printf("\n\tParabéns %c você venceu! \n",jog);
                break;
                }throw++;turn++;}
            else if(returnValue == 1){ printf("\tPosição inválida!\n");}
            else{printf("\tPosição já ocupada!\n");}}
            else if(turn%2==1){ jog = *simb2;
        jogada_computador(jog, nivel);
               checkSegund = verifica_ganhador(jog);
               if (checkSegund == 1) {
                 system("cls");
                 printf(" \t      1   2   3 \n\n");
                 printf("\t 1    %c | %c | %c \n",oldGameBoard[0][0], oldGameBoard[0][1], oldGameBoard[0][2]);
                 printf("\t     ---=---=--- \n");
                 printf("\t 2    %c | %c | %c \n",oldGameBoard[1][0], oldGameBoard[1][1], oldGameBoard[1][2]);
                 printf("\t     ---=---=--- \n");
                 printf("\t 3    %c | %c | %c \n",oldGameBoard[2][0], oldGameBoard[2][1], oldGameBoard[2][2]);
                 printf("\n\tVocê foi perdeu! GAME OVER! \n");
                 break;
               }throw++;turn++;
       }
    }while(throw < 9);
    if (checkFirst == 0 && checkSegund == 0) { //se nem o primeiro e nem o segundo jogador venceram, entao houve empate
      system("cls");
      printf(" \t      1   2   3 \n\n");
      printf("\t 1    %c | %c | %c \n",oldGameBoard[0][0], oldGameBoard[0][1], oldGameBoard[0][2]);
      printf("\t     ---=---=--- \n");
      printf("\t 2    %c | %c | %c \n",oldGameBoard[1][0], oldGameBoard[1][1], oldGameBoard[1][2]);
      printf("\t     ---=---=--- \n");
      printf("\t 3    %c | %c | %c \n",oldGameBoard[2][0], oldGameBoard[2][1], oldGameBoard[2][2]);
      printf("\n\t# Deu Velha!! #\n");
    }
    jogar_novamente();
}
/* JOGADA_USUARIO */
int jogada_usuario(int lin, int col, char jog){
    if(lin < 0 || col < 0 || lin > 2 || col > 2){ return 1;} // verifica se o jogador mandou um valor possivel
    else if(oldGameBoard[lin][col] != ' '){ return 2;} //verifica se a casa esta dispolevel para throw
    else{ oldGameBoard[lin][col] = jog; return 0;}} //se jogar cumpriu os requisitos de jogada entao preenche a casa
/* VERIFICA_GANHADOR */
  int verifica_ganhador(char jog){ // verifica todas as possiveis vitorias em um jogo
  if (oldGameBoard[0][0] == jog && oldGameBoard[0][1] == jog && oldGameBoard[0][2] == jog) {return 1;}
  else if (oldGameBoard[1][0] == jog && oldGameBoard[1][1] == jog && oldGameBoard[1][2] == jog) {return 1;}
  else if (oldGameBoard[2][0] == jog && oldGameBoard[2][1] == jog && oldGameBoard[2][2] == jog) {return 1;}
  else if (oldGameBoard[0][0] == jog && oldGameBoard[1][0] == jog && oldGameBoard[2][0] == jog) {return 1;}
  else if (oldGameBoard[0][1] == jog && oldGameBoard[1][1] == jog && oldGameBoard[2][1] == jog) {return 1;}
  else if (oldGameBoard[0][2] == jog && oldGameBoard[1][2] == jog && oldGameBoard[2][2] == jog) {return 1;}
  else if (oldGameBoard[0][2] == jog && oldGameBoard[1][1] == jog && oldGameBoard[2][0] == jog) {return 1;}
  else if (oldGameBoard[0][0] == jog && oldGameBoard[1][1] == jog && oldGameBoard[2][2] == jog) {return 1;}
  else{return 0;}}
/*JOGADA_COMPUTADOR*/
void jogada_computador(char jog, int nivel){
  char computerSymbol;
  computerSymbol = jog;
  if (nivel == 1) {
    basicLevel(computerSymbol); //faz jogada e mostra no console.
    system("cls");
    printf(" \t      1   2   3 \n\n");
    printf("\t 1    %c | %c | %c \n",oldGameBoard[0][0], oldGameBoard[0][1], oldGameBoard[0][2]);
    printf("\t     ---=---=--- \n");
    printf("\t 2    %c | %c | %c \n",oldGameBoard[1][0], oldGameBoard[1][1], oldGameBoard[1][2]);
    printf("\t     ---=---=--- \n");
    printf("\t 3    %c | %c | %c \n",oldGameBoard[2][0], oldGameBoard[2][1], oldGameBoard[2][2]);
  }else if (nivel == 2) {
    intermediateLevel(computerSymbol); //faz jogada e mostra no console.
    printf(" \t      1   2   3 \n\n");
    printf("\t 1    %c | %c | %c \n",oldGameBoard[0][0], oldGameBoard[0][1], oldGameBoard[0][2]);
    printf("\t     ---=---=--- \n");
    printf("\t 2    %c | %c | %c \n",oldGameBoard[1][0], oldGameBoard[1][1], oldGameBoard[1][2]);
    printf("\t     ---=---=--- \n");
    printf("\t 3    %c | %c | %c \n",oldGameBoard[2][0], oldGameBoard[2][1], oldGameBoard[2][2]);
  }else if (nivel == 3) {
    advancedLevel(computerSymbol); //faz jogada e mostra no console.
    printf(" \t      1   2   3 \n\n");
    printf("\t 1    %c | %c | %c \n",oldGameBoard[0][0], oldGameBoard[0][1], oldGameBoard[0][2]);
    printf("\t     ---=---=--- \n");
    printf("\t 2    %c | %c | %c \n",oldGameBoard[1][0], oldGameBoard[1][1], oldGameBoard[1][2]);
    printf("\t     ---=---=--- \n");
    printf("\t 3    %c | %c | %c \n",oldGameBoard[2][0], oldGameBoard[2][1], oldGameBoard[2][2]);
  }else{
    printf("\tErro nivel não decidido!!\n");
  }
}
/*Nivel Basico*/
void basicLevel(char computerSymbol){
  int lin, col;
  char symbol;
  symbol = computerSymbol;
  srand((unsigned)time(NULL)); lin = rand()%3; //level basico apenas joga randomicamente
  srand((unsigned)time(NULL)); col = rand()%3; // valores aleatórios
  if (oldGameBoard[lin][col] == ' ') {oldGameBoard[lin][col] = symbol;}
  else{do {
      srand((unsigned)time(NULL));lin = rand()%3; // valores aleatórios para as linhas
      srand((unsigned)time(NULL));col = rand()%3;// valores aleatórios para coluna
    } while(oldGameBoard[lin][col] != ' '); oldGameBoard[lin][col] = symbol; } }
/*intermediateLevel*/
void intermediateLevel(char computerSymbol){
  int lin, col, returnOfTheSecondMovement; //returnOfTheSecondMovement
  char symbol; char playerSymbol;
  symbol = computerSymbol;
  if (computerSymbol == 'X') {playerSymbol = 'O';}
  else if(computerSymbol == 'O'){playerSymbol = 'X';}

  returnOfTheSecondMovement = secondMovement(playerSymbol, symbol);
  if (returnOfTheSecondMovement == 2) { //se movimento(s) nao foi bem sucedida entao tenta random
    srand((unsigned)time(NULL)); lin = rand()%3;
    srand((unsigned)time(NULL)); col = rand()%3;
    if (oldGameBoard[lin][col] == ' ') {oldGameBoard[lin][col] = computerSymbol;}
    else{
      do {srand((unsigned)time(NULL)); lin = rand()%3;
          srand((unsigned)time(NULL)); col = rand()%3; }
      while(oldGameBoard[lin][col] != ' '); oldGameBoard[lin][col] = computerSymbol;}}}
/*Advenced*/
void advancedLevel(char computerSymbol){
  int lin, col, assistance = 0, returnOfTheSecondMovement = 0, returnOfTheFirstMove = 0;
  char symbol; char playerSymbol;
  symbol = computerSymbol;
       if (computerSymbol == 'X') { playerSymbol = 'O';}//se o symbol do Computador é um ex: X, player fica com o outro ex: O
  else if (computerSymbol == 'O') { playerSymbol = 'X';}// se não o computador ficara com O, e o jogador ficara com
  do { if (oldGameBoard[1][1] == ' ') { oldGameBoard[1][1] = computerSymbol;break;} //se o meio esta livre entao joga nele
    else if(
             oldGameBoard[0][0] == ' ' || oldGameBoard[0][1] == ' ' || oldGameBoard[0][2] == ' ' ||
             oldGameBoard[1][0] == ' ' || oldGameBoard[1][1] == ' ' || oldGameBoard[1][2] == ' ' ||
             oldGameBoard[2][0] == ' ' || oldGameBoard[2][1] == ' ' || oldGameBoard[2][2] == ' '
             ){ returnOfTheFirstMove = InitialMove(playerSymbol, symbol); //se houver casas vazias, tenta movimento(s)
             if (returnOfTheFirstMove == 1) { break;} //se houve movimento(s) bem sucedido entao termina o lop
        else if (returnOfTheFirstMove == 2) { returnOfTheSecondMovement = secondMovement(playerSymbol, symbol);//caso nao haja lugar bom para movimento(s), entao tenta defender
             if (returnOfTheSecondMovement == 1) { //se houve movimento(s) bem sucedida entao termina o lop
            break;}
            else if(returnOfTheSecondMovement == 2){
                 if (oldGameBoard[0][0] == playerSymbol && oldGameBoard[1][1] == ' ' && oldGameBoard[2][0] != playerSymbol && oldGameBoard[0][2] != playerSymbol) {
                 if (oldGameBoard[2][2] == ' ') {oldGameBoard[2][2] = computerSymbol; break;}}
            else if (oldGameBoard[0][2] == playerSymbol && oldGameBoard[1][1] == ' ' && oldGameBoard[0][0] != playerSymbol && oldGameBoard[2][2] != playerSymbol) {
                 if (oldGameBoard[2][0] == ' ') {oldGameBoard[2][0] = computerSymbol;break;}}
            else if (oldGameBoard[2][0] == playerSymbol && oldGameBoard[1][1] == ' ' && oldGameBoard[0][0] != playerSymbol && oldGameBoard[2][2] != playerSymbol) {
                 if (oldGameBoard[0][2] == ' ') {oldGameBoard[0][2] = computerSymbol;break;}}
            else if (oldGameBoard[2][2] == playerSymbol && oldGameBoard[1][1] == ' ' && oldGameBoard[0][2] != playerSymbol && oldGameBoard[2][0] != playerSymbol) {
                 if (oldGameBoard[0][0] == ' ') { oldGameBoard[0][0] = computerSymbol;break;} }
            else if (oldGameBoard[1][1] == computerSymbol){ //se o meio ja foi preenchido pelo pc
                 if (oldGameBoard[0][0] == playerSymbol && oldGameBoard[2][2] == playerSymbol && oldGameBoard[2][0] != playerSymbol && oldGameBoard[0][2] != playerSymbol) { //movimento(s) contra throw nas pontas
                 if (oldGameBoard[0][1] == ' ') {oldGameBoard[0][1] = computerSymbol; break;}
            else if (oldGameBoard[2][1] == ' ') {oldGameBoard[2][1] = computerSymbol; break;}
            else if (oldGameBoard[1][2] == ' ') {oldGameBoard[1][2] = computerSymbol;break;}
            else if (oldGameBoard[1][0] == ' ') {oldGameBoard[1][0] = computerSymbol;break;}}
            else if (oldGameBoard[2][0] == playerSymbol && oldGameBoard[0][2] == playerSymbol && oldGameBoard[0][0] != playerSymbol && oldGameBoard[2][2] != playerSymbol) { //movimento(s) contra throw
                 if (oldGameBoard[0][1] == ' ') { oldGameBoard[0][1] = computerSymbol; break;}
            else if (oldGameBoard[2][1] == ' ') {oldGameBoard[2][1] = computerSymbol;break;}
            else if (oldGameBoard[1][2] == ' ') {oldGameBoard[1][2] = computerSymbol; break;}
            else if (oldGameBoard[1][0] == ' ') {oldGameBoard[1][0] = computerSymbol;break;}}
                else{ srand((unsigned)time(NULL)); lin = rand()%3; // valores aleatorios
                      srand((unsigned)time(NULL)); col = rand()%3; // valores aleatorios
                 if (oldGameBoard[lin][col] == ' ') {oldGameBoard[lin][col] = computerSymbol; assistance = 1;} //se houver casa vazia nos indices escolhidos randomicamente, entao joga
                else{ //se nao houver casa vazia nos indices escolhidos randomicamente, entao randomiza novamente
                  do {  srand((unsigned)time(NULL)); lin = rand()%3; // valores aleatorios
                        srand((unsigned)time(NULL)); col = rand()%3;} // valores aleatorios
                  while(oldGameBoard[lin][col] != ' '); oldGameBoard[lin][col] = computerSymbol; assistance = 1;}}}
            else if (oldGameBoard[1][1] == playerSymbol) { //se o player jogou no meio, entao joga nos cantos
                 if (oldGameBoard[0][0] == ' ') {oldGameBoard[0][0] = computerSymbol;assistance = 1;}
            else if (oldGameBoard[0][2] == ' ') {oldGameBoard[0][2] = computerSymbol; assistance = 1;}
            else if (oldGameBoard[2][0] == ' ') {oldGameBoard[2][0] = computerSymbol; assistance = 1; }
            else if (oldGameBoard[2][2] == ' ') {oldGameBoard[2][2] = computerSymbol;assistance = 1;}
            else{ srand((unsigned)time(NULL)); lin = rand()%3; // valores aleatorios
                  srand((unsigned)time(NULL)); col = rand()%3; // valores aleatorios
                 if (oldGameBoard[lin][col] == ' ') { oldGameBoard[lin][col] = computerSymbol; assistance = 1; } //se houver casa vazia nos indices escolhidos randomicamente, entao joga
                else{ //se nao houver casa vazia nos indices escolhidos randomicamente, entao randomiza novamente
                  do { srand((unsigned)time(NULL)); lin = rand()%3; // valores aleatorios
                       srand((unsigned)time(NULL)); col = rand()%3; // valores aleatorios
                  }
                  while(oldGameBoard[lin][col] != ' '); oldGameBoard[lin][col] = computerSymbol;assistance = 1;}}}}} break;}
  } while(assistance != 1); //se ja terminou jogada, entao 
}
/*secondMovement*/
int secondMovement(char playerSymbol, char symbol){
  int lin, col, assistance = 0, retorno = 0;
  char symbolSegund, playerSymbolSegund;
  symbolSegund = symbol;
  playerSymbolSegund = playerSymbol;
do { //verifica todas casas com possibilidades de fazer o segundo movimento
  if (oldGameBoard[0][0] == playerSymbolSegund && oldGameBoard[0][2] == playerSymbolSegund && oldGameBoard[0][1] == ' ') {oldGameBoard[0][1] = symbolSegund;assistance = 1;retorno = 1;}
  else if (oldGameBoard[1][0] == playerSymbolSegund && oldGameBoard[1][2] == playerSymbolSegund && oldGameBoard[1][1] == ' ') {oldGameBoard[1][1] = symbolSegund;assistance = 1;retorno = 1;}
  else if (oldGameBoard[2][0] == playerSymbolSegund && oldGameBoard[2][2] == playerSymbolSegund && oldGameBoard[2][1] == ' ') {oldGameBoard[2][1] = symbolSegund;assistance = 1;retorno = 1;}
  else if (oldGameBoard[0][0] == playerSymbolSegund && oldGameBoard[2][0] == playerSymbolSegund && oldGameBoard[1][0] == ' ') {oldGameBoard[1][0] = symbolSegund;assistance = 1;retorno = 1;}
  else if (oldGameBoard[1][0] == playerSymbolSegund && oldGameBoard[2][1] == playerSymbolSegund && oldGameBoard[1][1] == ' ') {oldGameBoard[1][1] = symbolSegund;assistance = 1;retorno = 1;}
  else if (oldGameBoard[0][2] == playerSymbolSegund && oldGameBoard[2][2] == playerSymbolSegund && oldGameBoard[1][2] == ' ') {oldGameBoard[1][2] = symbolSegund;assistance = 1;retorno = 1;}
  else if (oldGameBoard[2][0] == playerSymbolSegund && oldGameBoard[2][1] == playerSymbolSegund && oldGameBoard[2][2] == ' ') {oldGameBoard[2][2] = symbolSegund;assistance = 1;retorno = 1;}
  else if (oldGameBoard[1][0] == playerSymbolSegund && oldGameBoard[1][1] == playerSymbolSegund && oldGameBoard[1][2] == ' ') {oldGameBoard[1][2] = symbolSegund;assistance = 1;retorno = 1;}
  else if (oldGameBoard[0][0] == playerSymbolSegund && oldGameBoard[0][1] == playerSymbolSegund && oldGameBoard[0][2] == ' ') {oldGameBoard[0][2] = symbolSegund;assistance = 1;retorno = 1;}
  else if (oldGameBoard[0][2] == playerSymbolSegund && oldGameBoard[0][1] == playerSymbolSegund && oldGameBoard[0][0] == ' ') {oldGameBoard[0][0] = symbolSegund;assistance = 1;retorno = 1;}
  else if (oldGameBoard[1][1] == playerSymbolSegund && oldGameBoard[1][2] == playerSymbolSegund && oldGameBoard[1][0] == ' ') {oldGameBoard[1][0] = symbolSegund;assistance = 1;retorno = 1;}
  else if (oldGameBoard[2][1] == playerSymbolSegund && oldGameBoard[2][2] == playerSymbolSegund && oldGameBoard[2][0] == ' ') {oldGameBoard[2][0] = symbolSegund;assistance = 1;retorno = 1;}
  else if (oldGameBoard[0][0] == playerSymbolSegund && oldGameBoard[2][2] == playerSymbolSegund && oldGameBoard[1][1] == ' ') {oldGameBoard[1][1] = symbolSegund;assistance = 1;retorno = 1;}
  else if (oldGameBoard[0][2] == playerSymbolSegund && oldGameBoard[2][0] == playerSymbolSegund && oldGameBoard[1][1] == ' ') {oldGameBoard[1][1] = symbolSegund;assistance = 1;retorno = 1;}
  else if (oldGameBoard[0][0] == playerSymbolSegund && oldGameBoard[1][0] == playerSymbolSegund && oldGameBoard[2][0] == ' ') {oldGameBoard[2][0] = symbolSegund;assistance = 1;retorno = 1;}
  else if (oldGameBoard[0][1] == playerSymbolSegund && oldGameBoard[1][1] == playerSymbolSegund && oldGameBoard[2][1] == ' ') {oldGameBoard[2][1] = symbolSegund;assistance = 1;retorno = 1;}
  else if (oldGameBoard[0][2] == playerSymbolSegund && oldGameBoard[1][2] == playerSymbolSegund && oldGameBoard[2][2] == ' ') {oldGameBoard[2][2] = symbolSegund;assistance = 1;retorno = 1;}
  else if (oldGameBoard[1][0] == playerSymbolSegund && oldGameBoard[2][0] == playerSymbolSegund && oldGameBoard[0][0] == ' ') {oldGameBoard[0][0] = symbolSegund;assistance = 1;retorno = 1;}
  else if (oldGameBoard[1][1] == playerSymbolSegund && oldGameBoard[2][1] == playerSymbolSegund && oldGameBoard[0][1] == ' ') {oldGameBoard[0][1] = symbolSegund;assistance = 1;retorno = 1;}
  else if (oldGameBoard[1][2] == playerSymbolSegund && oldGameBoard[2][2] == playerSymbolSegund && oldGameBoard[0][2] == ' ') {oldGameBoard[0][2] = symbolSegund;assistance = 1;retorno = 1;}
  else if (oldGameBoard[2][0] == playerSymbolSegund && oldGameBoard[1][1] == playerSymbolSegund && oldGameBoard[0][2] == ' ') {oldGameBoard[0][2] = symbolSegund;assistance = 1;retorno = 1;}
  else if (oldGameBoard[0][2] == playerSymbolSegund && oldGameBoard[1][1] == playerSymbolSegund && oldGameBoard[2][0] == ' ') { oldGameBoard[2][0] = symbolSegund; assistance = 1; retorno = 1; }
  else if (oldGameBoard[2][2] == playerSymbolSegund && oldGameBoard[1][1] == playerSymbolSegund && oldGameBoard[0][0] == ' ') { oldGameBoard[0][0] = symbolSegund; assistance = 1; retorno = 1; }
  else if (oldGameBoard[0][0] == playerSymbolSegund && oldGameBoard[1][1] == playerSymbolSegund && oldGameBoard[2][2] == ' ') { oldGameBoard[2][2] = symbolSegund; assistance = 1; retorno = 1; }
  else{ assistance = 1;retorno = 2;}}
  while(assistance != 1);
  if (retorno == 1) {return 1; }//se retorna 1, então houve movimento(s) possivel
  else if (retorno == 2) {return 2; }// se retorna 2, nao houve movimento(s) possivel
}
/*InitialMove*/
int InitialMove(char playerSymbol, char symbol){
  int lin, col, assistance = 0, retorno = 0;
  char InitialMove, playerSymbolSegund;
  InitialMove = symbol;
  playerSymbolSegund = playerSymbol;
  do { //verifica todas as possibilidades para o proximo movimento possivel disponiveis
    if (oldGameBoard[0][0] == InitialMove && oldGameBoard[0][2] == InitialMove && oldGameBoard[0][1] == ' ') {oldGameBoard[0][1] = InitialMove;assistance = 1; retorno = 1;}
    else if (oldGameBoard[1][0] == InitialMove && oldGameBoard[1][2] == InitialMove && oldGameBoard[1][1] == ' ') {oldGameBoard[1][1] = InitialMove;assistance = 1;retorno = 1;}
    else if (oldGameBoard[2][0] == InitialMove && oldGameBoard[2][2] == InitialMove && oldGameBoard[2][1] == ' ') {oldGameBoard[2][1] = InitialMove;assistance = 1;retorno = 1;}
    else if (oldGameBoard[0][0] == InitialMove && oldGameBoard[2][0] == InitialMove && oldGameBoard[1][0] == ' ') {oldGameBoard[1][0] = InitialMove;assistance = 1;retorno = 1;}
    else if (oldGameBoard[1][0] == InitialMove && oldGameBoard[2][1] == InitialMove && oldGameBoard[1][1] == ' ') {oldGameBoard[1][1] = InitialMove;assistance = 1;retorno = 1;}
    else if (oldGameBoard[0][2] == InitialMove && oldGameBoard[2][2] == InitialMove && oldGameBoard[1][2] == ' ') {oldGameBoard[1][2] = InitialMove;assistance = 1;retorno = 1;}
    else if (oldGameBoard[2][0] == InitialMove && oldGameBoard[2][1] == InitialMove && oldGameBoard[2][2] == ' ') {oldGameBoard[2][2] = InitialMove;assistance = 1;retorno = 1;}
    else if (oldGameBoard[1][0] == InitialMove && oldGameBoard[1][1] == InitialMove && oldGameBoard[1][2] == ' ') {oldGameBoard[1][2] = InitialMove;assistance = 1;retorno = 1;}
    else if (oldGameBoard[0][0] == InitialMove && oldGameBoard[0][1] == InitialMove && oldGameBoard[0][2] == ' ') {oldGameBoard[0][2] = InitialMove;assistance = 1;retorno = 1;}
    else if (oldGameBoard[0][2] == InitialMove && oldGameBoard[0][1] == InitialMove && oldGameBoard[0][0] == ' ') {oldGameBoard[0][0] = InitialMove;assistance = 1;retorno = 1;}
    else if (oldGameBoard[1][1] == InitialMove && oldGameBoard[1][2] == InitialMove && oldGameBoard[1][0] == ' ') {oldGameBoard[1][0] = InitialMove;assistance = 1;retorno = 1;}
    else if (oldGameBoard[2][1] == InitialMove && oldGameBoard[2][2] == InitialMove && oldGameBoard[2][0] == ' ') {oldGameBoard[2][0] = InitialMove;assistance = 1;retorno = 1;}
    else if (oldGameBoard[0][0] == InitialMove && oldGameBoard[2][2] == InitialMove && oldGameBoard[1][1] == ' ') {oldGameBoard[1][1] = InitialMove;assistance = 1;retorno = 1;}
    else if (oldGameBoard[0][2] == InitialMove && oldGameBoard[2][0] == InitialMove && oldGameBoard[1][1] == ' ') {oldGameBoard[1][1] = InitialMove;assistance = 1;retorno = 1;}
    else if (oldGameBoard[0][0] == InitialMove && oldGameBoard[1][0] == InitialMove && oldGameBoard[2][0] == ' ') {oldGameBoard[2][0] = InitialMove;assistance = 1;retorno = 1;}
    else if (oldGameBoard[0][1] == InitialMove && oldGameBoard[1][1] == InitialMove && oldGameBoard[2][1] == ' ') {oldGameBoard[2][1] = InitialMove;assistance = 1;retorno = 1;}
    else if (oldGameBoard[0][2] == InitialMove && oldGameBoard[1][2] == InitialMove && oldGameBoard[2][2] == ' ') {oldGameBoard[2][2] = InitialMove;assistance = 1;retorno = 1;}
    else if (oldGameBoard[1][0] == InitialMove && oldGameBoard[2][0] == InitialMove && oldGameBoard[0][0] == ' ') {oldGameBoard[0][0] = InitialMove;assistance = 1;retorno = 1;}
    else if (oldGameBoard[1][1] == InitialMove && oldGameBoard[2][1] == InitialMove && oldGameBoard[0][1] == ' ') {oldGameBoard[0][1] = InitialMove;assistance = 1;retorno = 1;}
    else if (oldGameBoard[1][2] == InitialMove && oldGameBoard[2][2] == InitialMove && oldGameBoard[0][2] == ' ') {oldGameBoard[0][2] = InitialMove;assistance = 1;retorno = 1;}
    else if (oldGameBoard[2][0] == InitialMove && oldGameBoard[1][1] == InitialMove && oldGameBoard[0][2] == ' ') {oldGameBoard[0][2] = InitialMove;assistance = 1;retorno = 1;}
    else if (oldGameBoard[0][2] == InitialMove && oldGameBoard[1][1] == InitialMove && oldGameBoard[2][0] == ' ') {oldGameBoard[2][0] = InitialMove;assistance = 1;retorno = 1;}
    else if (oldGameBoard[2][2] == InitialMove && oldGameBoard[1][1] == InitialMove && oldGameBoard[0][0] == ' ') {oldGameBoard[0][0] = InitialMove;assistance = 1;retorno = 1;}
    else if (oldGameBoard[0][0] == InitialMove && oldGameBoard[1][1] == InitialMove && oldGameBoard[2][2] == ' ') {oldGameBoard[2][2] = InitialMove;assistance = 1;retorno = 1;}
    else{ assistance = 1; retorno = 2;} }
    while(assistance != 1);
       if (retorno == 1) { return 1; } // se houve InitialMove bem sucedidos, entao retorna 1
  else if (retorno == 2) { return 2;  }} // se nao houve InitialMove bem sucedidos, entao retorna 2
/*PLAY AGAIN*/
void jogar_novamente(){ setlocale(LC_ALL, "Portuguese");
  char option;
  int saida;
  do { fflush(stdin); // limpar o buffer
  printf("\n Você deseja jogar novamente?: \n");
  printf("S - para sim\n ");
  printf("N - Caso deseje sair.\n");
  fflush(stdin); // limpar o buffer
  scanf("%c",&option);
  option = toupper(option);
  switch (option) {
    case 'S': main(); saida = 1;break;
    case 'N': system("cls"); printf("\n\tObrigado por testestar o jogar!\n"); saida = 1; break;} } while(saida != 1);}
