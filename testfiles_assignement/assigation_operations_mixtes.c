int main() {
    int a;
    int b = 5;
    int c = 3;
    a = (b + c) * (b - c) & (b | c);
    return a;
}