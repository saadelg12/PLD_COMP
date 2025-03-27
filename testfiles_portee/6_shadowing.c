int main() {
    int a=3;
    int b =4;
    {
        int a = 7;
        b = a;
    }
    return b;
}
