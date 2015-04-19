
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
        int height;
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
        tmp->height = 0;
        return tmp;
}


void releaseList(node* list)
{
        while(list != NULL)
        {
                node* tmp = list;
                list = list->next;
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
        root->height = 0;
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
       if(tree -> height != 0)
       {
               return tree->height;
       }
       int lh = 1 + treeHeight(tree->lchild);
       int rh = 1 + treeHeight(tree->rchild);
       return (lh > rh) ? lh : rh;
}


node* createList(tNode* tree)
{
        node* run = (node*)malloc(sizeof(node));
        run->elem = tree;
        run->next = NULL;
        node* rear = run;
        node* head = run;
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
                run = run -> next;
        }
        return head;
}



/* ::#def List:: */

void print_list(struct node* list)
{
        node* runner = list;
        while(runner != NULL)
        {
                tNode* t = runner->elem;
                printf("%d:%d ", t->key, t->height);
                runner = runner->next;
        }
        printf("\n");
}



void reverseList(node** list)
{
        node* r = *list;
        node* p = NULL;
        node* c = NULL;
        while(r != NULL)
        {
                c = r;
                r = r -> next;
                c -> next = p;
                p = c;       
        }
        
        *list = c;
}
/* #end */

void height(node** nl)
{
        node* r = *nl;
        while(r != NULL)
        {
               tNode* t = r->elem;
               int h = treeHeight(t);
               t->height = h;
               r = r -> next; 
        }       
}

int isBalanced(tNode* t)
{
        if(t == NULL)
        {
                return 0;
        }
        int ret = 0;
        int lh = 0;
        if(t->lchild != NULL)
        {
               lh = t->lchild->height;
                ret = ret + isBalanced(t->lchild);
        }
        int rh = 0;
        if(t->rchild != NULL)
        {
               rh = t->rchild->height;
                ret = ret + isBalanced(t->rchild);
        }
        printf("%d:%d ", t->key, ret);
        if(abs(lh-rh) > 1)
        {
                printf("This tree is not balanced.\n");
                return;
        }
        return ret;
}


int main()
{
        tNode* t = createTree(16);
        print_tree(t);
        printf("\n");
        node* nl = createList(t);
        print_list(nl);
        reverseList(&nl);
        print_list(nl);
        height(&nl);        
        print_list(nl);
        printf("\nisBalanced:%d\n",isBalanced(t));
        return 0;
}

