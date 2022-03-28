/*--------------------------------------------------------------------*/
/**                        PROJETO 2                                 **/
/**               IMPLEMENTATION OF THE FORCE GAME                    **/
/** Desenvolvido por João Vitor Andrade e Thiago dos Santos          **/
/**                       TADS - 2021/22                             **/
/*--------------------------------------------------------------------*/
#include <stdio.h> //standard library, has basic entrance and exit controls
#include <time.h> //Used to generate random numbers
#include <stdlib.h> //Used for System Commands ("");
#include <ctype.h> //Used for character functions
#include <string.h> //Contains operations with strings

void menu(); //Displays the menu
void sair(); //leave the game
void initialize(int a); //Creates the test string used in the game
void display(); //Prints test string

int entrada(); //Read the letter provided by User
int check_palpite (int a); //Verifies if the letter belongs to the word
int check_vitoria (void); //verifies that the person won

void enforcado(void); //Prints the doll depending on the amount of errors
void viveu(); //victory
void morreu(); //Image of defeat
void alfabeto(); //Prints string with alphabet letters
void reset_valores(); //Reset the values of variables so you can play again

int novamente(int a); //ask if the person wants to play again
void dica(int a); //Prints a word tip
int mecanismo_jogo(int a); //game mechanism
int jogar(void); //match

void limpa_buffer(); //Clean buffer

// Global variables
int erros=0;
char palpite = '0', teste[21];

char palavras[][21] = {
"Cachorro","Gato", "Foca", "Elefante", "Ornitorrinco",/*0-4*/
"William Bonner","Madonna","Aristoteles","Santos Dumont","Clarice Lispector",/*5-9*/
"Bangladesh","Alemanha","Madagascar","Noruega","Irlanda"/*10-14*/};

char dicas[][50] = {
"Melhor amigo do homem","Seus bigodes fazem cocegas","O animal mais ruidoso do mundo",
"Maior mamifero terrestre","Mamifero que bota ovos",/*0-4*/
"Ancora famoso de jornal brasileiro","Rainha do pop","Famoso filosofo grego",
"Inventor do relogio de pulso","Famosa por seus livros e contos",/*5-9*/
"A lingua mais falada nesse pais e o bengali","O sobrenome mais popular nesse pais e Muller",
"Pais onde habitam os lemures","Pais conhecido por exportar bacalhau","Pais dos duendes"/*10-14*/};

char alfa[] = {"abcdefghijklmnopqrstuvwxyz"};

//main funciation
int main()
{
    menu();
}

// menuPrincipal
void menu()
{
    int c;
    system("cls");
    printf("\nJOGO DA FORCA\n"
           "\nDigite a opcao desejada\n"
           "1. Jogar\n"
           "2. Sair\n");
    scanf("%d", &c);

    switch (c)
    {
        case 1 :
            jogar();
            break;
        case 2 :
            sair();
            break;
        default :
            printf ("\nOpcao invalida! Digite uma opcao valida\n");
            system("pause");
            menu();
    }

    limpa_buffer();
}

//leave the game
void sair()
{
    int c;
    system("cls");
    printf("\nDeseja realmente sair?\n"
           "1. Sim\n"
           "2. Nao\n");
    scanf("%d", &c);

    switch (c)
    {
        case 1 :
            system ("cls");
            printf("\nObrigado por jogar\n");
            system("pause");
            exit(0);
            break;
        case 2 :
            menu();
            break;
        default :
            printf ("\nOpcao invalida! Digite uma opcao valida\n");
            system("pause");
            sair();
    }

    limpa_buffer();
}

//Match
int jogar(void)
{
    int a, novojogo;
    srand ( time(NULL) );

    while(1)
    {
        a = rand()%15;
        system("cls");
        initialize(a); //Creates the string of '_ _'
        mecanismo_jogo(a);
        novojogo = novamente(a);
        if(novojogo) //Call the menu if it is false
            menu();
        reset_valores();
    }
    return 0;
}

// Creates the word string that will be used in the gallows.
void initialize(int a)
{
    int i;
    system("cls");
    for (i=0; palavras[a][i] != '\0'; i++)
    {
        if (palavras[a][i] == ' ')
            teste[i] = palavras[a][i];
        else
            teste[i] = '_';
    }
}

//Mechanism of the forca game.
int mecanismo_jogo(int a)
{
    while (erros<6)
    {
        printf("\n\tVoce pode errar %d vezes.\n", 6-erros);
        enforcado();
        display();
        alfabeto();
        dica(a);

        if (entrada())
        {
            system("cls");
            continue; // It only makes the current itercage stop, jumping for next
        }
        check_palpite(a);
        if (!(check_vitoria()))
            return 0;
        system("cls");
    }

    enforcado();
    return 0;
}

// At the end of the game, it allows a new match.
int novamente(int a)
{
    int c;
    system ("cls");
    if (erros == 6)
    {
        morreu();
        printf("\n\nVoce Perdeu!\n\n");
        printf("A palavra era: %s\n\n", palavras[a]);
    }
    else
    {
        viveu();
        printf("\n\nParabens!\n\n"
               "Voce venceu \n\n");
        printf("A palavra era: %s\n\n", palavras[a]);
    }

    printf("\nVoce deseja jogar de novo?\n");
    printf("1. Sim\n"
           "2. Nao\n");
    scanf("%d",&c);

    switch (c)
    {
        case 1 :
            reset_valores();
            return 0;
            break;
        case 2 :
            reset_valores();
            return 1;
            break;
        default :
            printf ("\nOpcao invalida! Digite uma opcao valida\n");
            system("pause");
            novamente(a);
    }

    limpa_buffer();
}

