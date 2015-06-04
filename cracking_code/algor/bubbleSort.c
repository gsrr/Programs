
/*
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>




/* ::#def array :: */




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
#define INT 101
#define CHAR 102

void* createArr(int num, int type)
{
        if(type == INT)
        {
                int* tmp = (int*)malloc(sizeof(int)* num);
                int i;
                for( i = 0 ; i < num ; i++)
                {
                        tmp[i] = myrand();
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

void bubbleSort(int* arr, int len)
{
        int i;
        for( i = 0 ; i < len ; i++)
        {
                int j;
                for( j = 0 ; j < len - i - 1 ; j++)
                {
                        if(arr[j] > arr[j+1])
                        {
                                swap(arr, j , j+1);
                        }
                }
        }
}

int main()
{
        int* arr = createArr(10, INT);        
        print_arr(arr, 10);
        bubbleSort(arr, 10);
        print_arr(arr, 10);
        return 0;
}

