// filepath: c:\Users\Admin\source\repos\COMP-SAAD\testfiles_while\7_complex_arithmetic_while.c
int main() {
    int n = 1;
    int sum = 0;
    int product = 1;
    
    // Calculate sum of first 5 factorials: 1! + 2! + 3! + 4! + 5!
    while(n <= 5) {
        product = product * n;
        sum = sum + product;
        n = n + 1;
    }
    
    return sum;  // Should return 1 + 2 + 6 + 24 + 120 = 153
}