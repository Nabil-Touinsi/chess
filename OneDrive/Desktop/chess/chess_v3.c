#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

// Déclaration de la structure Move et des nouvelles fonctions
typedef struct {
    int r1, c1;
    int r2, c2;
} Move;

int pwstatus[8] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 };
int pbstatus[8] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 };

char board[8][8] = {
    { 'R' , 'N' , ' ' , ' ' , 'Q' , ' ' , 'N' , 'R' },
    { ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' },
    { ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' },
    { ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' },
    { ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' },
    { ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' },
    { ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' },
    { 'r' , 'n' , ' ' , ' ' , 'q' , ' ' , 'n' , 'r' }
};

void display();
void change( int , int , int , int );
void rook(int , int );
void horse(int , int );
void queen(int , int );
void player1(int *);
void player2(int *);
void save_move(Move, int);
void load_game(int *);
void reset_save();

int main()
{
    int  x = 0;
    char ch, choice;
    int current_player = 1; // Détermine le joueur à qui c'est le tour, par défaut joueur 1

    printf( "\n\tWELCOME TO CHESS GAME" );
    printf( "\n\n\t By Shreeji , Neel , Kirtan " );

    getch();
    system( "cls" );

    printf("1. Nouvelle Partie\n");
    printf("2. Charger une sauvegarde\n");
    printf("Choisissez une option (1/2) : ");
    scanf(" %c", &choice);
    
    if (choice == '2') {
        load_game(&current_player);  // Charge l'état de la partie et le joueur courant
    } else if (choice == '1') {
        reset_save();  // Réinitialise la sauvegarde pour une nouvelle partie
    }

    do {
        x++;
        system("cls");
        display();

        if (current_player == 2) {
            player2(&current_player); // Tour du joueur 2
        } else {
            player1(&current_player); // Tour du joueur 1
        }

        printf(" \n\nPress Enter To Continue ! \n\n ");
        ch = getch();
    } while (ch == 13); // 13 correspond à la touche Enter

    return 0;
}

// Fonction d'affichage du plateau
void display()
{
    int i, j, k;

    printf(" ");
    for (i = 0; i < 8; i++) printf("    %d", i);
    printf("\n");

    for (k = 0; k < 8; k++) {
        printf("  ");
        for (i = 0; i < 42; i++) { printf("-"); }
        printf("\n%d ", k);

        for (j = 0; j < 8; j++) { printf("|| %c ", board[k][j]); }
        printf("|| \n");
    }

    printf("  ");
    for (i = 0; i < 42; i++) { printf("-"); }
    printf("\n");
}

// Fonction pour changer la position des pièces
void change(int r1, int c1, int r2, int c2)
{
    char temp;

    temp = board[r1][c1];
    board[r1][c1] = board[r2][c2];
    board[r2][c2] = temp;
}

// Exemple de mouvement de la tour
void rook(int r1, int c1)
{
    int n;

    printf("Available moves: \n");
    n = c1;
    printf("Horizontally: ");

    while (n > 0 && board[r1][n-1] == ' ') {
        printf("%d%d , ", r1, n-1);
        n--;
    }

    n = c1;

    while (n < 7 && board[r1][n+1] == ' ') {
        printf("%d%d , ", r1, n+1);
        ++n;
    }

    printf("\nVertically: ");

    n = r1;

    while (n > 0 && board[n-1][c1] == ' ') {
        printf("%d%d , ", n-1, c1);
        --n;
    }

    n = r1;

    while (n < 7 && board[n+1][c1] == ' ') {
        printf("%d%d , ", n+1, c1);
        ++n;
    }

    printf("\n");
}

// Exemple de mouvement du cheval
void horse(int r1, int c1)
{
    printf("Available moves: ");

    // Déplacements possibles d'un cheval (L-shape)
    if (r1+2 < 8 && c1+1 < 8 && board[r1+2][c1+1] == ' ') printf("%d%d, ", r1+2, c1+1);
    if (r1+2 < 8 && c1-1 >= 0 && board[r1+2][c1-1] == ' ') printf("%d%d, ", r1+2, c1-1);
    if (r1+1 < 8 && c1+2 < 8 && board[r1+1][c1+2] == ' ') printf("%d%d, ", r1+1, c1+2);
    if (r1-1 >= 0 && c1+2 < 8 && board[r1-1][c1+2] == ' ') printf("%d%d, ", r1-1, c1+2);
    if (r1-2 >= 0 && c1-1 >= 0 && board[r1-2][c1-1] == ' ') printf("%d%d, ", r1-2, c1-1);
    if (r1-2 >= 0 && c1+1 < 8 && board[r1-2][c1+1] == ' ') printf("%d%d, ", r1-2, c1+1);
    if (r1+1 < 8 && c1-2 >= 0 && board[r1+1][c1-2] == ' ') printf("%d%d, ", r1+1, c1-2);
    if (r1-1 >= 0 && c1-2 >= 0 && board[r1-1][c1-2] == ' ') printf("%d%d, ", r1-1, c1-2);

    printf("\n");
}

// Exemple de mouvement de la reine
void queen(int r1, int c1)
{
    printf("Available moves: \n");
    int a, b, x = 1, y = 1;

    // Horizontal gauche
    printf("Horizontal gauche: ");
    while ((c1 - y) >= 0 && board[r1][c1 - y] == ' ') {
        printf("%d%d , ", r1, c1 - y);
        y++;
    }

    // Horizontal droite
    printf("Horizontal droite: ");
    y = 1;
    while ((c1 + y) < 8 && board[r1][c1 + y] == ' ') {
        printf("%d%d , ", r1, c1 + y);
        y++;
    }

    // Vertical haut
    printf("\nVertical haut: ");
    while ((r1 - x) >= 0 && board[r1 - x][c1] == ' ') {
        printf("%d%d , ", r1 - x, c1);
        x++;
    }

    // Vertical bas
    printf("Vertical bas: ");
    x = 1;
    while ((r1 + x) < 8 && board[r1 + x][c1] == ' ') {
        printf("%d%d , ", r1 + x, c1);
        x++;
    }

    printf("\n");
}

// Actions pour le joueur 1
void player1(int *current_player)
{
    int p1, p2, c1, r1, c2, r2;
    Move move;

    printf("\nPLAYER 1 - Big Case\n");
again1:
    printf("\nEnter Position of Element to change (RC): ");
    scanf("%d", &p1);

    c1 = p1 % 10;
    r1 = p1 / 10;

    if (r1 < 0 || r1 > 7 || c1 < 0 || c1 > 7) {
        printf("Positions invalides ! Reessayez.\n");
        goto again1;
    }

    switch (board[r1][c1]) {
        case 'R': rook(r1, c1); break;
        case 'N': horse(r1, c1); break;
        case 'Q': queen(r1, c1); break;
        default: printf("Invalid Position ! "); goto again1;
    }

    printf("\nEnter Position of Place to Send (RC): ");
    scanf("%d", &p2);

    c2 = p2 % 10;
    r2 = p2 / 10;

    if (r2 < 0 || r2 > 7 || c2 < 0 || c2 > 7) {
        printf("Positions invalides ! Reessayez.\n");
        goto again1;
    }

    change(r1, c1, r2, c2);

    move.r1 = r1;
    move.c1 = c1;
    move.r2 = r2;
    move.c2 = c2;
    save_move(move, 2);  // Enregistre le coup avec le joueur courant
    *current_player = 2;  // Passe le tour au joueur 2
}

// Actions pour le joueur 2
void player2(int *current_player)
{
    int p1, p2, c1, r1, c2, r2;
    Move move;

    printf("\nPLAYER 2 - Small Case\n");
again2:
    printf("\nEnter Position of Element to change (RC): ");
    scanf("%d", &p1);

    c1 = p1 % 10;
    r1 = p1 / 10;

    if (r1 < 0 || r1 > 7 || c1 < 0 || c1 > 7) {
        printf("Positions invalides ! Reessayez.\n");
        goto again2;
    }

    switch (board[r1][c1]) {
        case 'r': rook(r1, c1); break;
        case 'n': horse(r1, c1); break;
        case 'q': queen(r1, c1); break;
        default: printf("Invalid Position ! "); goto again2;
    }

    printf("\nEnter Position of Place to Send (RC): ");
    scanf("%d", &p2);

    c2 = p2 % 10;
    r2 = p2 / 10;

    if (r2 < 0 || r2 > 7 || c2 < 0 || c2 > 7) {
        printf("Positions invalides ! Reessayez.\n");
        goto again2;
    }

    change(r1, c1, r2, c2);

    move.r1 = r1;
    move.c1 = c1;
    move.r2 = r2;
    move.c2 = c2;
    save_move(move, 1);  // Enregistre le coup avec le joueur courant
    *current_player = 1;  // Passe le tour au joueur 1
}

// Fonction pour sauvegarder un coup avec le joueur courant
void save_move(Move move, int player_turn)
{
    FILE *file = fopen("save_game.txt", "a"); // Ouvre en mode ajout
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde.\n");
        return;
    }
    fprintf(file, "%d %d %d %d %d\n", move.r1, move.c1, move.r2, move.c2, player_turn);  // Sauvegarde le tour du joueur
    fclose(file);
}

// Fonction pour charger la partie
void load_game(int *player_turn)
{
    FILE *file = fopen("save_game.txt", "r");  // Ouvre en mode lecture
    if (file == NULL) {
        printf("Aucune partie sauvegardée trouvée.\n");
        return;
    }

    Move move;
    while (fscanf(file, "%d %d %d %d %d", &move.r1, &move.c1, &move.r2, &move.c2, player_turn) == 5) {
        change(move.r1, move.c1, move.r2, move.c2);
    }

    fclose(file);
}

// Fonction pour réinitialiser la sauvegarde
void reset_save()
{
    FILE *file = fopen("save_game.txt", "w");  // Écrase le fichier existant
    if (file == NULL) {
        printf("Erreur lors de la réinitialisation du fichier de sauvegarde.\n");
        return;
    }
    fclose(file);
}

