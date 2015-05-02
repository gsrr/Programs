
/*
 * Insert M into N
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>


typedef struct{
        int base;
        int cust;
}f_args;

int myrand_base(int base)
{
        return rand() % base;
}

int myrand(int base);


int var_f(f_args in)
{
        int base = in.cust ? in.cust : in.base;
        return myrand_base(base);
}

/*
* varadic macros
*/
#define myrand(...) var_f((f_args){.base=1000,__VA_ARGS__});




/* ::#def array :: */
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
                        tmp[i] = i+1;
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

int* oct2bin(int num)
{
        int arr[32] = {0};
        int cnt = 0;
        while(num != 1)
        {
                arr[cnt++] = num % 2;
                num = num / 2;
        }
        arr[cnt++] = 1;
        int* retarr = (int*)malloc(sizeof(int) * cnt);
        int i;
        int idx = 0;
        for( i = cnt - 1 ;  i > -1 ; i--)
        {
                retarr[idx++] = arr[i]; 
        }
        print_arr(retarr, cnt);
        return retarr;
}

void insertNum(int** arrN, int* arrM)
{

}

int main()
{
        srand(time(NULL));
        int M = myrand(100);
        int N = myrand();
        printf("(M,N) = (%d,%d)\n", M,N);
        int* arrM = oct2bin(M);
        int* arrN = oct2bin(N);
        insertNum(&arrN, arrM);
        return 0;
}

