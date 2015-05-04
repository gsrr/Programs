
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

typedef struct
{
        int* arr;
        int len;
}StructArr;

StructArr oct2bin(int num)
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
        StructArr ret = {retarr, cnt};
        return ret;
}

void updateBit(int *num, int i, int v)
{
        int c = ~( 1<<i );
        *num = (*num & c) | ( v<<i );
        return;
}

void insertNum(StructArr sarrN, StructArr sarrM)
{
        int* arrN = sarrN.arr;
        int nlen = sarrN.len;
        int* arrM = sarrM.arr;
        int mlen = sarrM.len;

        if(nlen < mlen)
        {
                printf("N should bigger than M\n");
                return;
        }

}

void insertNumBit(int N, int M)
{
        if(N < M)
        {
                printf("N should bigger than M\n");
                return;
        }
        int num = M;
        int cnt = 0;
        while( num != 1 )
        {
                int bit = num % 2;
                updateBit(&N, cnt++, bit);
                num = num / 2;
        }
        updateBit(&N, cnt++, 1);
        printf("After inserting:(M,N) = (%d,%d)\n", M, N);
}

int main()
{
        srand(time(NULL));
        int M = myrand(100);
        int N = myrand();
        printf("(M,N) = (%d,%d)\n", M,N);
        StructArr arrM = oct2bin(M);
        StructArr arrN = oct2bin(N);
        insertNum(arrN, arrM);
        insertNumBit(N, M);
        return 0;
}

