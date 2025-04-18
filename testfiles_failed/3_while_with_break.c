int main() {
    int a = 10;
    int sum = 0;
    
    while(a > 0) {
        sum = sum + a;
        a = a - 1;
        
        if(sum > 30) {
            break;  
        }
    }
    
    return sum;  
}