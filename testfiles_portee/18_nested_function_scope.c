int outer(int a) {
    int b = a * 2;
    
    int inner(int c) {
        int d = b + c;
        return d;
    }
    
    return inner(a + 1);
}

int main() {
    int x = 5;
    int result = outer(x);
    
    return result;
}
