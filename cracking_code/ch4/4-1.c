
/*
 * check if a tree is balanced
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>


struct node
{
        void* elem;
        struct node* next;
};

typedef struct node node;

struct tNode
{
        struct tNode* rchild;
        struct tNode* lchild;
        int key;
};

typedef struct tNode tNode;



void listAppend(node** rear, void* elem)
{
        node* r = *rear;
        node* tmp = (node*)malloc(sizeof(node));
        tmp->elem = elem;
        tmp->next = NULL;
        r->next = tmp;
}


tNode* createTreeNode(int key)
{
        tNode* tmp = (tNode*)malloc(sizeof(tNode));
        tmp->key = key;
        tmp->rchild = NULL;
        tmp->lchild = NULL;
        return tmp;
}


void releaseList(node* list)
{
        while(list != NULL)
        {
                node* tmp = list;
                list = list->next;
                free(tmp->elem);
                free(tmp);
        }
}

void appendNode(tNode** root , int key)
{
        node* front = (node*)malloc(sizeof(node));
        node* rear = front;
        front->elem = *root;
        front->next = NULL;
        while( front != NULL )
        {
                tNode* r = front->elem;
                if(r->lchild == NULL)
                {
                        tNode* tmp = createTreeNode(key);
                        r-> lchild = tmp;
                        break; 

                }
                else if(r->rchild == NULL)
                {
                        tNode* tmp = createTreeNode(key);
                        r-> rchild = tmp;
                        break; 

                }
                else
                {
                        listAppend(&rear, r->lchild);
                        rear = rear -> next;
                        listAppend(&rear, r->rchild);
                        rear = rear -> next;

                }
                node* old = front;
                front = front->next;
                free(old);
        }
        releaseList(front);

}

tNode* createTree(int num)
{
        srand(time(NULL));
        tNode* root = (tNode*)malloc(sizeof(tNode));
        root->key = 0;
        root->rchild = NULL;
        root->lchild = NULL;
        int i;
        for( i = 1 ; i < num ; i++)
        {
                appendNode(&root, i);       
        } 

        return root;
}


void print_tree(tNode* root)
{
        printf("%d ", root->key);
        if(root->lchild != NULL)
        {
                print_tree(root->lchild);
        }
        if(root->rchild != NULL)
        {
                print_tree(root->rchild);
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

int isBalance(tNode* tree)
{
        node* run = (node*)malloc(sizeof(node));
        run->elem = tree;
        run->next = NULL;
        node* rear = run;
        while(run != NULL)
        {
                tNode* root = run->elem;
                if(root->lchild != NULL)
                {
                        listAppend(&rear, root->lchild);
                        rear = rear -> next;
                }
                if(root->rchild != NULL)
                {
                        listAppend(&rear, root->rchild);
                        rear = rear -> next;
                }
                int lh = treeHeight(root->lchild);
                int rh = treeHeight(root->rchild);
                printf("tree root:%d,lh:%d,rh:%d\n", root->key, lh, rh);
                sleep(1);
                if(abs(lh - rh) > 1)
                {
                        return 0;
                }
                node* tmp = run;
                run = run -> next;
                free(tmp);
        }
        return 1;
}

int main()
{
        tNode* t = createTree(16);
        print_tree(t);
        printf("\n");
        printf("Is this three balanced:%d\n",isBalance(t));
        
        return 0;
}

