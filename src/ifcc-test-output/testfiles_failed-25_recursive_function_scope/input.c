int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    

    int result = n * factorial(n - 1);
    return result;
}

int main() {
    int n = 4;
    int result = factorial(n);
    
    return result; 
}