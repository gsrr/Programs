
#include <stdio.h>
#include <stdlib.h>
#include <string.h>






/* ::#def Hash:: */
struct Hash{
        int pos;
        int val;
        struct Hash* next;
};

typedef struct Hash Hash;

Hash** HashTable(int len)
{
        Hash** tmp = (Hash**)malloc(sizeof(Hash*) * len);
        int i;
        for( i = 0 ; i < len ; i++)
        {
                tmp[i] = NULL;
        }
        return tmp;
}
Hash* HashNode()
{
        return (Hash*)malloc(sizeof(Hash));
}

int HashInsert(Hash** map , int key , Hash* tmp)
{
        if(map[key] == NULL)
        {
                map[key] = tmp;
        }
        else
        {
                Hash* runner = map[key];
                Hash* pre_runner = NULL;
                while(runner != NULL)
                {
                        if(tmp -> val == runner -> val)
                        {
                                return 1;
                        }
                        pre_runner = runner;
                        runner = runner -> next;
                }

                pre_runner -> next = tmp;
        }
        return 0;
}


void HashShow(Hash** map, int len)
{
        int i;
        for(i = 0 ; i < len ; i++)
        {
                printf("%d ",i);
                Hash* runner = map[i];
                while(runner != NULL)
                {
                        printf("pos:%d val:%d, ", runner->pos, runner->val);
                        runner = runner -> next;
                }
                printf("\n");
        }        
        printf("\n");
}
/* #end */

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
int main()
{
        return 0;
}

