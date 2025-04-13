int outer(int a) {
    int b = a * 2;
    
    int inner(int c) {
        // Can access outer function's variables
        int d = b + c;
        return d;
    }
    
    return inner(a + 1);
}

int main() {
    int x = 5;
    int result = outer(x);
    
    return result; // Should return (5*2) + (5+1) = 16
}