int add(int x, int y) {
    return x + y;
}

int multiply(int x, int y) {
    return x * y;
}

int main() {
    int (*operation)(int, int);
    
    operation = add;
    int result = operation(5, 3);  
    
    {
        operation = multiply;
        result = operation(result, 2);  
    }
    
    result = operation(result, 3);  
    
    return result;  
}