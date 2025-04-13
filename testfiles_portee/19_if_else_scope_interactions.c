int main() {
    int x = 10;
    int result = 0;
    
    if (x > 5) {
        int y = 20;
        
        if (y > 10) {
            int z = 30;
            result = x + y + z; // 10 + 20 + 30 = 60
        } else {
            int z = 40;
            result = x + y - z; // Not executed
        }
        
        // z is out of scope here
        result = result - y; // 60 - 20 = 40
    } else {
        int y = 50;
        result = x * y; // Not executed
    }
    
    // y is out of scope here
    result = result + x; // 40 + 10 = 50
    
    return result; // Should return 50
}