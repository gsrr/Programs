
/*
 * Implement Queneu by two stacks
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
        int tag;
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

Stack* createStack(int num, int t)
{
        srand(time(NULL));
        int* arr = (int*)malloc(sizeof(int) * num);
        Stack* s = initialStack(arr, 0, num-1);
        s->tag = t;
        return s;
}

Stack* initialValue(Stack** s, int num)
{
        int i;
        for( i = 10 ; i > 0 ; i-- )
        {
                //int tmp = rand() % 100;       
                push(s , i);
        }
        print_stack(*s);

}

int isStackEmpry(Stack* s)
{
        if(s -> top == -1)
        {
                return 1;
        }
        return 0;
}
/* #end */

struct Queue
{
        Stack* s1;
        Stack* s2;
};
typedef struct Queue Queue;

//從s2 塞, s1拿取
void insert(Queue** q, int val)
{
        Stack* s = (*q)->s2;
        push(&s, val);       
}

void moveItem(Queue** q)
{
        Stack* s1 = (*q) -> s1;
        Stack* s2 = (*q) -> s2;
        while(isStackEmpry(s2) == 0)
        {
                int val = pop(&s2);
                push(&s1, val);
        }
}

int qRemove(Queue** q)
{
        Stack* s = (*q)->s1;
        if(isStackEmpry(s))
        {
                moveItem(q);
        } 
        int val = pop(&s);
        return val;
}

int main()
{
        Queue* q = (Queue*)malloc(sizeof(Queue));
        q->s1 = createStack(10, 1);
        q->s2 = createStack(10, 2);
        int i;
        for(i = 1 ; i < 10 ; i++)
        {
                insert(&q, i);
        }
        printf("queue:%d\n", qRemove(&q));
        printf("queue:%d\n", qRemove(&q));
        printf("queue:%d\n", qRemove(&q));
        printf("queue:%d\n", qRemove(&q));
        
        return 0;
}

