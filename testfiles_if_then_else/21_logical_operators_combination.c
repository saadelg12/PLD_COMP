int main() {
    int a = 5;
    int b = 0;
    int c = 15;
    int result;
    
    // Test logical operators in combination (!b is true, a<c is true)
    if(!b & a < c) {
        result = 42;
    } else {
        result = 24;
    }
    
    return result;
}