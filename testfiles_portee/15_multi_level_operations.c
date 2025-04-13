int main() {
    int x = 5;
    int y = 10;
    int z = 15;
    
    {
        int a = x * 2;      // a = 10
        int b = y - 3;      // b = 7
        
        {
            int c = z / x;  // c = 3
            int y = a + b;  // y shadows outer y, y = 17
            
            z = x + y + c;  // z = 5 + 17 + 3 = 25 (using shadowed y)
            
            {
                int x = c * 2;  // x shadows outer x, x = 6
                y = y + x;      // y = 17 + 6 = 23 (both are shadowed)
                
                int result = x + y + z;  // result = 6 + 23 + 25 = 54
                z = result - a;          // z = 54 - 10 = 44
            }
            
            y = y + 1;      // y = 24 (still shadowed, not outer y)
        }
        
        z = z + y;          // z = 44 + 10 = 54 (using original y, not shadowed)
    }
    
    return z;  // Should return 54
}