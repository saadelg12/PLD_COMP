// filepath: c:\Users\Admin\source\repos\COMP-SAAD\testfiles_while\6_nested_while_complex_condition.c
int main() {
    int i = 5;
    int j = 0;
    int result = 0;
    
    while(i > 0) {
        j = i;
        while(j > 0 && result < 15) {
            result = result + 1;
            j = j - 1;
        }
        i = i - 1;
    }
    
    return result;  // Should return 15 (loop stops when result reaches 15)
}