#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

// D�claration de la structure Move et des nouvelles fonctions
typedef struct {
    int r1, c1;
    int r2, c2;
} Move;

int pwstatus[8] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 };
int pbstatus[8] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 };

char board[8][8] = {
    { 'R' , 'N' , 'B' , ' ' , 'Q' , 'B' , 'N' , 'R' },
    { ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' },
    { ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' },
    { ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' },
    { ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' },
    { ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' },
    { ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' },
    { 'r' , 'n' , 'b' , ' ' , 'q' , 'b' , 'n' , 'r' }
};

// D�claration des fonctions
void display();
void change( int , int , int , int );
void rook(int , int , int);
void horse(int , int , int);
void queen(int , int , int);
void bishop(int, int, int); // Fonction ajout�e pour le fou
void player1(int *, char *);
void player2(int *, char *);
void save_move(Move, int, char *);
void load_game(int *, char *);
void reset_save(char *);
int is_opponent_piece(char piece, int current_player);
int check_game_over(); // Ajout de la fonction de v�rification de fin de partie
void end_game(int winner); // Ajout de la fonction de fin de partie

int main()
{
    int  x = 0;
    char ch, choice;
    int current_player = 1; // D�termine le joueur � qui c'est le tour, par d�faut joueur 1
    char filename[100]; // Variable pour stocker le nom de fichier

    while(1) {
        printf( "\n\tWELCOME TO CHESS GAME" );
        printf( "\n\n\t By Shreeji , Neel , Kirtan " );

        getch();
        system( "cls" );

        printf("1. Nouvelle Partie\n");
        printf("2. Charger une sauvegarde\n");
        printf("Choisissez une option (1/2) : ");
        scanf(" %c", &choice);

        if (choice == '2') {
            printf("Entrez le nom du fichier de sauvegarde � charger (ex: partie1.txt) : ");
            scanf("%s", filename);
            load_game(&current_player, filename);  // Charge l'�tat de la partie depuis le fichier
        } else if (choice == '1') {
            printf("Entrez le nom du fichier pour la nouvelle partie (ex: partie1.txt) : ");
            scanf("%s", filename);
            reset_save(filename);  // R�initialise la sauvegarde pour une nouvelle partie
        }

        do {
            x++;
            system("cls");
            display();

            // V�rifier si la partie est termin�e
            if (check_game_over()) {
                break;
            }

            if (current_player == 2) {
                player2(&current_player, filename); // Tour du joueur 2
            } else {
                player1(&current_player, filename); // Tour du joueur 1
            }

            printf(" \n\nPress Enter To Continue ! \n\n ");
            ch = getch();
        } while (ch == 13); // 13 correspond � la touche Enter

        // Fin de partie et retour au menu
        system("cls");
    }

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

// Fonction pour changer la position des pi�ces
void change(int r1, int c1, int r2, int c2)
{
    board[r2][c2] = board[r1][c1];  // D�place la pi�ce
    board[r1][c1] = ' ';  // Vide la case pr�c�dente
}

// Fonction pour v�rifier si la pi�ce est celle de l'adversaire
int is_opponent_piece(char piece, int current_player)
{
    if (current_player == 1) {
        return piece >= 'a' && piece <= 'z'; // Joueur 1 peut capturer les pi�ces en minuscules
    } else {
        return piece >= 'A' && piece <= 'Z'; // Joueur 2 peut capturer les pi�ces en majuscules
    }
}

// Exemple de mouvement de la tour
void rook(int r1, int c1, int current_player)
{
    int n;

    printf("Available moves: \n");
    n = c1;

    printf("Horizontally: ");
    // Vers la gauche
    while (n > 0) {
        if (board[r1][n-1] == ' ') {
            printf("%d%d , ", r1, n-1);
        } else if (is_opponent_piece(board[r1][n-1], current_player)) {
            printf("%d%d (capture), ", r1, n-1);
            break;
        } else {
            break;
        }
        n--;
    }

    n = c1;
    // Vers la droite
    while (n < 7) {
        if (board[r1][n+1] == ' ') {
            printf("%d%d , ", r1, n+1);
        } else if (is_opponent_piece(board[r1][n+1], current_player)) {
            printf("%d%d (capture), ", r1, n+1);
            break;
        } else {
            break;
        }
        ++n;
    }

    printf("\nVertically: ");
    n = r1;
    // Vers le haut
    while (n > 0) {
        if (board[n-1][c1] == ' ') {
            printf("%d%d , ", n-1, c1);
        } else if (is_opponent_piece(board[n-1][c1], current_player)) {
            printf("%d%d (capture), ", n-1, c1);
            break;
        } else {
            break;
        }
        --n;
    }

    n = r1;
    // Vers le bas
    while (n < 7) {
        if (board[n+1][c1] == ' ') {
            printf("%d%d , ", n+1, c1);
        } else if (is_opponent_piece(board[n+1][c1], current_player)) {
            printf("%d%d (capture), ", n+1, c1);
            break;
        } else {
            break;
        }
        ++n;
    }

    printf("\n");
}

// Exemple de mouvement du cheval
void horse(int r1, int c1, int current_player)
{
    printf("Available moves: ");
    
    int moves[8][2] = {
        {2, 1}, {2, -1}, {1, 2}, {1, -2},
        {-2, 1}, {-2, -1}, {-1, 2}, {-1, -2}
    };

    for (int i = 0; i < 8; i++) {
        int nr = r1 + moves[i][0];
        int nc = c1 + moves[i][1];

        if (nr >= 0 && nr < 8 && nc >= 0 && nc < 8) {
            if (board[nr][nc] == ' ') {
                printf("%d%d, ", nr, nc);
            } else if (is_opponent_piece(board[nr][nc], current_player)) {
                printf("%d%d (capture), ", nr, nc);
            }
        }
    }

    printf("\n");
}

// Mouvement du fou
void bishop(int r1, int c1, int current_player)
{
    printf("Available moves: \n");
    int x, y;

    // Diagonale haut-gauche
    printf("Diagonale haut-gauche: ");
    x = r1 - 1;
    y = c1 - 1;
    while (x >= 0 && y >= 0) {
        if (board[x][y] == ' ') {
            printf("%d%d , ", x, y);
        } else if (is_opponent_piece(board[x][y], current_player)) {
            printf("%d%d (capture), ", x, y);
            break;
        } else {
            break;
        }
        x--;
        y--;
    }

    // Diagonale haut-droite
    printf("Diagonale haut-droite: ");
    x = r1 - 1;
    y = c1 + 1;
    while (x >= 0 && y < 8) {
        if (board[x][y] == ' ') {
            printf("%d%d , ", x, y);
        } else if (is_opponent_piece(board[x][y], current_player)) {
            printf("%d%d (capture), ", x, y);
            break;
        } else {
            break;
        }
        x--;
        y++;
    }

    // Diagonale bas-gauche
    printf("Diagonale bas-gauche: ");
    x = r1 + 1;
    y = c1 - 1;
    while (x < 8 && y >= 0) {
        if (board[x][y] == ' ') {
            printf("%d%d , ", x, y);
        } else if (is_opponent_piece(board[x][y], current_player)) {
            printf("%d%d (capture), ", x, y);
            break;
        } else {
            break;
        }
        x++;
        y--;
    }

    // Diagonale bas-droite
    printf("Diagonale bas-droite: ");
    x = r1 + 1;
    y = c1 + 1;
    while (x < 8 && y < 8) {
        if (board[x][y] == ' ') {
            printf("%d%d , ", x, y);
        } else if (is_opponent_piece(board[x][y], current_player)) {
            printf("%d%d (capture), ", x, y);
            break;
        } else {
            break;
        }
        x++;
        y++;
    }

    printf("\n");
}

// Exemple de mouvement de la reine
void queen(int r1, int c1, int current_player)
{
    printf("Available moves: \n");

    // Mouvement horizontal et vertical (comme la tour)
    rook(r1, c1, current_player);

    // Mouvement diagonal (comme le fou)
    bishop(r1, c1, current_player);
}

// Actions pour le joueur 1
void player1(int *current_player, char *filename)
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
        case 'R': rook(r1, c1, *current_player); break;
        case 'N': horse(r1, c1, *current_player); break;
        case 'Q': queen(r1, c1, *current_player); break;
        case 'B': bishop(r1, c1, *current_player); break;  // Ajout du fou
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
    save_move(move, 2, filename);
    *current_player = 2;
}

// Actions pour le joueur 2
void player2(int *current_player, char *filename)
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
        case 'r': rook(r1, c1, *current_player); break;
        case 'n': horse(r1, c1, *current_player); break;
        case 'q': queen(r1, c1, *current_player); break;
        case 'b': bishop(r1, c1, *current_player); break;  // Ajout du fou
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
    save_move(move, 1, filename);
    *current_player = 1;
}

// Fonction pour v�rifier si la partie est termin�e
int check_game_over() {
    int pieces_player1 = 0;
    int pieces_player2 = 0;

    // Compte les pi�ces des deux joueurs
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            if (board[r][c] >= 'A' && board[r][c] <= 'Z') {
                pieces_player1++;
            } else if (board[r][c] >= 'a' && board[r][c] <= 'z') {
                pieces_player2++;
            }
        }
    }

    if (pieces_player1 == 0) {
        end_game(2); // Le joueur 2 gagne
        return 1;
    } else if (pieces_player2 == 0) {
        end_game(1); // Le joueur 1 gagne
        return 1;
    }

    return 0; // La partie continue
}

// Fonction pour g�rer la fin de partie
void end_game(int winner) {
    printf("\n--- Fin de la partie ---\n");
    if (winner == 1) {
        printf("Le joueur 1 a gagn� !\n");
    } else if (winner == 2) {
        printf("Le joueur 2 a gagn� !\n");
    }

    printf("\nAppuyez sur une touche pour revenir au menu principal...\n");
    getch();
}

// Fonction pour sauvegarder un coup avec le joueur courant dans un fichier sp�cifique
void save_move(Move move, int player_turn, char *filename)
{
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde.\n");
        return;
    }
    fprintf(file, "%d %d %d %d %d\n", move.r1, move.c1, move.r2, move.c2, player_turn);
    fclose(file);
}

// Fonction pour charger la partie depuis un fichier sp�cifique
void load_game(int *player_turn, char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Fichier de sauvegarde non trouv� : %s\n", filename);
        return;
    }

    Move move;
    while (fscanf(file, "%d %d %d %d %d", &move.r1, &move.c1, &move.r2, &move.c2, player_turn) == 5) {
        change(move.r1, move.c1, move.r2, move.c2);
    }

    fclose(file);
}

// Fonction pour r�initialiser une sauvegarde (cr�er un fichier vide ou r��crire un fichier)
void reset_save(char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erreur lors de la cr�ation du fichier de sauvegarde.\n");
        return;
    }
    fclose(file);
}

