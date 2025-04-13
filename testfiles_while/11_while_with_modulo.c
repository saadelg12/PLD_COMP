int main() {
    int num = 100;
    int sum = 0;
    
    while(num > 0) {
        if(num % 3 == 0) {
            sum = sum + num;
        }
        num = num - 1;
    }
    
    return sum;
}