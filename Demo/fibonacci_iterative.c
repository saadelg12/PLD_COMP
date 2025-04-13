int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    int a = 0;
    int b = 1;
    int i = 2;
    int fib = 0;
    while (i <= n) {
        fib = a + b;
        a = b;
        b = fib;
        i = i + 1;
    }
    return fib;
}

int main() {
    int num = 10;
    return fibonacci(num); 
}