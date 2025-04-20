#include <stdio.h>

int factorielle_recursive(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorielle_recursive(n - 1);
}

int main() {
    int nombre = 10; // le resultat de la factorielle doit etre stocke dans un int donc a partir de 12, cela ne fonctionne plus

    if (nombre < 0) {
        putchar('L');
        putchar('a');
        putchar(' ');
        putchar('f');
        putchar('a');
        putchar('c');
        putchar('t');
        putchar('o');
        putchar('r');
        putchar('i');
        putchar('e');
        putchar('l');
        putchar('l');
        putchar('e');
        putchar(' ');
        putchar('n');
        putchar('\'');
        putchar('e');
        putchar('s');
        putchar('t');
        putchar(' ');
        putchar('p');
        putchar('a');
        putchar('s');
        putchar(' ');
        putchar('d');
        putchar('e');
        putchar('f');
        putchar('i');
        putchar('n');
        putchar('i');
        putchar('e');
        putchar(' ');
        putchar('p');
        putchar('o');
        putchar('u');
        putchar('r');
        putchar(' ');
        putchar('l');
        putchar('e');
        putchar('s');
        putchar(' ');
        putchar('n');
        putchar('o');
        putchar('m');
        putchar('b');
        putchar('r');
        putchar('e');
        putchar('s');
        putchar(' ');
        putchar('n');
        putchar('e');
        putchar('g');
        putchar('a');
        putchar('t');
        putchar('i');
        putchar('f');
        putchar('s');
        putchar('.');
        putchar('\n');
    } else {
        putchar('L');
        putchar('a');
        putchar(' ');
        putchar('f');
        putchar('a');
        putchar('c');
        putchar('t');
        putchar('o');
        putchar('r');
        putchar('i');
        putchar('e');
        putchar('l');
        putchar('l');
        putchar('e');
        putchar(' ');
        putchar('d');
        putchar('e');
        putchar(' ');
        int temp = nombre;
        if (temp == 0) {
            putchar('0');
        } else {
            int buffer[10];
            int index = 0;
            while (temp > 0) {
                buffer[index] = temp % 10;
                index = index + 1;
                temp = temp / 10;
            }
            while (index > 0) {
                index = index - 1;
                putchar(buffer[index] + '0');
            }
        }
        putchar(' ');
        putchar('e');
        putchar('s');
        putchar('t');
        putchar(' ');
        int fact = factorielle_recursive(nombre);
        temp = fact;
        if (temp == 0) {
            putchar('0');
        } else {
            int buffer[10];
            int index = 0;
            while (temp > 0) {
                buffer[index] = temp % 10;
                index = index + 1;
                temp = temp / 10;
            }
            while (index > 0) {
                index = index - 1;
                putchar(buffer[index] + '0');
            }
        }
        putchar('\n');
    }

    return 0;
}
