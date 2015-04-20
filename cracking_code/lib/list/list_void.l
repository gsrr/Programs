


/* ::#def list_void:: */
struct node
{
        void* elem;
        struct node* next;
};
typedef struct node node;

void releaseList(node* nl)
{
        while(nl != NULL)
        {
                node* tmp = nl;
                nl = nl -> next;
                free(tmp->elem);
                free(tmp);
        }
}

void print_list(struct node* list, void (*print)(void* item))
{
        node* runner = list;
        while(runner != NULL)
        {
                print(runner->elem);
                runner = runner->next;
        }
        printf("\n");
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

/* #end */
