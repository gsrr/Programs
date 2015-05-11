
/*
 * Given an integer , 
 * print the next smallest and next largest number 
 * that have the same number of 1 bits in their binary representation.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>




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



/* ::#def myrand :: */
typedef struct{
        int base;
        int cust;
}f_args;

int myrand_base(int base)
{
        srand(time(NULL));
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




/* ::#def bit :: */

typedef struct
{
        int* arr;
        int len;
}binarray;

binarray oct2bin(int num)
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
        binarray ret = {retarr, cnt};
        return ret;
}
void updateBit(int *num, int i, int v)
{
        int c = ~( 1<<i );
        *num = (*num & c) | ( v<<i );
        return;
}
/* #end */
void nextSmallest(int n)
{
        binarray ba = oct2bin(n);
        int cnt = 0;
        int i;
        for( i = ba.len - 1; ba.arr[i] != 1; i--)
        {
                cnt++;
        }
        int tmp = n;
        updateBit(&tmp, cnt, 0 );
        updateBit(&tmp, cnt + 1, 1);
        printf("%d\n", tmp);
        oct2bin(tmp);

}

int main()
{
        int n = myrand();
        nextSmallest(n);
        return 0;
}

