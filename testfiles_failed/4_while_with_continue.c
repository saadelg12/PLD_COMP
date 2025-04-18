int main() {
    int a = 10;
    int sum = 0;
    
    while(a > 0) {
        a = a - 1;
        
        if(a % 2 == 0) {
            continue;  
        
        sum = sum + a;  
    }
    
    return sum;  
}
}