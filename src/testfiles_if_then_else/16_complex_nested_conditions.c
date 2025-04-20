int main() {
    int a = 5;
    int b = 10;
    int c = 15;
    int result = 0;
    
    if(a < b) {
        if(b < c) {
            if(a + b > c) {
                result = 1;
            } else {
                result = 2;
            }
        } else {
            result = 3;
        }
    } else {
        if(a > c) {
            result = 4;
        } else {
            result = 5;
        }
    }
    
    return result;
}