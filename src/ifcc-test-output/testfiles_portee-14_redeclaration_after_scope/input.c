int main() {
    int a = 10;
    int result = a;
    
    {
        int b = 20;
        result = result + b;
    }
    

    int b = 30;
    result = result + b;
    
    {

        int b = 5;
        result = result + b;
    }
    
    return result; 
}