int main() {
    int a = 48;
    int b = 18;
    int temp;
    
    while(b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    
    return a;
}