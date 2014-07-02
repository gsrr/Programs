#include <stdio.h>


int answer(int n , int k , int m, int r) 
{
        if (n == r)
        {
                return (k - 1) % n;
        }
        else
        {
                return (answer(n-1, k, m, r) + k) % n;
        }
}

int main() 
{
        int t, tc;
        int n, k, m;
        scanf("%d", &t);
        for (tc = 1; tc <= t; tc++) 
        {
                scanf("%d%d%d", &n, &k, &m);
                int r = n + 1 - m;
                printf("Case %d: %d\n", tc, answer(n, k , m, r) + 1);
        }
}
