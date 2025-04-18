int calculate(int x) {
    return x * 2;
}

int main() {
    int result = 0;
    int calculate = 5; 
    
    result = calculate; 
    
    {
        result = result + calculate(3);
    }
    
    return result; 
}