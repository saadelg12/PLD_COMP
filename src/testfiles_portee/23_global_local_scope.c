int globalVar = 10;

int modifyGlobal() {
    int localVar = 5;
    globalVar = globalVar + localVar;
    return globalVar;
}

int main() {
    int result = 0;
    int globalVar = 20; 
    
    result = globalVar; 
    
    {
        result = result + modifyGlobal(); 
    }
    
    result = result + globalVar; 
    
    return result;