
/*
 * Swap odd and even bit
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


void swap(int* tmp, int index, int cur, int pre)
{
        if(cur == pre)
        {
                return;
        }
        updateBit(tmp, index, pre);
        updateBit(tmp, index - 1, cur);

}


void convertOddEvent(int n, binarray ba)
{
        int tmp = n;
        int i;
        int cnt = 0 ;
        int pre;
        for( i = ba.len - 1 ; i > -1 ; i--)
        {
                cnt++;
                if(cnt % 2 == 0)
                {
                        swap(&tmp, ba.len - i - 1, ba.arr[i], pre);
                }
                else
                {
                        pre = ba.arr[i];
                }
        }
        printf("After swap:%d\n", tmp);
        oct2bin(tmp);
}


int main()
{

        int n = myrand();
        printf("Random number:%d\n", n);
        binarray ba = oct2bin(n);
        print_arr(ba.arr, ba.len);        
        convertOddEvent(n, ba);
        return 0;
}

