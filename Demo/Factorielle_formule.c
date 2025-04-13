#include <stdio.h>

// Function to calculate factorial iteratively
int factorielle(int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    int number;
    printf("Entrez un nombre: ");
    scanf("%d", &number);

    if (number < 0) {
        printf("La factorielle n'est pas définie pour les nombres négatifs.\n");
    } else {
        printf("La factorielle de %d est %d.\n", number, factorielle(number));
    }

    return 0;
}