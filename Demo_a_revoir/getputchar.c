#include <stdio.h>

int main() {
    int secret =3;
    int guess = -1;
    int input;
    while (guess != secret) {
        input = getchar();
        guess = input;
    }
    return 0;
}