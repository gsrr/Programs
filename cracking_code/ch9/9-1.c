
/*
 * How many possible ways can run up the stairs?
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>


int possibleWay(int n)
{
        if( n == 1)
        {
                return 1;
        }
        else if( n == 2)
        {
                return 2;
        }
        else if( n == 3)
        {
                return 4;
        }
        else
        {
                return possibleWay(n-1) + possibleWay(n-2) + possibleWay(n-3);
        }
}

int dypossibleWay(int n)
{
        if( n == 1)
        {
                return 1;
        }
        else if( n == 2)
        {
                return 2;
        }
        else if( n == 3)
        {
                return 4;
        }
        else
        {
                int *arr = (int*)malloc(sizeof(int)* n);
                arr[0] = 1;
                arr[1] = 2;
                arr[2] = 4;
                int i;
                for( i = 3 ; i < n ; i++)
                {
                        arr[i] = arr[i-1] + arr[i-2] + arr[i-3];
                }
                int value = arr[n-1];
                free(arr);
                return value;
        }
}

void currtime()
{
        time_t t;
        struct tm *timeinfo;
        time(&t);
        timeinfo = localtime(&t);
        printf("%s\n",asctime(timeinfo));
}


int main()
{
        int n;
        while(1)
        {
                printf("Please enter a number:");
                scanf("%d", &n);
                if( n == 0)
                {
                        break;
                }
                currtime();
                printf("n=%d possible ways:%d\n", n, possibleWay(n));
                currtime();
                printf("n=%d possible ways:%d\n", n, dypossibleWay(n));
                currtime();
        }
        return 0;
}

