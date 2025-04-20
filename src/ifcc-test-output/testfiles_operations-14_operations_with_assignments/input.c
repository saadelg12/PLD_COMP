int main() {
    int a = 10;
    int b = 5;
    int c;
    
    c = a;
    a = a + b;
    b = b * 2;
    
    return a + b - c;
}