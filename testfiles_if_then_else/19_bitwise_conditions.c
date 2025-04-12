int main() {
    int a = 5;    // 0101 in binary
    int b = 3;    // 0011 in binary
    int result;
    
    if(a & b) {  // bitwise AND: 0101 & 0011 = 0001 (1 in decimal, which is true)
        result = 100;
    } else {
        result = 200;
    }
    
    return result;
}