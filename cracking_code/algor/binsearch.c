
/*
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>


int binsearch(int* arr, int s, int e, int key)
{
        if(s > e)
        {
                return -1;
        }
        int mid = (s + e) / 2;
        if(key > arr[mid])
        {
                return binsearch(arr, mid+1, e, key);
        }
        else if(key < arr[mid])
        {
                return binsearch(arr, s, mid-1, key);
        }
        else
        {
                return mid;
        }
} 

int main()
{
        int num = 7;
        int arr[] = {11, 22, 33, 44, 55, 66, 77};
        int ret = binsearch(arr, 0, num-1, 77);
        if(ret < 0)
        {
                printf("Can not find...\n");
        }
        else
        {
                printf("Position:%d\n", ret);
        }

        return 0;
}

