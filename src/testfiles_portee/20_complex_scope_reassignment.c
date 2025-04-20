int main() {
    int result = 1;
    int x = 2;
    

    int y;
    
    {
        int z = 3;
        result = result * z; 
        
        x = x * 2;          
        y = x + z;         
        
        {
            int x = 5;     
            int w = 6;
            
            result = result + x; 
            y = y + w;           
        }
        
        result = result * x;     
    }
    

    result = result + y;   
    
    return result;          
}