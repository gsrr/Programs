#include <stdio.h>
#include <stdlib.h>

struct intArr{
        int *arr;
};

int global_m = 0;


int compare(const void *a, const void *b)
{
        struct intArr* struA = (struct intArr*) a;
        struct intArr* struB = (struct intArr*) b;
        for(int i = 0 ; i < global_m ; i++)
        {
                if(struA->arr[i] < struB->arr[i])
                {
                        return -1;
                }
                else if(struA->arr[i] > struB->arr[i])
                {
                        return 1;
                }
                else
                {
                        ;
                }
        }
        return 0;
}

int main()
{
        int n,m;
        struct intArr *struArr;
        while(scanf("%d %d", &n, &m) != EOF)
        {
                struArr = (struct intArr*) malloc(sizeof(struct intArr) * n);
                for(int i = 0 ; i < n ; i++)
                {
                        struArr[i].arr = (int*) malloc(sizeof(int) * m);
                        for(int j = 0 ; j < m ; j++)
                        {
                                scanf("%d", &(struArr[i].arr[j]));
                        }
                }
                global_m = m;
                qsort(struArr, n, sizeof(struct intArr), compare);

                for(int i = 0 ; i < n ; i++)
                {
                        for(int j = 0 ; j < m ; j++)
                        {
                                printf("%d ", struArr[i].arr[j]);
                        }
                        printf("\n");
                }

                for(int i = 0 ; i < n ; i++)
                {
                        free(struArr[i].arr);
                }
                free(struArr);

        }
        return 0;
}
