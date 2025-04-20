int main() {
    int count = 0;
    int sum = 0;
    int max = 100;
    
    while(count < 20 &  sum < max) {
        count = count + 1;
        sum = sum + count * count;
        
        if(sum % 17 == 0) {
            sum=max;
        }
    }
    
    return sum;
}