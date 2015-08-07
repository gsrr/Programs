
/*
 * merge B into A (Both are sorted array)
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


void insertionSort(int* arrA, int value, int pos)
{
        int i;
        for( i = pos - 1 ; i > -1 ; i--)
        {
                if(value < arrA[i])
                {
                        arrA[i+1] = arrA[i];
                }
                else
                {
                        break;       
                }
        }
        arrA[i+1] = value;
}

int main()
{
        int* A = createArr(20, INT);
        print_arr(A, 20);
        int* B = createArr(10, INT);
        print_arr(B, 10);
        int i;
        int size = 10;
        for( i = 0 ; i < 10 ; i++)
        {
                insertionSort(A, B[i], i + 10);
        }
        print_arr(A, 20);
        return 0;
}

