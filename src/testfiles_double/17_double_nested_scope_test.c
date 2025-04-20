int main() {
    double x = 5.5;
    {
        double x = 2.5;
        double y = 3.5;
        x = x + y;
    }
    return x == 5.5;
}