int main() {
    int a = 0;
    int b = 1;
    int i = 0;
    int n = 7;

    while (i < n) {
        int temp = b;
        b = a + b;
        a = temp;
        i = i + 1;
    }

    return a;
}
