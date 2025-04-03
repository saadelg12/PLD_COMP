int main() {
    int a = 5;
    int b = 10;
    int c = 15;
    int result = 0;
    
    if (a < b) {
        int temp1 = a;
        int temp2 = b;
        result = 1;
        
        {
            int nested1 = temp1;
            int nested2 = temp2;
            if (nested1 < nested2) {
                int inner1 = nested1;
                int inner2 = nested2;
                result = result + 10;
                
                {
                    int deep1 = inner1;
                    int deep2 = inner2;
                    if (deep1 < deep2) {
                        int deeper1 = deep1;
                        int deeper2 = deep2;
                        result = result + 5;
                    } else {
                        int deeper3 = deep1;
                        int deeper4 = deep2;
                        result = result + 3;
                    }
                }
            } else {
                int inner3 = nested1;
                int inner4 = nested2;
                result = result + 2;
            }
        }
    } else {
        int temp3 = a;
        int temp4 = b;
        result = 2;
        
        {
            int nested3 = temp3;
            int nested4 = temp4;
            if (nested3 < nested4) {
                int inner5 = nested3;
                int inner6 = nested4;
                result = result + 1;
            } else {
                int inner7 = nested3;
                int inner8 = nested4;
                
                {
                    int deep3 = inner7;
                    int deep4 = inner8;
                    if (deep3 < deep4) {
                        int deeper5 = deep3;
                        int deeper6 = deep4;
                        result = result + 4;
                    } else {
                        int deeper7 = deep3;
                        int deeper8 = deep4;
                        result = result + 6;
                    }
                }
            }
        }
    }
    
    {
        int final1 = a;
        int final2 = b;
        if (final1 < final2) {
            int last1 = final1;
            int last2 = final2;
            result = result + 7;
        } else {
            int last3 = final1;
            int last4 = final2;
            
            {
                int verylast1 = last3;
                int verylast2 = last4;
                if (verylast1 < verylast2) {
                    result = result + 8;
                } else {
                    result = result + 9;
                }
            }
        }
    }

    return result;
}