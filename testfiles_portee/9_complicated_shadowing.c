int main() {
    int x = 10;
    {
        int x = 20;
        {
            int x = 30;
            x = x + 1;
            {
                int x = 40;
                x = x * 2;
                {
                    int x = 50;
                    x = x - 3;
                    {
                        int x = 60;
                        x = x % 7;
                        {
                            int x = 70;
                            x = x / 2;
                            {
                                int x = 80;
                                {
                                    int x = 90;
                                    {
                                        int x = 100;
                                        return x;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}