int main() {
    int sum = 0;
    int i = 0;
    
    while (i < 3) {
        int j = 0;
        int temp = i * 10;
        
        while (j < 2) {
            // Access outer loop variables
            int value = temp + j;
            sum = sum + value;
            j = j + 1;
        }
        
        i = i + 1;
        // j is out of scope here
    }
    
    return sum; // Should return (0+0) + (0+1) + (10+0) + (10+1) + (20+0) + (20+1) = 62
}