
/*
 * create balanced binary search tree
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>


int* createArr(int num)
{
        int* tmp = (int*)malloc(sizeof(int)* num);
        int i;
        for( i = 0 ; i < num ; i++)
        {
                tmp[i] = i+1;
        } 
        return tmp;
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
void createLTreeByArr(tNode** root, int* arr, int low, int high);
void createRTreeByArr(tNode** root, int* arr, int low, int high)
{
        if(high < low)
        {
                return;
        }
        
        int middle = (low + high)/2;
        printf("R:%d:%d:%d:%d\n", low,high, middle, arr[middle]);
        tNode* tmp = createTreeNode(&arr[middle]);
        (*root)->rchild = tmp;
        createLTreeByArr(&((*root)->rchild), arr, low, middle - 1);
        createRTreeByArr(&((*root)->rchild), arr, middle + 1, high);
}

void createLTreeByArr(tNode** root, int* arr, int low, int high)
{
        if(high < low)
        {
                return;
        }
        int middle = (low + high)/2;
        printf("L:%d:%d:%d\n", low,high, arr[middle]);
        tNode* tmp = createTreeNode(&arr[middle]);
        (*root)->lchild = tmp;
        createLTreeByArr(&((*root)->lchild), arr, low, middle - 1);
        createRTreeByArr(&((*root)->lchild), arr, middle + 1, high);
}

void print(void* item)
{
        printf("%d ", *(int*)item);
}

int main()
{
        int num = 20;
        int* arr = createArr(num);
        int low = 0 ; 
        int high = num - 1;
        int middle = (low + high)/2;
        tNode* root = createTreeNode(&arr[middle]);
        createLTreeByArr(&root, arr, low, middle - 1);
        createRTreeByArr(&root, arr, middle + 1, high);
        printf("height:%d\n", treeHeight(root));
        print_tree(root, print);
        printf("\n");
        return 0;
}

