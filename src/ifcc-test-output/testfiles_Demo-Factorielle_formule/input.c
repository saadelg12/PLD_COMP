#include <stdio.h>

int factorielle(int n) {
    int result = 1;
    while (i<= n) {
        result *= i;
        i = i + 1;
    }
    return result;
}

int main() {
    int number = 5;
    int a = factorielle(number);


    return a;
}