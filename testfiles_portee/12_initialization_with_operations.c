int main() {
    int a = 5;
    int b = 10;
    int result = a + b;
    {
        int c = result * 2;  // c = 30
        {
            int d = c - a;   // d = 25
            result = d / b;  // result = 2
        }
        result = result + c; // result = 32
    }
    return result;
}