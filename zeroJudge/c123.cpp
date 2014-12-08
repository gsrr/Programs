#include <stdio.h>
#include <stdlib.h>


int main()
{
        int n;
        while(scanf("%d", &n))
        {
                if( n == 0 )
                {
                        break;
                }
                int *arr = (int*)malloc(sizeof(int) * n);
                int m;
                while(1)
                {
                        int i;
                        int j = 1;
                        int top = -1;
                        for( i = 0 ; i < n ; i++)
                        {
                                scanf("%d", &m);
                                if(m == 0)
                                {
                                        break;
                                }
                                for( j ;  j <= n+1 ;)
                                {
                                        if(top == -1)
                                        {
                                                arr[++top] = j;
                                                j++;
                                        }
                                        else
                                        {
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
                        }
                        if(m == 0)
                        {
                                break;
                        }
                        if(top == -1)
                        {
                                printf("Yes\n");
                        }
                        else
                        {
                                printf("No\n");
                        }
                }
                free(arr);
                printf("\n");
        }
        return 0;
}
