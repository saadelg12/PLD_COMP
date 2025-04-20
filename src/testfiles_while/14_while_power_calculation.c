int main() {
    int base = 2;
    int exponent = 5;
    int result = 1;
    
    while(exponent > 0) {
        result = result * base;
        exponent = exponent - 1;
    }
    
    return result;
}