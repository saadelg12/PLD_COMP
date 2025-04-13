int calculate(int x) {
    return x + 10;
}

int main() {
    int a = 13;
    int b = 7;
    
    int result = calculate(a & b);
    
    return result;
}