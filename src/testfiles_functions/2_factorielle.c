int factorielle(int a) {
   int c;
   if(a == 0) {
      c = 1;
   } else {
      c= a * factorielle(a - 1);
   }
   return c;
}

int main() {
    int a = 10;
    int b= factorielle(a);
    return b;
}

