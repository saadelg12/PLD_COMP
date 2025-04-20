int main() {
    int a = 17;
    int b = 5;
    int quotient;
    int remainder;
    int result;
    
    quotient = a / b;
    remainder = a % b;
    result = quotient * b + remainder;
    
    return result == a;
}