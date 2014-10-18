#include <stdio.h>
#include <stdlib.h>


int main()
{
        int n;
        while(scanf("%d", &n))
        {
                printf("n:%d\n",n);
                if( n == 0 )
                {
                        break;
                }
                int *arr = (int*)malloc(sizeof(int) * n);
                int top = -1;
                int m;
                while(1)
                {
                        int i;
                        int j = 1;
                        for( i = 0 ; i < n ; i++)
                        {
                                scanf("%d", &m);
                                if(m == 0)
                                {
                                        break;
                                }
                                for( j ;  j <= n ;)
                                {
                                        if(top == -1)
                                        {
                                                arr[++top] = j;
                                                j++;
                                        }
                                        if(m == arr[top])
                                        {
                                                top--;
                                                break;
                                        }
                                        else
                                        {
                                                arr[++top] = j;
                                                j++;
                                        }
                                }

                        }
                        if(top == -1)
                        {
                                printf("Yes\n");
                        }
                        else
                        {
                                printf("No\n");
                        }
                        if(m == 0)
                        {
                                break;
                        }
                }
                printf("\n");
        }
        return 0;
}
