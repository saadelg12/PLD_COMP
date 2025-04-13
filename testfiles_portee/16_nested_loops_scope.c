int main() {
    int sum = 0;
    int i = 0;
    
    while (i < 3) {
        int j = 0;
        int temp = i * 10;
        
        while (j < 2) {
            int value = temp + j;
            sum = sum + value;
            j = j + 1;
        }
        
        i = i + 1;
    }
    
    return sum;
}
