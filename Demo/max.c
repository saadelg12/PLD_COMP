int findMax(int n1, int n2, int n3, int n4, int n5) {
    int max = n1;
    if (n2 > max) {
        max = n2;
    }
    if (n3 > max) {
        max = n3;
    }
    if (n4 > max) {
        max = n4;
    }
    if (n5 > max) {
        max = n5;
    }
    return max;
}

int main() {
    int n1 = 1;
    int n2 = 5;
    int n3 = 3;
    int n4 = 9;
    int n5 = 2;
    return findMax(n1, n2, n3, n4, n5);
}