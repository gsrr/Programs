#include <stdio.h>
#include <stdlib.h>


int main()
{
        int p[8] = {9, 8, 7, 6, 5, 4, 3, 2};
        int t;
        scanf("%d", &t);
        while(t--)
        {
                int n;
                scanf("%d", &n);
                if(n == 1)
                {
                        printf("1\n");
                        continue;
                }

                int nums[8] = {0};
                for(int i = 0 ; i < 8 ; i++)
                {
                        while(n % p[i] == 0)
                        {
                                nums[p[i] - 2]++;
                                n = n / p[i];
                        }
                }
                if( n != 1 )
                {
                        printf("-1\n");
                }
                else
                {
                        for(int i = 0 ; i < 8 ; i++)
                        {
                                while(nums[i] != 0)
                                {
                                        printf("%d", i+2);
                                        nums[i]--;
                                }
                        }
                        printf("\n");
                }

        }
        return 0;
}
