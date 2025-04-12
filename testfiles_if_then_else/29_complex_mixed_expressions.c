int main() {
    int a = 5;
    int b = 10;
    int c = 15;
    int result = 0;
    
    // Testing complex expressions with mixed operators
    if((a + b > c) & (b - a < c) | (c / a == 3)) {
        if(!(a >= b) & (c % a == 0)) {
            result = 42;
        } else {
            result = 24;
        }
    } else {
        result = 100;
    }
    
    return result;
}