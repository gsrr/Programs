#include <stdio.h>
int f(int m,int n, int mod)
{
        long long int mul = m;
        long long int r = 1;
        while(n){
                if(n % 2 == 1){r *= mul;r %= mod;}
                mul *= mul;
                mul %= mod;
                n >>= 1;
        }
        return r;
}


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
        int B,P,M;
        while(scanf("%d%d%d",&B,&P,&M)==3)
                printf("%d\n",f2(1, B, P, M));
        return 0;
}
