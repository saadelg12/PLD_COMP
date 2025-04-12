int main() {
    int i = 5;
    int j = 0;
    int result = 0;
    
    while(i > 0) {
        j = i;
        while(j > 0 & result < 15) {
            result = result + 1;
            j = j - 1;
        }
        i = i - 1;
    }
    
    return result;  
}