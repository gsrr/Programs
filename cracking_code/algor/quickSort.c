
/*
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>







/* ::#def myrand :: */
typedef struct{
        int base;
        int cust;
}f_args;

int myrand_base(int base)
{
        return rand() % base;
}

int var_f(f_args in)
{
        int base = in.cust ? in.cust : in.base;
        return myrand_base(base);
}

/*
* varadic macros
*/
#define myrand(...) var_f((f_args){.base=1000,__VA_ARGS__});


/* #end */


/* ::#def array :: */
#define INT 101
#define CHAR 102

void* createArr(int num, int type)
{
        srand(time(NULL));
        if(type == INT)
        {
                int* tmp = (int*)malloc(sizeof(int)* num);
                int i;
                for( i = 0 ; i < num ; i++)
                {
                        tmp[i] = myrand(100);
                        //sleep(1);
                } 
                return tmp;
        }

}

void print_arr(int* arr, int num)
{
        int i;
        for( i = 0 ; i < num ; i++)
        {
                printf("%d ", arr[i]);
        }
        printf("\n");
}

/* #end */

void swap(int* arr, int i, int j)
{
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
}

int arrange(int* arr, int s, int e)
{
        int key = arr[s];
        int i = s + 1;
        int j = e - 1;
        while(1)
        {
                while( arr[i] < key && i < j)
                {
                        i++;
                }
                while( arr[j] > key && i < j)
                {
                        j--;
                }
                if(i < j)
                {
                        swap(arr, i , j);
                        i++;
                        j--;
                }
                else
                {
                        break;
                }
        }
        if(arr[s] > arr[i])
                swap(arr , s, i);
        print_arr(arr, 10);
        return i;
} 

void quickSort(int* arr, int s, int e)
{
        if(s >= e - 1)
        {
                return;
        }
        int pos = arrange(arr, s, e);
        quickSort(arr, s , pos);
        quickSort(arr, pos+1 , e);
}

int main()
{
        int* arr = createArr(10, INT);
        print_arr(arr, 10);
        quickSort(arr, 0 , 10);
        print_arr(arr, 10);
        return 0;
}

