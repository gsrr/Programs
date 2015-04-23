
/*
 * Find the next node in bst.(in-order)
 * child has a link to its parent.
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


Node* initialNode(int val)
{
        Node* tmp = createNode();
        tmp -> val = val;
        tmp -> next = NULL;
        return tmp;
}

Node* list_add(Node* a, Node* b)
{
        Node* c = NULL;
        Node* runA = a;
        Node* runB = b;
        Node* runC = NULL;
        int carry = 0;
        while(runA != NULL || runB != NULL)
        {
                int valA = 0;
                int valB = 0;
                if(runA != NULL)
                {
                        valA = runA -> val;
                        runA = runA -> next;
                }
                if(runB != NULL)
                {
                        valB = runB -> val;
                        runB = runB -> next;
                }
                int sum = valA + valB + carry;
                carry = sum / 10;
                sum = sum % 10;
                Node* tmp = initialNode(sum);
                if( c == NULL )
                {
                        c = tmp;
                        runC = c;
                }
                else
                {
                        runC -> next = tmp;
                        runC = runC -> next;
                }
        }

        if(carry != 0)
        {
                Node* tmp = initialNode(carry);
                runC -> next = tmp;
        }
        return c;
}
void reverseList(Node** list)
{
        Node* r = *list;
        Node* p = NULL;
        Node* c = NULL;
        while(r != NULL)
        {
                c = r;
                r = r -> next;
                c -> next = p;
                p = c;       
        }
        
        *list = c;
}
void makeToCircular(Node** list, int begin)
{
        Node* r = *list;
        Node* p = *list;
        int cnt = begin;
        while(r->next != NULL)
        {
                r = r -> next;
                cnt--;
                if(cnt < 0)
                {
                        p = p -> next;
                }
        }
        r -> next = p;
        printf("Begin Node:%d\n", p->val);
}
/* #end */



/* ::#def tree :: */
struct tNode
{
        struct tNode* rchild;
        struct tNode* lchild;
        struct tNode* p;
        void* item;
};

typedef struct tNode tNode;

tNode* createTreeNode(void* item)
{
        tNode* tmp = (tNode*)malloc(sizeof(tNode));
        tmp->item = item;
        tmp->rchild = NULL;
        tmp->lchild = NULL;
        tmp->p = NULL;
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



/* ::#def bst :: */
/* include tree.l first*/
void print(void* item)
{
        printf("%d ", *(int*)item);
}
void appendData(tNode** root, tNode** tmp)
{
        tNode* r = *root;
        tNode* tchild = *tmp;
        int* ritem = (int*)r->item;
        int* titem = (int*)tchild->item;

        if(*titem < *ritem)
        {
                if(r->lchild == NULL)
                {
                        r->lchild = tchild;
                        tchild->p = r;
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
                        r->rchild = tchild;
                        tchild->p = r;
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
          
        appendData(root, &tmp);
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


void print_item(tNode* root)
{
        int* item = root->item;
        printf("%d ", *item);
}

void inOrder(tNode* root)
{
        if(root == NULL)
        {
                return;
        }
        inOrder(root->lchild);
        print_item(root);
        inOrder(root->rchild);        
}


tNode* findKeyNode(tNode* root , int key)
{
        if(root == NULL)
        {
                return;
        }
        int* item = root->item;
        if(key < *item)
        {
                findKeyNode(root->lchild, key);
        }
        else if(key > *item)
        {
                findKeyNode(root->rchild, key);
        }
        else
        {
                return root;
        }
}

tNode* findParent(tNode* root)
{
        if(root->p == NULL)
        {
                return NULL; //There is no next node;
        }
        tNode* c = root;
        root = root -> p;
        if(root->lchild == c)
        {
                return root;
        }
        else
        {
                findParent(root);
        }

}

tNode* findChild(tNode* root)
{
       if(root->lchild == NULL)
       {
               return root;
       } 
       else
       {
                return findChild(root->lchild);
       }
}

tNode* findNext(tNode* root)
{
        if(root->rchild == NULL)
        {
                return findParent(root);
        }
        else
        {
                return findChild(root->rchild);
        }
}

int main()
{
        int num = 20;
        int* arr = (int*)createArr(num, INT);
        print_arr(arr, num);
        tNode* root = createBSTRoot(arr, num);
        print_tree(root, print);
        printf("\n");
        inOrder(root);
        printf("\n");
        
        int i;
        for( i = 0 ; i < num ; i++ )
        {
                tNode* keyNode = findKeyNode(root, arr[i]);
                tNode* nextNode = findNext(keyNode);
                int* keyItem = keyNode->item;
                if(nextNode == NULL)
                {
                        printf("There is no next node\n");
                }
                else
                {
                        int* nextItem = nextNode->item;
                        printf("current:%d, next:%d\n", *keyItem, *nextItem);
                }
        }
        return 0;
}

