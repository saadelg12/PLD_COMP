int main() {
    int choice = 2;
    int result = 0;
    
    switch (choice) {
        case 1:
            int x = 10;
            result = x;
            break;
        case 2:
            int x = 20;
            {
                int y = 5;
                result = x + y; 
            }
            result = result * 2; 
            break;
        case 3:
            int y = 30; 
            result = y;
            break;
        default:
            int z = 40;
            result = z;
    }
    
    return result; 
}