


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
