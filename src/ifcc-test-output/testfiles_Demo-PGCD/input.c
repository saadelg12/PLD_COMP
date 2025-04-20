int pgcd(int a, int b) {
    while(b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int x = 1071;
    int y = 462;
    int res = pgcd(x, y);
    return res;
}