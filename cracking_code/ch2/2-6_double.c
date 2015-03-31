
/*
 *
 */
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


Node* initialNode(int val)
{
        Node* tmp = createNode();
        tmp -> val = val;
        tmp -> next = NULL;
        return tmp;
}

Node* list_add(Node* a, Node* b)
{
        Node* c = NULL;
        Node* runA = a;
        Node* runB = b;
        Node* runC = NULL;
        int carry = 0;
        while(runA != NULL || runB != NULL)
        {
                int valA = 0;
                int valB = 0;
                if(runA != NULL)
                {
                        valA = runA -> val;
                        runA = runA -> next;
                }
                if(runB != NULL)
                {
                        valB = runB -> val;
                        runB = runB -> next;
                }
                int sum = valA + valB + carry;
                carry = sum / 10;
                sum = sum % 10;
                Node* tmp = initialNode(sum);
                if( c == NULL )
                {
                        c = tmp;
                        runC = c;
                }
                else
                {
                        runC -> next = tmp;
                        runC = runC -> next;
                }
        }

        if(carry != 0)
        {
                Node* tmp = initialNode(carry);
                runC -> next = tmp;
        }
        return c;
}
void reverseList(Node** list)
{
        Node* r = *list;
        Node* p = NULL;
        Node* c = NULL;
        while(r != NULL)
        {
                c = r;
                r = r -> next;
                c -> next = p;
                p = c;       
        }
        
        *list = c;
}
void makeToCircular(Node** list, int begin)
{
        Node* r = *list;
        Node* p = *list;
        int cnt = begin;
        while(r->next != NULL)
        {
                r = r -> next;
                cnt--;
                if(cnt < 0)
                {
                        p = p -> next;
                }
        }
        r -> next = p;
        printf("Begin Node:%d\n", p->val);
}
/* #end */


void findBeginNode(Node* list)
{
        Node* f = list -> next -> next;
        Node* s = list -> next;
        while( f != s )
        {
                f = f -> next -> next;
                s = s -> next;
        }

        f = list;
        while( f != s)
        {
                f = f -> next;
                s = s -> next;
        }
        printf("Find Begin Node:%d\n", s -> val);
}

int main()
{
        Node *a = createLinkList(11);
        print_list(a);
        makeToCircular(&a , 6);
        findBeginNode(a);

        return 0;
}

