/*Find kth to last element*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/* ::#def List:: */
struct Node* createLinkList(int len);
struct Node* createNode();
void print_list(struct Node* list);

struct Node
{
        int val;
        struct Node* next;
};
typedef struct Node Node;
struct Node* createLinkList(int len)
{
        srand(time(NULL));
        struct Node* list = createNode();
        list->val = rand() % 10;
        list->next =NULL;
        struct Node* runner = list;
        int i;
        for( i = 0 ; i < len - 1 ; i++)
        {
                struct Node* tmp = createNode();
                tmp->val = rand() % 10;
                tmp->next = NULL;
                runner->next = tmp;
                runner = runner->next; 
        }
        return list;              
}

struct Node* createNode()
{
        return (struct Node*)malloc(sizeof(struct Node));
}

void print_list(struct Node* list)
{
        struct Node* head = list;
        while(list != NULL)
        {
                printf("%d ", list->val);
                list = list->next;
        }
        printf("\n");
        list = head;
}
void free_list(struct Node* list)
{
        Node* runner  = list;
        while(runner != NULL)
        {
                struct Node* tmp = runner;
                runner = runner -> next;
                free(tmp);                
        }
}


struct Node* dupList(struct Node* list, int len)
{
        struct Node* dup_list = createLinkList(len);
        struct Node* dup_runner = dup_list;
        struct Node* runner = list;
        while(runner != NULL)
        {
                dup_runner -> val = runner -> val;
                dup_runner = dup_runner -> next;
                runner = runner -> next;
        }
        return dup_list;
}
/* #end */


void findKthToLast(Node* list, int k)
{
        if( k <= 0)
        {
                printf("wrong position:%d\n",k);
                return;
        }
        Node* runner = list;
        Node* target = list;
        int cnt = k - 1;
        while( runner -> next != NULL )
        {
                if(cnt == 0)
                {
                        target = target -> next;
                }
                else
                {
                        cnt--;
                }
                runner = runner -> next;
        }
        printf("\n");
        print_list(list);
        printf("%dth to last:%d\n", k, target->val);       
        

}

int main()
{
        Node* list = createLinkList(11);
        print_list(list);
        while(1)
        {
                int k;
                scanf("%d", &k);
                findKthToLast(list, k);
        }
        return 0;
}

