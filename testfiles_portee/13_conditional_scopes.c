int main() {
    int a = 1;
    int result = 0;
    
    if (a > 0) {
        int b = 10;
        result = b;
        {
            int c = 20;
            if (b > 5) {
                result = result + c;
            }
        }
    } else {
        int b = 30;
        result = b;
    }
    
    return result; // Should return 30 (10 + 20)
}