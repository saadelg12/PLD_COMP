int add(int x, int y) {
    return x + y;
}

int multiply(int x, int y) {
    return x * y;
}

int main() {
    // Declare a function pointer
    int (*operation)(int, int);
    
    // Assign add function to the pointer
    operation = add;
    int result = operation(5, 3);  // result = 8
    
    {
        // Inside a new scope, change the function
        operation = multiply;
        result = operation(result, 2);  // result = 16
    }
    
    // Operation still points to multiply after the scope ends
    result = operation(result, 3);  // result = 48
    
    return result;  // Should return 48
}