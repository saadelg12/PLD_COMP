int calculate(int x, int y) {
    int result = x * y;
    {
        int x = 5;
        result = result + x;
    }
    return result;
}

int main() {
    int x = 10;
    int y = 3;
    int result = calculate(x, y);
    
    return result;
}
