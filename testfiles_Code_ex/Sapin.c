#include <stdio.h>

void printTree(int height) {
    int i = 0;
    while (i < height) {

        int spaces;

        if (height == 1) {
            spaces = 1;
        } else {
            spaces = height - i - 1;
        }
            
        int stars = 2 * i + 1;

        int j = 0;
        while (j < spaces) {
            putchar(' ');
            j=j + 1;
        }

        j = 0;
        while (j < stars) {
            putchar('*');
            j=j + 1;
        }

        putchar('\n');
        i = i + 1;
    }
}

void printTrunk(int height) {
    int i = 0;
    while (i < 2) {
        int spaces = height - 2;

        int j = 0;
        while (j < spaces) {
            putchar(' ');
            j=j + 1;
        }

        putchar('|');
        putchar('|');
        putchar('|');
        putchar('\n');
        i = i + 1;
    }
}

int main() {
    int height = 0;

    choose the height of the tree
    putchar('C');
    putchar('h');
    putchar('o');
    putchar('o');
    putchar('s');
    putchar('e');
    putchar(' ');
    putchar('t');
    putchar('h');
    putchar('e');
    putchar(' ');
    putchar('h');
    putchar('e');
    putchar('i');
    putchar('g');
    putchar('h');
    putchar('t');
    putchar(' ');
    putchar('o');
    putchar('f');
    putchar(' ');
    putchar('t');
    putchar('h');
    putchar('e');
    putchar(' ');
    putchar('t');
    putchar('r');
    putchar('e');
    putchar('e');
    
    putchar(':');


    height = getchar() - '0';

    if (height > 0) {
        printTree(height);
        printTrunk(height);
    } else {
        putchar('E');
        putchar('r');
        putchar('r');
        putchar('e');
        putchar('u');
        putchar('r');
        putchar('e');
        putchar(':');
        putchar(' ');
        putchar('H');
        putchar('e');
        putchar('i');
        putchar('g');
        putchar('h');
        putchar('t');
        putchar(' ');
        putchar('i');
        putchar('s');
        putchar(' ');
        putchar('i');
        putchar('n');
        putchar('v');
        putchar('a');
        putchar('l');
        putchar('i');
        putchar('d');
        putchar('\n');
    }

    return 0;
}