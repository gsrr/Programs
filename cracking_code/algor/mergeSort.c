
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
        srand(time(NULL));
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


void mergeCombine(int* arr, int s, int e, int mid)
{
        int* tmp = (int*)malloc(sizeof(int) * 10);
        int t = s;
        int i = s;
        int j = mid + 1;
        while( i <= mid && j <= e)
        {
                if( arr[i] <= arr[j] )
                {
                        tmp[t++] = arr[i];
                        i++;
                }              
                else
                {
                        tmp[t++] = arr[j];
                        j++;
                }
        }       

        int k;
        if( i < mid + 1)
        {
                for( k = i ; k < mid + 1 ; k++)
                {
                        tmp[t++] = arr[k];
                }             
        }
 
        if( j < e+1)
        {
                for( k = j ; k < e+1 ; k++)
                {
                        tmp[t++] = arr[k];
                }             

        }
        
        for( k = s ; k < e+1 ; k++)
        {
                arr[k] = tmp[k];
        }
        free(tmp);
}

void mergeSort(int* arr, int s, int e)
{
        if(s >= e)
        {
                return;
        }
        int mid = (s + e) / 2;
        //printf("(s, e, mid) = (%d, %d, %d)\n", s, e,mid );
        mergeSort(arr, s, mid);
        mergeSort(arr, mid + 1, e);
        mergeCombine(arr, s, e, mid);
}

int main()
{
        int* arr = createArr(10, INT);
        print_arr(arr, 10);
        mergeSort(arr, 0 , 9);
        print_arr(arr, 10);
        free(arr);
        return 0;
}

