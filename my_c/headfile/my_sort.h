#include <stdio.h>

/* myHead : displayArr : start */
void displayArr(int arr[], int len)
{
        for(int i = 0 ; i < len ; i++)
        {
                printf("%d ", arr[i]);
        }
        printf("\n");
}
/* myHead : displayArr : end */

/* myHead : insertion_sort : start */
void insertion_sort(int arr[], int index)
{
        int value = arr[index];
        int i;
        for( i = index ; i > 0 ; i-- )
        {
                if(arr[i-1] > value)
                {
                        arr[i] = arr[i-1];
                }
                else
                {
                        break;
                }
                
        }
        arr[i] = value;

}
/* myHead : insertion_sort : end */
