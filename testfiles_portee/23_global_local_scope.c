int globalVar = 10;

int modifyGlobal() {
    int localVar = 5;
    globalVar = globalVar + localVar;
    return globalVar;
}

int main() {
    int result = 0;
    int globalVar = 20; // Shadows the global variable
    
    result = globalVar; // Uses the local variable (20)
    
    {
        result = result + modifyGlobal(); // Global var becomes 10+5=15
    }
    
    result = result + globalVar; // Uses the local variable again (20)
    
    return result; // Should return 20 + 15 + 20 = 55
}