int main() {
    int n = 1;
    int sum = 0;
    int sign = 1;
    
    while(n <= 10) {
        sum = sum + sign * n;
        sign = sign * -1;
        n = n + 1;
    }
    
    return sum;
}