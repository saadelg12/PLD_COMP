int main() {
    int x = 5;
    int y = 10;
    int z = 15;
    
    {
        int a = x * 2;
        int b = y - 3;
        
        {
            int c = z / x;
            int y = a + b;
            
            z = x + y + c;
            
            {
                int x = c * 2;
                y = y + x;
                
                int result = x + y + z;
                z = result - a;
            }
            
            y = y + 1;
        }
        
        z = z + y;
    }
    
    return z;
}