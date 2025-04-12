int main() {
    int a = 10;
    int result = 0;
    
    // Test multiple nested conditions with alternating true/false patterns
    if(a > 5) {
        if(a > 20) {
            result = 1;
        } else {
            if(a > 8) {
                if(a > 15) {
                    result = 2;
                } else {
                    result = 3;
                }
            } else {
                result = 4;
            }
        }
    } else {
        result = 5;
    }
    
    return result;
}