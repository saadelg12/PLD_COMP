int main() {
    int base = 2;
    int exp = 5;
    int result = 1;

    while (exp > 0) {
        result = result * base;
        exp = exp - 1;
    }

    return result;
}