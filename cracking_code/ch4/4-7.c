
/*
 * find common ancestor of two nodes in a binary tree.
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
/* #end */


int findAncestor(tNode* root, int key1, int key2)
{
        int lc = 0;
        int rc = 0;
        if(root->lchild != NULL)
        {
                lc = findAncestor(root->lchild , key1, key2);
        }

        if(root->rchild != NULL)
        {
                rc = findAncestor(root->rchild , key1, key2);
        }
        int ret = lc + rc;
        int cc = *(int*)root->item;
        if( cc == key1 || cc == key2)
        {
                ret += 1;
        }
        if( ret == 2)
        {
                printf("The ancestor is %d\n",*(int*)root->item);
        }
        return ret;
}


int main()
{
        srand(time(NULL));
        int num = 20;
        int* arr = createArr(num, INT);
        print_arr(arr, num);
        tNode* root = createBSTRoot(arr, num);
        print_tree(root,print);
        printf("\n");
        int i;
        for(i = 0 ; i < num ; i++)
        {
                int key1 = rand()%20 + 1;
                int key2 = rand()%20 + 1;
                printf("(%d,%d)\n", key1, key2);
                int tmp = findAncestor(root, key1, key2);
        }
        return 0;
}

