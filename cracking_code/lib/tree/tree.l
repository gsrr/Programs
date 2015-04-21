


/* ::#def tree :: */
struct tNode
{
        struct tNode* rchild;
        struct tNode* lchild;
        void* item;
};

typedef struct tNode tNode;

tNode* createTreeNode(void* item)
{
        tNode* tmp = (tNode*)malloc(sizeof(tNode));
        tmp->item = item;
        tmp->rchild = NULL;
        tmp->lchild = NULL;
        return tmp;
}


void print_tree(tNode* root, void (*print)(void* item))
{
        print(root->item);
        if(root->lchild != NULL)
        {
                print_tree(root->lchild, print);
        }
        if(root->rchild != NULL)
        {
                print_tree(root->rchild, print);
        }
}

int treeHeight(tNode* tree)
{
       if(tree == NULL)
       {
               return 0;
       }
       int lh = 1 + treeHeight(tree->lchild);
       int rh = 1 + treeHeight(tree->rchild);
       return (lh > rh) ? lh : rh;
}
/* #end */
