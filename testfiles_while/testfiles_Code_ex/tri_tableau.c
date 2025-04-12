#include <stdio.h>

void selection_sort(int arr[], int size) {
    int i = 0;
    while (i < size - 1) {
        int min_index = i;
        int j = i + 1;
        while (j < size) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
            j= j + 1;
        }
        if (min_index != i) {
            int temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
        }
        i = i + 1;
    }
}

void print_array(int arr[], int size) {
    int i = 0;
    while (i < size) {
        int num = arr[i];
        if (num < 0) {
            putchar('-');
            num = -num;
        }
        int digits[10];
        int digit_count = 0;
        int temp_num = num;
        while (temp_num > 0) {
            digits[digit_count] = temp_num % 10;
            digit_count = digit_count + 1;
            temp_num = temp_num / 10;
        }
        if (digit_count == 0) {
            digits[digit_count] = 0;
            digit_count = digit_count + 1;
        }
        while (digit_count > 0) {
            digit_count = digit_count - 1;
            putchar('0' + digits[digit_count]);
        }
        putchar(' ');
        i = i + 1;
    }
    putchar('\n');
}

int main() {
    int arr[] = {64, 25, 12, 22, 11};
    int size = 5;

    putchar('O'); 
    putchar('r'); 
    putchar('i'); 
    putchar('g'); 
    putchar('i'); 
    putchar('n'); 
    putchar('a'); 
    putchar('l'); 
    putchar(' '); 
    putchar('a'); 
    putchar('r'); 
    putchar('r'); 
    putchar('a'); 
    putchar('y'); 
    putchar(':');
    putchar('\n');
    print_array(arr, size);

    selection_sort(arr, size);

    putchar('S'); 
    putchar('o'); 
    putchar('r'); 
    putchar('t'); 
    putchar('e'); 
    putchar('d'); 
    putchar(' '); 
    putchar('a'); 
    putchar('r'); 
    putchar('r'); 
    putchar('a'); 
    putchar('y'); 
    putchar(':'); 
    putchar('\n');
    print_array(arr, size);

    return 0;
}