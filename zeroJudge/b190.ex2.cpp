#include <cstdio>

int cnt = 0;

void f(int n, int from, int to)
{
        if(n <= 0)
                return ;

        f(n - 1, from, 6 - from - to);
        printf("ring %d : %c -> %c\n", n, 'a' + from - 1, 'a' + to - 1);
        cnt++;
        f(n - 1, 6 - from - to, to);
}

int main()
{
        int n;
        while(scanf("%d", &n) != EOF)
        {
                cnt = 0;
                int from = 1;
                for(int i=n; i>0; i--)
                {
                        if(i % 2 == 0 && from != 3)
                        {
                                f(i - 1, from, 6 - from - 3);
                                printf("ring %d : %c -> %c\n", i, 'a' + from - 1, 'a' + 3 - 1);
                                cnt++;
                                from = 6 - from - 3;
                        }
                        else if(i % 2 == 1 && from != 2)
                        {
                                f(i - 1, from, 6 - from - 2);
                                printf("ring %d : %c -> %c\n", i, 'a' + from - 1, 'a' + 2 - 1);
                                cnt++;
                                from = 6 - from - 2;
                        }
                }
                printf("move steps: %d\n", cnt);
        }

        return 0;
}
