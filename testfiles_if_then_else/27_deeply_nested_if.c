int main() {
    int a = 5;
    int b = 10;
    int c = 15;
    int d = 20;
    int e = 25;
    int result = 0;
    
    // Testing extremely deep nesting that might challenge the compiler
    if(a < b) {
        if(b < c) {
            if(c < d) {
                if(d < e) {
                    if(a + b > c) {
                        if(b + c > d) {
                            if(c + d > e) {
                                result = 1;
                            } else {
                                result = 2;
                            }
                        } else {
                            result = 3;
                        }
                    } else {
                        result = 4;
                    }
                } else {
                    result = 5;
                }
            } else {
                result = 6;
            }
        } else {
            result = 7;
        }
    } else {
        result = 8;
    }
    
    return result;
}