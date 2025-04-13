int main() {
    int a = 10;
    int result = a;
    
    {
        int b = 20;
        result = result + b;
    }
    
    // b's scope has ended, so we can declare a new b
    int b = 30;
    result = result + b;
    
    {
        // We can even shadow the outer b
        int b = 5;
        result = result + b;
    }
    
    return result; // Should return 10 + 20 + 30 + 5 = 65
}