#include<stdio.h>
#include<stdlib.h>
int A[500000];

int compare(const void *a, const void *b)
{
        return *(int*)a < *(int*)b;
}

int findRedFloor(int* begin, int* end, int A[])
{
        while(A[*end] < 0)
        {
                if(abs(A[*end]) < abs(A[*begin]))
                {
                        *begin = *begin + 1;
                        return 1;
                }
                *end = *end - 1;
        }
        return 0;
}

int findBlueFloor(int* begin, int* end, int A[])
{
        while(A[*begin] > 0)
        {
                if(abs(A[*begin]) < abs(A[*end]))
                {
                        *end = *end - 1;
                        return 1;
                }
                *begin = *begin + 1;
        }
        return 0;

}

int main() {
        int t, n;
        scanf("%d", &t);
        while(t--)
        {
                scanf("%d", &n);
                int floor;
                int i = 0;
                for(i; i < n; i++) 
                {
                        scanf("%d", &floor);
                        A[i] = floor;
                }
                qsort(A, n, sizeof(int), compare);
                int begin = 0;
                int end = n-1;
                int ans = 1;
                int findRed = abs(A[begin]) > abs(A[end]) ? 1 : 0;
                while(A[begin] > 0 && A[end] < 0)
                {
                        if(findRed)
                        {
                                ans = ans + findRedFloor(&begin, &end, A);
                                findRed = 0;
                        }
                        else
                        {
                                ans = ans + findBlueFloor(&begin , &end, A);
                                findRed = 1;
                        }
                }
                printf("%d\n", ans);
        }
        return 0;
}
