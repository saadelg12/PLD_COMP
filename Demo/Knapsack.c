int knapsack(int w1, int v1, int w2, int v2, int W) {
    int res = 0;

    if (w1 <= W) {
        res = v1;
    }

    if (w2 <= W) {
        if (v2 > res) {
            res = v2;
        }
    }

    if (w1 + w2 <= W) {
        if (v1 + v2 > res) {
            res = v1 + v2;
        }
        res = v1 + v2;
    }

    return res;
}

int main() {
    int result = knapsack(3, 40, 4, 50, 7);
    return result;
}