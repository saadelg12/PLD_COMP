int main() {
    int a = 5;
    int b = 10;
    int c = 15;
    int result = 0;

    if (a < b) {
        result = 1;
        
        {
            int nested = a + b;
            if (nested > c) {
                result =result + 10;
            } else {
                result =result + 5;
            }
        }
    } else {
        result = 2;
    }

    
    return result;
}