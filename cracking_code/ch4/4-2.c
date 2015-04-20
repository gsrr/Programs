
/*
 * a directed graph , find out where is a route between two nodes.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>


/* ::#def list_void:: */
struct node
{
        void* elem;
        struct node* next;
};
typedef struct node node;

void releaseList(node* list)
{
        while(list != NULL)
        {
                node* tmp = list;
                list = list->next;
                free(tmp->elem);
                free(tmp);
        }
}
void listAppend(node** nl, void* elem)
{
        node* tmp = (node*)malloc(sizeof(node));
        tmp->elem = elem;
        tmp->next = NULL;
        if( *nl == NULL )
        {
                *nl = tmp;
        }
        else
        {
                node* r = *nl;
                while(r -> next != NULL)
                {
                        r = r -> next;
                }
                r->next = tmp;
        }
}


void print(void* item)
{
        int* t = (int*)item;
        printf("%d ", *t);
}

void print_list(node* nl, void (*print)(void* item))
{
        node* r = nl;
        while(r != NULL)
        {
                print(r->elem);
                r = r->next;
        }
        printf("\n");
}
/* #end */
int** createGraph(int num)
{
        int** graph = (int**)malloc(sizeof(int*)*num);
        int i;
        for( i = 0 ; i < num ; i++)
        {
                graph[i] = (int*)malloc(sizeof(int) * num);
        }
        return graph;
}


void print_graph(int** graph, int num)
{
        int i;
        for( i = 0 ; i < num ; i++)
        {
                int j;
                for( j = 0 ; j < num ; j++)
                {
                        printf("%d ", graph[i][j]);
                }
                printf("\n");
        }
        printf("\n");
}

void initialGraph(int*** graphAdd, int num)
{
        srand(time(NULL));
        int** graph = *graphAdd;
        int i;
        int j;
        for( i = 0 ; i < num ; i++)
        {
                for( j = 0 ; j < num ; j++)
                {
                        int n = rand() % 2;
                        graph[i][j] = n; 

                }
        }
}



int isWalked(node* nl, int s)
{
        node* r = nl;
        while(r != NULL)
        {
                int* old = r->elem;
                if(*old == s)
                {
                        return 1;
                }
                r = r -> next;
        }
        return 0;
}


void DFSSearch(int** graph, int s, int d, int num, node** nl)
{
        sleep(1);
        printf("(%d)\n", s);
        if(isWalked(*nl, s) == 1)
        {
                return;
        }
        if( s == d )
        {
                printf("There is a route between two nodes\n");
                return;
        }
        listAppend(nl, &s);
        print_list(*nl, print);
        int i;
        for( i = 0 ; i < num ; i++)
        {
                if(graph[s][i] == 1)
                {
                        DFSSearch(graph, i, d, num, nl);
                }
        }
}

void findRoute(int** graph , int num)
{
        int x, y;
        printf("Enter the source node x:");
        scanf("%d", &x);
        printf("Enter the destination node y:");
        scanf("%d", &y);
        printf("%d to %d\n", x, y); 
        node* nl = (node*)malloc(sizeof(node));
        nl = NULL;
        DFSSearch(graph, x, y, num, &nl);
        //BFSSearch()
}

int main()
{
        int** graph = createGraph(10);
        print_graph(graph, 10);
        initialGraph(&graph, 10);
        print_graph(graph, 10);
        findRoute(graph, 10);

        return 0;
}

