#include <stdio.h>
#include <math.h>


void insertion_sort(int arr[] , int n, int cnt)
{
        int index = cnt - 1;
        for(int i = cnt - 1 ; i > 0 ; i--)
        {
                if(n < arr[i-1])
                {
                        arr[index--] = arr[i-1];
                }
                else
                {
                        break;
                }
        }
        arr[index] = n;
}

int main()
{
        int arr[10000];

        int n;
        int cnt = 0;
        while(scanf("%d", &n) != EOF)
        {
                cnt++;
                insertion_sort(arr, n, cnt);
                if(cnt % 2 == 0)
                {
                        printf("%d\n", (arr[cnt/2 - 1] + arr[cnt/2])/2);             
                }
                else
                {
                        printf("%d\n", arr[cnt/2]);
                }


                
        }
        return 0;
}
