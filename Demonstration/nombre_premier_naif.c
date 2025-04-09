int main() {
    int n = 13;
    int i = 2;
    int isPrime = 1;

    while (i < n) {
        if (n % i == 0) {
            isPrime = 0;
        }
        i = i + 1;
    }

    return isPrime;
}
