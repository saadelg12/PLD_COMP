int main() {
    int a = 15;
    int result;
    
    // Testing if-else chain structure
    if(a < 10) {
        result = 1;
    } else {
        if(a < 20) {
            result = 2;
        } else {
            if(a < 30) {
                result = 3;
            } else {
                result = 4;
            }
        }
    }
    
    return result;
}