int main() {
    int mask = 32;
    int result = 0;
    
    while(mask > 0) {
        result = result | mask;
        mask = mask /2;
    }
    
    return result;
}