int main() {
    int counter = 0;
    int result = 42;
    
    while(counter > 0) {
        result = result + 1;
        counter = counter - 1;
    }
    
    return result;
}