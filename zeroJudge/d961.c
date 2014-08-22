#include<stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
        int c = *(int*) a;
        int d = *(int*) b;
        if(c < d)
        {
                return 1;
        }
        else
        {
                return -1;
        }
}


void isort(int array[] , int n)
{
        int c;
        for (c = 1 ; c < n ; c++) 
        {
                int d = c;
                while ( d > 0 && array[d] > array[d-1]) 
                {
                        int tmp = array[d];
                        array[d]   = array[d-1];
                        array[d-1] = tmp;
                        d--;
                }
        }
}

int main() 
{
        int t, n, m, a;
        scanf("%d", &t);
        while(t--) 
        {
                scanf("%d %d", &n, &m);
                int *A = (int*) malloc( n * sizeof(int));
                int *B = (int*) malloc( m * sizeof(int));
                for(a = 0; a < n; a++)    scanf("%d", &A[a]);
                for(a = 0; a < m; a++)    scanf("%d", &B[a]);
                /*isort(A, n);
                isort(B, m);*/
                qsort(A, n, sizeof(int), compare);
                qsort(B, m, sizeof(int), compare);
                int in1 = 0, in2 = 0, Ans = 0;
                for(; in1 < n && in2 < m; in1++) 
                {
                        if(A[in1] <=  B[in2])
                        {
                                Ans++, in2++;
                        }
                }
                if(Ans) 
                {   
                        printf("%d\n", Ans);
                }
                else 
                {
                        puts("Santa Claus wishes you get AC in the next submission.");
                }
                free(A);
                free(B);
        }
        return 0;
}

