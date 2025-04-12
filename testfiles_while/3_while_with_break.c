// filepath: c:\Users\Admin\source\repos\COMP-SAAD\testfiles_while\3_while_with_break.c
int main() {
    int a = 10;
    int sum = 0;
    
    while(a > 0) {
        sum = sum + a;
        a = a - 1;
        
        if(sum > 30) {
            break;  // Exit the loop when sum exceeds 30
        }
    }
    
    return sum;  // Should return 10+9+8+7=34
}