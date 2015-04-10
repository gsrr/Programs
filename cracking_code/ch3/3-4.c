
/*
 * Hanoi Tower
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
/* #end */

void hanoi(Stack** s1, Stack** s2, Stack** s3, int n)
{
        if(n == 1)
        {
                int val = pop(s1);
                push(s3, val);
                printf("move plate %d from %d to %d\n", val, (*s1)->tag, (*s3)->tag);
                sleep(1);
                return;
        }
        hanoi(s1, s3, s2, n-1);
        hanoi(s1, s2, s3, 1);
        hanoi(s2, s1, s3, n-1);
}

int main()
{
        Stack* s1 = createStack(10, 1);
        initialValue(&s1, 10);
        print_stack(s1);
        Stack* s2 = createStack(10, 2);
        Stack* s3 = createStack(10, 3);
        hanoi(&s1, &s2, &s3, 10);
        print_stack(s3);
        return 0;
}

