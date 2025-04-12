int main() {
    int a = 10;
    int result = 0;
    
    // Test consecutive if statements with different conditions
    if(a > 5) {
        result = result+ 1;
    }
    
    if(a < 15) {
        result = result + 2;
    }
    
    if(a == 10) {
        result = result + 4;
    }
    
    if(a != 20) {
        result = result + 8;
    }
    
    return result;  // Should return 15 (1+2+4+8)
}