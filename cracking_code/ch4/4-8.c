
/*
 * Decide if t2 is a subtree of t1 (binary tree)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>




/* ::#def array :: */
#define INT 101
#define CHAR 102

void* createArr(int num, int type)
{
        if(type == INT)
        {
                int* tmp = (int*)malloc(sizeof(int)* num);
                int i;
                for( i = 0 ; i < num ; i++)
                {
                        tmp[i] = i+1;
                } 
                return tmp;
        }

}

void print_arr(int* arr, int num)
{
        int i;
        for( i = 0 ; i < num ; i++)
        {
                printf("%d ", arr[i]);
        }
        printf("\n");
}

/* #end */





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

/* ::#def list_void:: */
struct node
{
        void* elem;
        struct node* next;
};
typedef struct node node;


node* createNode(void* elem)
{
        node* nl = (node*)malloc(sizeof(node));
        nl->elem = elem;
        nl->next = NULL;
        return nl;
}

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

void printl(void* item)
{
        tNode* t = (tNode*)item;
        printf("%d ", *(int*)t->item);
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
        if(elem == NULL)
        {
                return;
        }
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
tNode* createBSTRoot(int* arr, int num)
{
        int low = 0;
        int high = num - 1;
        int middle = (low + high)/2;

        tNode* root = createTreeNode(&arr[middle]);
        appendBST(&root, arr, low, middle-1);
        appendBST(&root, arr, middle+1, high);
        return root;
}


void appendBSTNormal(tNode** root, int* key)
{
        tNode* tmp = *root;
        int* rk = (int*)tmp->item;
        if(*key < *rk)
        {
                if(tmp->lchild != NULL)
                {
                        appendBSTNormal(&(tmp->lchild), key);
                }
                else
                {
                        tNode* c = createTreeNode(key);
                        tmp->lchild = c;
                }
        }
        else
        {
                if(tmp->rchild != NULL)
                {
                        appendBSTNormal(&(tmp->rchild), key);
                }
                else
                {
                        tNode* c = createTreeNode(key);
                        tmp->rchild = c;
                }

        }
}

tNode* createBST(int* arr, int num)
{
        tNode* root = createTreeNode(arr);
        int i;
        for( i = 1 ; i < num ; i++)
        {
                appendBSTNormal(&root, &arr[i]);
        }
        print_tree(root, print);
        return root;
}

/* #end */

void deQueue(node** nlist)
{
        node* tmp = *nlist;
        *nlist = (*nlist) -> next;
        free(tmp);
}

int checkSubTree(tNode* tree, tNode* subTree)
{
        node* nl_sub = createNode(subTree);
        node* nl_tree = createNode(tree);
        while(nl_sub != NULL)
        {
                tNode* t_tree = (tNode*)nl_tree->elem;
                tNode* t_sub = (tNode*)nl_sub->elem;
                int* k_tree = (int*)t_tree->item;
                int* k_sub = (int*)t_sub->item;
                printf("check sub tee:(%d,%d, %d)\n", *k_tree, *k_sub, *k_tree == *k_sub);
                sleep(1);
                if(*k_tree != *k_sub)
                {
                        return -1;
                }
                if(t_sub->lchild != NULL && t_tree->rchild == NULL)
                {
                        return -2;
                }
                if(t_sub->rchild != NULL && t_tree->rchild == NULL)
                {
                        return -3;
                }
                listAppend(&nl_tree, t_tree->lchild);
                listAppend(&nl_sub, t_sub->lchild);
                listAppend(&nl_tree, t_tree->rchild);
                listAppend(&nl_sub, t_sub->rchild);
                deQueue(&nl_tree);
                deQueue(&nl_sub);
        }
        return 0;
}


int isSubTree(tNode* tree, tNode* subTree)
{
        node* nl = createNode(tree);        
        int cnt = 0;
        while(nl != NULL)
        {
                tNode* t = (tNode*)nl->elem;
                printf("(%d:%d)\n",cnt++, *(int*)t->item);
                listAppend(&nl, t->lchild);
                listAppend(&nl, t->rchild);
                deQueue(&nl);
                int ret = checkSubTree(t, subTree);
                if(ret == 0)
                {
                        printf("Find the sub tree\n");
                        return 0;
                }
        }
        return 1;

}


int main()
{
        int num = 20;
        int* arr = createArr(num, INT);
        print_arr(arr, num);        
        tNode* tree = createBSTRoot(arr, num);
        print_tree(tree, print);
        printf("\n");
        int sub[3] = {10, 5, 15};
        tNode* subTree = createBST(sub, 3);
        printf("\n");
        int ret = isSubTree(tree, subTree);
        printf("result:%d\n", ret);
        return 0;
}

