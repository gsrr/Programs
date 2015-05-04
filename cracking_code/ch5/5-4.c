
/*
 * Explain that the following code does: (( n & (n-1)) == 0)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>


void isPowerOf2(int num)
{
        if( (num & (num-1)) == 0)
        {
                printf("%d is power of 2 : True\n", num);
        }
        else
        {
                printf("%d is power of 2 : False\n", num);
        }
}




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

int main()
{

        int num = rand() % 100;
        isPowerOf2(num);
        isPowerOf2(4);
        int num2 = myrand(100);
        isPowerOf2(num2);

        return 0;
}

