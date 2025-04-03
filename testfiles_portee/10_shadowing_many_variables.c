int main() {
    int a = 1;
    int b = 2;
    int c = 3;
    {
        int x = a + b;
        int y = b * c;
        int z = c - a;
        x = x | y;
        y = y & z;
        z = z ^ x;
        {
            int a = x < 1;
            int b = y > 1;
            int c = z % 5;
            a = a + b - c;
            b = b * c / a;
            c = (c | a) & b;
            {
                int x = a;
                int y = !b;
                int z = -c;
                x = x & y | z;
                y = y ^ z & x;
                z = z | x ^ y;
                {
                    int p = a + x;
                    int q = b + y;
                    int r = c + z;
                    p = p % q;
                    q = q / r;
                    r = r * p;
                    {
                        int m = p ^ q;
                        int n = q & r;
                        int o = r | p;
                        m = m < n;
                        n = n > o;
                        o = o & m;
                        {
                            int x = m + n;
                            int y = n - o;
                            int z = o * m;
                            x = x / y;
                            y = y % z;
                            z = z & x;
                            return z;
                        }
                    }
                }
            }
        }
    }
}