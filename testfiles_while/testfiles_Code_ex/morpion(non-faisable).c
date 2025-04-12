#include <stdio.h>

void afficherGrille(char grille[3 * 3]) {
    int i = 0;
    int j;
    while (i < 3) {
        j = 0;
        while (j < 3) {
            putchar(grille[i * 3 + j]);
            if (j < 3 - 1)
            {
                putchar('|');
            }
            j = j + 1;
        }
        putchar('\n');
        if (i < 3 - 1) {
            j = 0;
            while (j < 3 * 2 - 1) {
                putchar('-');
                j=j + 1;
            }
            putchar('\n');
        }
        i= i + 1;
    }
}

int verifierGagnant(char grille[3 * 3]) {
    int i = 0;
    while (i < 3) {
        if (grille[i * 3] == grille[i * 3 + 1] && grille[i * 3 + 1] == grille[i * 3 + 2] && grille[i * 3] != ' ') return 1;
        if (grille[i] == grille[i + 3] && grille[i + 3] == grille[i + 2 * 3] && grille[i] != ' ') return 1;
        i= i + 1;
    }
    if (grille[0] == grille[3 + 1] && grille[3 + 1] == grille[2 * 3 + 2] && grille[0] != ' ') return 1;
    if (grille[3 - 1] == grille[3 + 1] && grille[3 + 1] == grille[2 * 3 - 1] && grille[3 - 1] != ' ') return 1;
    return 0;
}

int main() {
    char grille[3 * 3] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    int joueur = 1
    int ligne, colonne, coups = 0;
    char symbole;
    int jeuEnCours = 1;

    while (jeuEnCours) {
        afficherGrille(grille);
        if (joueur == 1) symbole = 'X';
        else symbole = 'O';

        printf("Joueur %d (%c):\n", joueur, symbole);

        printf("Ligne: ");
        ligne = getchar() - '0';
        getchar(); // Consommer le retour à la ligne

        printf("Colonne: ");
        colonne = getchar() - '0';
        getchar(); // Consommer le retour à la ligne

        if (ligne < 0 || ligne >= 3 || colonne < 0 || colonne >= 3 || grille[ligne * 3 + colonne] != ' ') {
            printf("Invalide!\n");
            jeuEnCours = jeuEnCours; // Pas de continue
        } else {
            grille[ligne * 3 + colonne] = symbole;
            coups++;

            if (verifierGagnant(grille)) {
                afficherGrille(grille);
                printf("Joueur %d gagne!\n", joueur);
                jeuEnCours = 0; // Pas de break
            } else if (coups == 3 * 3) {
                afficherGrille(grille);
                printf("Egalite!\n");
                jeuEnCours = 0; // Pas de break
            } else {
                joueur = 3 - joueur; // Alterner entre 1 et 2
            }
        }
    }

    return 0;
}
