
#include <stdio.h>

int f2(int residual, int b,int p, int m)
{
        if(p == 0)
        {
                return residual;
        }


        if(p % 2 == 1)
        {
                int tmp_r  = ((residual % m) * (b % m)) % m;
                return f2(tmp_r, b, p-1, m);
        }
        else
        {
                int tmp_b = ((b % m) * (b % m)) % m;
                return f2(residual,tmp_b, p/2, m);
        }
}
int main()
{
        int B,P;
        while(scanf("%d%d",&B,&P) == 2)
        {
                printf("%d\n",f2(1, B, P, 10007));
        }
        return 0;
}
