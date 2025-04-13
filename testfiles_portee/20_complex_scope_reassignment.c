int main() {
    int result = 1;
    int x = 2;
    
    // Forward declaration
    int y;
    
    {
        int z = 3;
        result = result * z; // 1 * 3 = 3
        
        // Reassign x from outer scope
        x = x * 2;          // 2 * 2 = 4
        
        // Assign to forward-declared y
        y = x + z;          // 4 + 3 = 7
        
        {
            int x = 5;      // Shadows outer x
            int w = 6;
            
            result = result + x; // 3 + 5 = 8
            y = y + w;           // 7 + 6 = 13
        }
        
        // x is still 4 (not the shadowed 5)
        result = result * x;     // 8 * 4 = 32
    }
    
    // z and w are out of scope here
    // y is still in scope as it was declared at this level
    result = result + y;   // 32 + 13 = 45
    
    return result;          // Should return 45
}