int add(int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}

int mul(int a, int b) {
    return a * b;
}

int divide(int a, int b) {
    return a / b;
}

int mod(int a, int b) {
    return a % b;
}

int main() {
    int a = 9;
    int b = 12;
    int op = '+';

    int res;


    if(op == '+') {
        res = add(a, b);
    }
    if(op == '-') {
        res = sub(a, b);
    }
    if(op == '*') {
        res = mul(a, b);
    }
    if(op == '/') {
        res = divide(a, b);
    }
    if(op == '%') {
        res = mod(a, b);
    }


    return res;
}