// Reset the values so you can play again
void reset_valores(void)
{
    int a;
    erros=0;
    palpite = '0';
    for (a=0; teste[a]!= '\0'; a++)
    {
        teste[a] = '\0';
    }
    memmove(alfa, "abcdefghijklmnopqrstuvwxyz", 27); // Copy the full alpha string for memory again
}

// Prints the Fork Doll for each number of errors.
void enforcado(void)
{
    switch (erros)
    {
        case 0:
            printf ("_________     \n"
                    "|       |     \n"
					"|             \n"
                    "|             \n"
					"|             \n"
					"|     ______  \n"
					"|     |    |  \n"
					"|     |    |  \n");
            break;
        case 1:
            printf ("_________     \n"
                    "|       |     \n"
					"|      (oo)   \n"
					"|             \n"
					"|             \n"
					"|     ______  \n"
					"|     |    |  \n"
					"|     |    |  \n");
            break;
        case 2:
            printf ("_________     \n"
                    "|       |     \n"
					"|      (oo)   \n"
					"|       ||    \n"
					"|             \n"
					"|     ______  \n"
					"|     |    |  \n"
					"|     |    |  \n");
            break;
        case 3:
            printf ("_________     \n"
                    "|       |     \n"
					"|      (oo)   \n"
					"|      /||    \n"
					"|             \n"
					"|     ______  \n"
					"|     |    |  \n"
					"|     |    |  \n");
            break;
        case 4:
            printf ("_________     \n"
                    "|       |     \n"
					"|      (oo)   \n"
					"|      /||\\  \n"
					"|             \n"
					"|     ______  \n"
					"|     |    |  \n"
					"|     |    |  \n");
            break;
        case 5:
            printf ("_________     \n"
                    "|       |     \n"
					"|      (oo)   \n"
					"|      /||\\  \n"
					"|       /     \n"
					"|     ______  \n"
					"|     |    |  \n"
					"|     |    |  \n");
            break;
        case 6:
            printf ("_________     \n"
                    "|       |     \n"
					"|      (oo)   \n"
					"|      /||\\  \n"
					"|       /\\   \n"
					"|     ______  \n"
					"|     |    |  \n"
					"|     |    |  \n");
            break;
        system ("cls");
    }
}

//Show the status of the game.
void display(void)
{
    int k;
    printf("\n");
    for (k=0; teste[k] != '\0'; k++)
    {
        putchar(teste[k]);
        printf(" ");
    }
    printf("\n");
}

//Shows the alphabet and removes the letters already used, replacing them by '-'.
void alfabeto (void)
{
    int i;
    printf("\n");
	for (i=0; alfa[i] != '\0'; i++)
	{
		if (palpite == alfa[i])
			alfa[i] = '-';
        putchar (alfa[i]);
		printf(" ");
    }
    printf("\n\n");
}

//Prints on the screen the tip for the word
void dica(int a)
{
    if(a <= 4)
        printf("DICA: \nAnimal");
    else if(a <= 9)
        printf("DICA: \nPessoa");
    else if(a <= 14)
        printf("DICA: \nLugar");
    printf("\n%s",dicas[a]);
    printf("\n\n\n");
}

// Read the PALPITE, with the care of disposing invalid entries.
int entrada(void)
{
    char op;
    printf("Digite uma letra: ");
    scanf("%c", &op);
    palpite = op;

    if (palpite == '\n')
        return 1;
    limpa_buffer();
    if(!isalpha(palpite)) // isalpha checks if or caracter and alphabetical
        return 1;
    palpite = tolower(palpite); //minusculas
    return 0;
}

// Czech the guess.If certain, it replaces the respective '_' by the corresponding letter.
// if wrong, add a variable errors * /
int check_palpite (int a)
{
    int i;
    for (i=0; palavras[a][i] != '\0'; i++)
    {
        if (palpite == palavras[a][i] || toupper(palpite)==palavras[a][i]) //maiscula
            teste[i] = palavras[a][i];
    }
    if (!(strchr(alfa, palpite))) // StrCHR looks for the first occurrence of the character in the string pointed by the argument
        return 1;
    if((!(strchr(palavras[a], palpite))) && (!(strchr(palavras[a], toupper(palpite)))))
        erros++;
    return 0;
}

// Checks if the person won.
int check_vitoria (void)
{
    int x, y;
    for(x=0, y=0; teste[x] != '\0'; x++)
    {
        if (teste[x] == '_')
            continue;
        else
            y++;
    }
    if(x == y)
    {
        display();
        return 0;
    }
    return 1;
}

// Figure for cases of Vitoria.
void viveu()
{
    printf ("_________            \n"
            "|       |            \n"
            "|                    \n"
	        "|                    \n"
	        "|                    \n"
	        "|     ______  (oo)   \n"
	        "|     |    |  /||\\  \n"
            "|     |    |   /\\   \n");
}

// Animation for the case of defeat...
void morreu()
{
    system("cls");
    printf ("_________      \n"
            "|       |      \n"
            "|       |      \n"
			"|      (xx)    \n"
			"|      /||\\   \n"
			"|       /\\    \n"
            "|     |\\  /|  \n"
			"|     |    |   \n");
}

// Clean any character that is on the screen and functions as System ("Pause")
void limpa_buffer()
{
    char x;
    do {
        x = getchar();
    }while ((x != '\n')&&(x != EOF));
}
