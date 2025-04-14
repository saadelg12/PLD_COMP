#include <stdio.h>

int printTree(int height) {
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

 
         i = i + 1;
     }
     return 0;
 }
 
 int printTrunk(int height) {
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

        i = i + 1;
     }
     return 0;
 }
 
 int main() {
     int height = 7;

     if (height > 0) {
         printTree(height);
         printTrunk(height);
     } else {
         putchar('E');
         putchar('r');
         putchar('r');
         putchar('o');
         putchar('r');
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
     }
 
     return 0;
 }