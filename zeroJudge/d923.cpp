#include<stdio.h>
#include<stdlib.h>

int findAns(int i, int j)
{
        long long t = 2;
        long long Ans = 0;
        while(t < i || t < j) {
                t *= 2;
        }
        if(i == 1 && j == 1) 
        {
               return ++Ans;
        }
        if(t / 2 >= i && t / 2 < j)
        {
                j = j - t/2;
                return findAns(i, j) + (t * t / 2);
        }
        else if(t / 2 < i && t / 2 < j)
        {
                i -= t / 2;
                j -= t / 2;
                return findAns(i, j) + (t * t / 4);
        }
        else
        {
                i -= t / 2;
                return findAns(i, j) + (t * t / 4 * 3);
        }


}

int main() {
        int i, j;
        while(scanf("%d %d", &i, &j) == 2) {
                printf("%lld\n", findAns(i, j));
        }
        return 0;
}
