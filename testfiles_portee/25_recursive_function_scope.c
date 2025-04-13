int factorial(int n) {
    // Base case
    if (n <= 1) {
        return 1;
    }
    
    // Each recursive call creates a new scope for n
    // Previous values of n are preserved in the call stack
    int result = n * factorial(n - 1);
    return result;
}

int main() {
    int n = 4;
    int result = factorial(n);
    
    return result; // Should return 4*3*2*1 = 24
}