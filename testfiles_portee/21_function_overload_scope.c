int calculate(int x) {
    return x * 2;
}

int main() {
    int result = 0;
    int calculate = 5; // Variable with same name as function
    
    result = calculate; // Uses the variable, not the function
    
    {
        result = result + calculate(3); // Uses the function, not the variable
    }
    
    return result; // Should return 5 + 6 = 11
}