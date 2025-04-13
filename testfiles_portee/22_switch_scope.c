int main() {
    int choice = 2;
    int result = 0;
    
    switch (choice) {
        case 1:
            int x = 10;
            result = x;
            break;
        case 2:
            int x = 20; // Different scope than the x in case 1
            {
                int y = 5;
                result = x + y; // 20 + 5 = 25
            }
            result = result * 2; // 25 * 2 = 50
            break;
        case 3:
            int y = 30; // Different scope than the y in case 2
            result = y;
            break;
        default:
            int z = 40;
            result = z;
    }
    
    return result; // Should return 50
}