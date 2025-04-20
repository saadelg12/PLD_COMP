int function(int a, int b) {
    int c = a + b;
    return c;
}

int main() {
    int a = 10;
    int b= function(a , a, a);
    return b;
}