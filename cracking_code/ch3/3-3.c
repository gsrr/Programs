
/*
 * stack set
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>





/* ::#def Stack :: */
struct Stack
{
        int* arr;
        int top;
        int b;
        int h;
        struct Stack* next;
};

typedef struct Stack Stack;
Stack* initialStack(int* arr, int b, int h)
{
        Stack* s = (Stack*)malloc(sizeof(Stack));
        s -> arr = arr;
        s -> b = b;
        s -> h = h;
        s -> top = b - 1;     
        return s;  
}

void push(Stack** s, int val)
{
        Stack* t = *s;
        if(t->top == t->h) 
        {
                printf("Stack is full!\n");
                return;
        }      
        t->top += 1;
        t->arr[t->top] = val;
}

int pop(Stack** s)
{
        Stack* t = *s;
        if(t->top == (t->b) - 1)
        {
                printf("Stack is empty!!\n");
        }
        int val = t->arr[t->top];
        t->top -= 1;
        return val;
        
}
void print_stack(Stack* s)
{
        int i;
        for( i = s->b ; i <= s->top ; i++)
        {
                printf("%d ", s->arr[i]);
        }
        printf("\n");
}

Stack* createStack(int num)
{
        srand(time(NULL));
        int* arr = (int*)malloc(sizeof(int) * num);
        Stack* s = initialStack(arr, 0, num-1);
        return s;
}
/* #end */

struct StackSet
{
        Stack* head;
};

typedef struct StackSet StackSet;


void setCreateStack(StackSet** ss)
{
        Stack* cur = createStack(10);
        cur->next = (*ss)->head;
        (*ss)->head = cur;
}

int isFull(Stack* s)
{
        if(s->top == s->h)
        {
                return 1;
        } 
        return 0;
}


int isEmpty(Stack* s)
{
        if(s->top == -1)
        {
                return 1;
        }
        return 0;
}

void setPush(StackSet** ss, int val)
{
        /*
         * 我打算在Set裡面使用一個stack list, 
         * 所以當有value 被push進來時, 首先要找到這個stack list的最後一個node.
         * 然後判斷該stack是否有空, 若沒有的話就建立新的stack, 否則就push value.
         */
                //setCreateStack(ss);
        
        if((*ss)->head == NULL)
        {
                setCreateStack(ss);
        }
        Stack* runner = (*ss)->head;
        push(&runner, val);
        if(isFull(runner))
        {
                setCreateStack(ss);
        }

}

void freeStack(StackSet** ss)
{
        Stack* tmp = (*ss) -> head;
        (*ss)->head = (*ss)->head->next;
        free(tmp);
}

int setPop(StackSet** ss)
{
        /*
         * 要pop時, 先找到最後一個stack, 然後取出value,
         * 若取出後為empty的話, 就刪除這個stack.
         */
        Stack* runner = (*ss) -> head;
        if(runner == NULL)
        {
                printf("Stack set is empty!!\n");
        }

        int val = pop(&runner);
        if(isEmpty(runner))
        {
                freeStack(ss);
        }
        return val;
}


void testPush(StackSet** ss)
{
        Stack* runner = (*ss)->head;
        int i;
        for( i = 2 ; i < 10 ; i++)
        {
                push(&runner, i);
        }
        print_stack(runner);
}

void print_stackSet(StackSet* ss)
{
        Stack* runner = ss->head;
        while(runner)
        {
                print_stack(runner);
                runner = runner->next;
        }
}


int main()
{
        StackSet* ss = (StackSet*)malloc(sizeof(StackSet));
        ss->head = NULL;
        /*
                setPush(&ss, 1);       
                setPush(&ss, 2);       
                setPush(&ss, 3);       
                setPush(&ss, 4);       
                setPush(&ss, 5);       
                setPush(&ss, 6);       
                setPush(&ss, 7);       
                setPush(&ss, 8);       
                setPush(&ss, 9);       
                setPush(&ss, 10);       
                */
        int i;
        for( i = 1 ; i < 20 ; i++)
        {
                setPush(&ss, i);       
        }
        print_stackSet(ss);
        return 0;
}

