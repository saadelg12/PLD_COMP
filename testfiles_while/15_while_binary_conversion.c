int main() {
    int decimal = 42;
    int binary = 0;
    int place = 1;
    
    while(decimal > 0) {
        binary = binary + (decimal % 2) * place;
        decimal = decimal / 2;
        place = place * 10;
    }
    
    return binary;
}