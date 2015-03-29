
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
