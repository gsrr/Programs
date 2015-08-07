
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

void swap(int* arr, int i, int j)
{
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
}


void checkParent(int* arr, int i)
{
        int p = i;
        int c = i;
        while( p != 0)
        {
                p = ( c - 1 )/2;
                if(arr[c] < arr[p])
                {
                        swap(arr, c, p);
                        c = p;
                }
                else
                {
                        break;
                }
        }
}


int getChild(int* arr, int pos, int len)
{
        if(pos < len)
        {
                return arr[pos];
        }
        else
        {
                return 9999;
        }
}



int getChildPos(int* arr, int len, int c)
{
        int lval = getChild(arr, c * 2 + 1, len);
        int rval = getChild(arr, c * 2 + 2, len);
        if(arr[c] < lval && arr[c] < rval)
        {
                return -1;
        }
        else
        {
                if(lval < rval)
                {
                        return c * 2 + 1;
                }
                else
                {
                        return c * 2 + 2;
                }

        }

}

void adjustHeap(int* arr, int len)
{
        int c = 0;
        while( c * 2 + 1 < len )
        {
                int ch_pos = getChildPos(arr, len, c);
                if(ch_pos == -1)
                {
                        break;
                }
                swap(arr, c, ch_pos);
                c = ch_pos;
        }
}

void heapSort(int* arr, int num)
{
        int i;
        for( i = 0 ; i < num ; i++)
        {
                checkParent(arr, i);
        }
        int level = 0;
        for( i = 0 ; i < num ; i++)
        {
                if( i == ((int)pow(2, level) - 1))
                {
                        printf("\n");
                        printf("%d ", arr[i]);
                        level++;
                }
                else
                {
                        printf("%d ", arr[i]);
                }
        }
        printf("\n");

        for( i = num - 1 ; i > 0 ; i--)
        {
                swap(arr, 0, i);
                adjustHeap(arr, i);
        }
        
}


int main()
{
        int num = 10;
        int* arr = createArr(num, INT);
        print_arr(arr, 10) ;
        heapSort(arr, num);       
        print_arr(arr, 10) ;
        return 0;
}

