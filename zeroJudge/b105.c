#include <stdio.h>
#include <stdlib.h>

struct Book
{
        int printT;
        int bindT;
};

int compare(const void* a, const void* b)
{
        struct Book *tmp_a = (struct Book*) a;
        struct Book *tmp_b = (struct Book*) b;
        return tmp_a->bindT < tmp_b->bindT;
}



int main()
{
        while(1)
        {
                int n;
                scanf("%d", &n);
                printf("%d\n", n);
                if(n == 0)
                {
                        break;
                }
                else
                {
                        struct Book *book = (struct Book*) malloc(n * sizeof(struct Book));
                        int i = 0;
                        for(i ; i < n ; i++)
                        {
                                int ret = scanf("%d %d", &book[i].printT, &book[i].bindT);
                                printf("%d\n",book[i].printT);
                        }
                       
                        getchar(); 
                        qsort(book, n, sizeof(struct Book), compare);
                        int finalPrintT = 0, finalBindT = 0, finalT = 0;

                        for(i = 0 ; i < n ; i++)
                        {
                                finalPrintT += book[i].printT;
                                int tmp_max = finalPrintT + book[i].bindT; 
                                if ( tmp_max > finalT)
                                        finalT = tmp_max;

                        }
                        printf("%d\n", finalT);
                        free(book);
                }
        }


}
