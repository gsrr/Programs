/*partition a linked list around a value x*/
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

void insertToList(Node** list, Node* node)
{
        if(*list == NULL)
        {
                *list = node;
                return;
        }
        Node* runner = *list;
        while(runner -> next != NULL)
        {
                runner = runner->next;
        }
        runner->next = node;
}


void partitionList(Node** list , int k)
{
        Node* newList = NULL;
        if(*list == NULL)
        {
                printf("no data\n");
        }
        else
        {
                while( *list != NULL && (*list)->val > k)
                {
                        Node* tmp = *list;
                        *list = (*list) -> next;
                        tmp-> next = NULL;
                        insertToList(&newList, tmp); 
                }
        }

        Node* runner = *list;
        Node* pre_runner = NULL;

        while( runner != NULL)
        {
                if(runner->val > k)
                {
                        pre_runner -> next = runner -> next;
                        runner -> next = NULL;                        
                        insertToList(&newList, runner); 
                        runner = pre_runner;
                }
                pre_runner = runner;
                runner = runner -> next;
        }
        pre_runner->next = newList;
}

int main()
{
        Node* list = createLinkList(11);
        print_list(list);
        int k;
        scanf("%d", &k);
        partitionList(&list, k);
        print_list(list);
        return 0;
}

