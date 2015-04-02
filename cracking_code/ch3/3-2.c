
/*
 * min() operation for stack
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
        int minCnt;
        int* min;
};

typedef struct Stack Stack;
Stack* initialStack(int* arr, int b, int h)
{
        Stack* s = (Stack*)malloc(sizeof(Stack));
        s -> arr = arr;
        s -> b = b;
        s -> h = h - 1;
        s -> top = b - 1;
        s -> min = (int*)malloc(sizeof(int) * h);  
        s -> minCnt = -1;
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
        if(t->top == -1 || val < (t->min)[t->minCnt])
        {
                t->minCnt += 1;
                (t->min)[t->minCnt] = val;
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
        int ret = t->arr[t->top];
        if(ret == (t->min)[t->minCnt])
        {
                t->minCnt -= 1;
        }
        t->top -= 1;
        return ret;
        
}

int min(Stack* s)
{
        if(s-> top == -1)
        {
                printf("Stack is empty!!\n");
                return;
        }
        return s->min[s->minCnt];
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
        Stack* s = initialStack(arr, 0, num);
        int i;
        for( i = 0 ; i < num ; i++ )
        {
                int tmp = rand() % 100;       
                push(&s , tmp);
        }
        print_stack(s);
        return s;
}
/* #end */

int main()
{
        Stack* s = createStack(10);
        print_stack(s);
        printf("min:%d\n", min(s));
        pop(&s);
        pop(&s);
        pop(&s);
        pop(&s);
        print_stack(s);
        printf("min:%d\n", min(s));

        return 0;
}

