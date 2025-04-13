int calculate(int x, int y) {
    int result = x * y;
    {
        // Shadow parameter
        int x = 5;
        result = result + x; // result = (x param * y) + 5
    }
    return result;
}

int main() {
    int x = 10;
    int y = 3;
    int result = calculate(x, y);
    
    return result; // Should return (10 * 3) + 5 = 35
}