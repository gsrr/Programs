#include <stdio.h>
#include <stdlib.h>

void swap(int* arr , int i)
{
        int temp = arr[i];
        arr[i] = arr[i+1];
        arr[i+1] = temp;
}

int bubble_sort(int *arr, int n)
{
        int cnt = 0;
        int i, j;
        for( i = 0 ; i < n ; i++)
        {
                int s = 0;
                for( j = 0 ; j < n - 1 - i ; j++)
                {
                        if(arr[j] > arr[j + 1])
                        {
                                swap(arr , j);
                                s++;
                                cnt++;
                        }
                }
                if(s == 0)
                {
                        break;
                }
        }
        return cnt;
}


int insert_sort(int *arr, int i)
{
        int value = arr[i];
        int cnt = 0;
        int index = bin_search(arr , );
        while( index > 0)
        {
                if(arr[index - 1] > value)
                {
                        arr[index] = arr[index-1];
                                cnt++;
                }
                else
                {
                        break;
                }
                index--;

        }
        arr[index] = value;
        return cnt;
}
int main()
{
        int n;
        int *arr;
        while(scanf("%d", &n) != EOF)
        {
                if( n == 0 )
                {
                        break;
                }
                arr = (int * )malloc(sizeof(int) * n);
                int m = 0;
                int i = 0;
                for(i = 0 ; i < n ; i++)
                {
                        scanf("%d", &arr[i]);
                        m += insert_sort(arr, i); 
                }
                
                printf("%d\n", m);
                free(arr);

                
        }
        return 0;
}
