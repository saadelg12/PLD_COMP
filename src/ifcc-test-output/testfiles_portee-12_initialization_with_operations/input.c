int main() {
    int a = 5;
    int b = 10;
    int result = a + b;
    {
        int c = result * 2;  
        {
            int d = c - a;   
            result = d / b;  
        }
        result = result + c; 
    }
    return result;
}