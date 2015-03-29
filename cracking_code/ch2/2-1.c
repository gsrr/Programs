
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


struct Node
{
        int val;
        struct Node* next;
};

typedef struct Node Node;

struct Node* createNode()
{
        return (struct Node*)malloc(sizeof(struct Node));
}

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

void removeDup_basic(struct Node* list)
{
        Node* pre_runner = NULL;
        Node* runner = list;
        while(runner != NULL)
        {
                Node* check = list;
                while(check != runner) 
                {
                        if(check->val == runner->val)
                        {
                                pre_runner->next = runner->next;
                                free(runner);
                                runner = pre_runner;               
                                break;
                        }
                        check = check -> next;
                }
                pre_runner = runner;      
                runner = runner -> next;
         }
        pre_runner -> next = NULL;
}

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
/*hash table*/
void removeDup_buffer(struct Node* list)
{
        Hash** map = HashTable(10);
        Node* pre_runner = NULL;
        Node* runner = list;
        int cnt = 0;
        while(runner != NULL)
        {
                int val = runner -> val;
                int key = val % 10;
                Hash* tmp = HashNode();
                tmp -> pos = cnt;
                tmp -> val = runner -> val;
                tmp -> next = NULL;
                int ret = HashInsert(map, key, tmp);
                if(ret == 1) //dup
                {
                        pre_runner -> next = runner -> next;
                        free(runner);
                        free(tmp);
                        runner = pre_runner;
                }
                pre_runner = runner;
                runner = runner -> next;
                cnt++;
        }
        //HashShow(map, 10);

        
}

int main()
{
        struct Node* list = createLinkList(11);
        print_list(list);
        struct Node* dup_list = dupList(list, 11);
        print_list(dup_list);
        removeDup_basic(dup_list);
        print_list(dup_list);
        free_list(dup_list);
        dup_list = dupList(list, 11);
        removeDup_buffer(dup_list);
        print_list(dup_list);
        /*
        free_list(list);
        list = createLinkList(10);
        print_list(list)
        removeDup_Sort(list);
        print_list(list);
        free_list(list);
        */
        return 0;
}

