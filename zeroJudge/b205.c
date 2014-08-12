#include <stdio.h>

int main()
{
        int A[4] = {27, 9, 3, 1};
        int n;
        while(scanf("%d", &n) != EOF)
        {
                for(int i = 0 ; i < n ; i++)
                {
                        int p;
                        int q = 0;
                        scanf("%d", &p);
                        int sum = 0;
                        for(int j = 0 ; p != 0 ; j++)
                        {
                                q = p / A[j];
                                p = p % A[j];
                                sum = sum + q;
                        }
                        printf("%d\n", sum);
                }
        }
        return 0;              
}
