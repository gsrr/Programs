


/* ::#def bst :: */
/* include tree.l first*/
void print(void* item)
{
        printf("%d ", *(int*)item);
}
void appendData(tNode** root, tNode* tmp)
{
        tNode* r = *root;
        int* ritem = (int*)r->item;
        int* titem = (int*)tmp->item;

        if(*titem < *ritem)
        {
                if(r->lchild == NULL)
                {
                        r->lchild = tmp;
                }
                else
                {
                        appendData(&(r->lchild), tmp);
                }
        }
        else
        {
                if(r->rchild == NULL)
                {
                        r->rchild = tmp;
                }
                else
                {
                        appendData(&(r->rchild), tmp);
                }
        }
}

void appendBST(tNode** root, int* arr, int low, int high)
{
        if(high < low)
        {
                return;
        }
        tNode* data = *root;
        int* ritem = (int*)data->item; 
        int middle = (low + high)/2;
        tNode* tmp = createTreeNode(&arr[middle]);
          
        appendData(root, tmp);
        appendBST(root, arr, low, middle-1);
        appendBST(root, arr, middle+1, high);
}

void createBSTByOrder(int* arr, int num)
{
        tNode* root = createTreeNode(&arr[0]);
        int i;
        for( i = 1 ; i < num ; i++)
        {
                appendBST(&root, arr, i, i);
        }
        printf("\nheight:%d\n", treeHeight(root));
        print_tree(root, print);
}
/* #end */
