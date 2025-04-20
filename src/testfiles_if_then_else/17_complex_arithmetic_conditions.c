int main() {
    int a = 5;
    int b = 10;
    int c = 15;
    int result = 0;
    
    if((a + b) * 2 > c + a) {
        result = 42;
    } else {
        result = 24;
    }
    
    return result;
}