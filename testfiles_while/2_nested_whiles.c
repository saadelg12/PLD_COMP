int main() {
    int a = 4;
    int b= 0;
    int c = 0;

    while(a>0){
        b = b+1;
        a  = a-1;
        while(b>0){
            c= c+1;
            b= b-1;
        }
    }
    
    return c;
}
