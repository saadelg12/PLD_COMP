int main() {
    int a = 5;
    int result = 0;
    
    if(a > 0) {
        int b = 10;  // Variable declared inside if block
        result = a + b;
    } else {
        int b = 20;  // Different variable with same name in else block
        result = a - b;
    }
    
    // b should not be accessible here
    
    return result;
}