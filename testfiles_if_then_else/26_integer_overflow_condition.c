int main() {
    int a = 2147483647;  // Maximum value for 32-bit signed int
    int result = 0;
    
    // Test condition with potential integer overflow
    if(a + 1 > 0) {
        result = 1;  // Should be false due to overflow
    } else {
        result = 2;
    }
    
    return result;
}