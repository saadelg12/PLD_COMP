int main() {
    int x = 10;
    int result = 0;
    
    if (x > 5) {
        int y = 20;
        
        if (y > 10) {
            int z = 30;
            result = x + y + z;
        } else {
            int z = 40;
            result = x + y - z;
        }
        
        result = result - y;
    } else {
        int y = 50;
        result = x * y;
    }
    
    result = result + x;
    
    return result;
}
