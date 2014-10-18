#include <stdio.h>
#include <stdlib.h>


struct bone{
        int m;
        char c;
        int n;
};


int compare(const void * a, const void * b)
{
          return ( ((struct bone*)a)->m - ((struct bone*)b)->m );
}


int main()
{
        int n;
        while(scanf("%d", &n)!=EOF)
        {
                int i;
                for( i=0 ; i < n ; i++)
                {
                        int m;
                        scanf("%d",&m);
                        struct bone *b_list = (struct bone*)malloc(sizeof(struct bone) * 255);
                        int headArr[255] = {0};
                        int j;
                        for( j = 0 ; j < m ; j++ )
                        {
                                int a , b;
                                char c;
                                scanf("%d %c %d", &a , &c , &b);
                                b_list[a].m = a;
                                headArr[a]--;
                                b_list[a].c = c;
                                b_list[a].n = b;
                                headArr[b] -= 2;
                        }
                        //qsort(b_list, m, sizeof(struct bone), compare);
                        
                        int head = 0;
                        for( j = 0 ; j < 255 ; j++)
                        {
                                if (headArr[j] == -1)
                                {
                                        head = j;
                                        break;
                                }
                        }
                        for( j = 0 ; j < m ; j++ )
                        {
                                printf("%c",b_list[head].c);
                                head = b_list[head].n;
                        }
                        printf("\n");
                        free(b_list);
                }

        }      
}
