
/*
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>


struct test
{
        int a;
        int b;
};

void func(struct test t)
{
        printf("(a,b) = (%d, %d)\n", t.a, t.b);
}

int main()
{
        func((struct test){1,2});
        struct test t = {1,2}; //initial structure
        func(t);
        struct test t2 = {.a=4,.b=2}; //initial structure
        func(t2);
        struct test t3 = {}; //empty initialize
        func(t3);
        struct test t4 = {1}; //initialize one element
        func(t4);
        return 0;
}

