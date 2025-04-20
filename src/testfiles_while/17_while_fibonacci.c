int main() {
    int n = 8;
    int a = 0;
    int b = 1;
    int i = 2;
    int fib = 0;
    
    if(n <= 1) {
        return n;
    }
    
    while(i <= n) {
        fib = a + b;
        a = b;
        b = fib;
        i = i + 1;
    }
    
    return fib;
}