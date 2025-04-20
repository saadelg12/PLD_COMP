int main() {
    int x = 10;
    int y = 0;
    int z = 0;
    int flag = 0;

    while(x > 0) {
        int temp = x;
        y = 0;
        
        while(temp > 0) {
            if(flag == 0) {
                y = y + 1;
                temp = temp - 1;
                
                if(y % 2 == 0) {
                    z = z + 1;
                } else {
                    z = z + 2;
                }
            } else {
                y = y + 2;
                temp = temp - 2;
                
                if(y % 3 == 0) {
                    z = z + 3;
                } else {
                    z = z + 4;
                }
            }
        }

        if(z > 15) {
            flag = 1;
        }

        x = x - 1;
    }

    return z;
}