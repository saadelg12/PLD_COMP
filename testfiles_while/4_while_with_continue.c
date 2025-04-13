// filepath: c:\Users\Admin\source\repos\COMP-SAAD\testfiles_while\4_while_with_continue.c
int main() {
    int a = 10;
    int sum = 0;
    
    while(a > 0) {
        a = a - 1;
        
        if(a % 2 == 0) {
            continue;  // Skip even numbers
        }
        
        sum = sum + a;  // Only add odd numbers
    }
    
    return sum;  // Should return 9+7+5+3+1=25
}