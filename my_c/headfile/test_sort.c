#include "my_sort.h"
#include <stdio.h>


int main()
{
        int arr[5] = {5, 4, 3, 2, 1};
        int i;
        for(i = 0 ; i < 5 ; i++)
        {
                insertion_sort(arr, i); 
        }
        displayArr(arr, 5);
        return 0;
}

