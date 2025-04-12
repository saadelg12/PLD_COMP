int main() {
    int n = 1;
    int sum = 0;
    int product = 1;
    
    while(n < 6) {
        product = product * n;
        sum = sum + product;
        n = n + 1;
    }
    
    return sum;  
}