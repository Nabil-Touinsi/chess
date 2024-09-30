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

// Déclaration des fonctions
void display();
void change( int , int , int , int );
void rook(int , int , int);
void horse(int , int , int);
void queen(int , int , int);
void player1(int *);
void player2(int *);
void save_move(Move, int);
void load_game(int *);
void reset_save();
int is_opponent_piece(char piece, int current_player);
int check_game_over(); // Ajout de la fonction de vérification de fin de partie
void end_game(int winner); // Ajout de la fonction de fin de partie

int main()
{
    int  x = 0;
    char ch, choice;
    int current_player = 1; // Détermine le joueur à qui c'est le tour, par défaut joueur 1

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
            load_game(&current_player);  // Charge l'état de la partie et le joueur courant
        } else if (choice == '1') {
            reset_save();  // Réinitialise la sauvegarde pour une nouvelle partie
        }

        do {
            x++;
            system("cls");
            display();

            // Vérifier si la partie est terminée
            if (check_game_over()) {
                break;
            }

            if (current_player == 2) {
                player2(&current_player); // Tour du joueur 2
            } else {
                player1(&current_player); // Tour du joueur 1
            }

            printf(" \n\nPress Enter To Continue ! \n\n ");
            ch = getch();
        } while (ch == 13); // 13 correspond à la touche Enter

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

// Fonction pour changer la position des pièces
void change(int r1, int c1, int r2, int c2)
{
    // La fonction change s'assure que la pièce se déplace
    // et écrase la pièce adverse si elle est capturée
    board[r2][c2] = board[r1][c1];  // Déplace la pièce
    board[r1][c1] = ' ';  // Vide la case précédente
}

// Fonction pour vérifier si la pièce est celle de l'adversaire
int is_opponent_piece(char piece, int current_player)
{
    if (current_player == 1) {
        // Joueur 1 (majuscules) peut capturer les pièces en minuscules
        return piece >= 'a' && piece <= 'z';
    } else {
        // Joueur 2 (minuscules) peut capturer les pièces en majuscules
        return piece >= 'A' && piece <= 'Z';
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
            break;  // Arrête après la capture
        } else {
            break;  // Impossible d'aller plus loin si c'est une pièce alliée
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
    
    // Mouvement en L : 2 cases dans une direction et 1 case dans une autre
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

// Exemple de mouvement de la reine
void queen(int r1, int c1, int current_player)
{
    printf("Available moves: \n");

    // Mouvement horizontal et vertical (comme la tour)
    rook(r1, c1, current_player);  // On réutilise la logique de la tour

    // Mouvement diagonal (comme le fou)
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
        case 'R': rook(r1, c1, *current_player); break;
        case 'N': horse(r1, c1, *current_player); break;
        case 'Q': queen(r1, c1, *current_player); break;
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
        case 'r': rook(r1, c1, *current_player); break;
        case 'n': horse(r1, c1, *current_player); break;
        case 'q': queen(r1, c1, *current_player); break;
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

// Fonction pour vérifier si la partie est terminée
int check_game_over() {
    int pieces_player1 = 0;
    int pieces_player2 = 0;

    // Compte les pièces des deux joueurs
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

// Fonction pour gérer la fin de partie
void end_game(int winner) {
    printf("\n--- Fin de la partie ---\n");
    if (winner == 1) {
        printf("Le joueur 1 a gagné !\n");
    } else if (winner == 2) {
        printf("Le joueur 2 a gagné !\n");
    }

    printf("\nAppuyez sur une touche pour revenir au menu principal...\n");
    getch();
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

