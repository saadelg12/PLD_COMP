
int calculate(int x, int y);

int multiply(int a, int b) {
    return a * b;
}

int add(int a, int b) {
    return a + b;
}

int calculate(int x, int y) {
    int result = add(x, y);
    result = multiply(result, 2);
    return result;
}

int main() {
    int x = 5;
    int y = 3;
    
    int result = calculate(x, y);
    
    return result; // Should return (5+3)*2 = 16
}