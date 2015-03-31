
/*
 * stack
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/*::#def Stack.l ::*/
struct Stack
{
        int* arr;
        int top;
        int b;
        int h;
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

void pop(Stack** s)
{
        Stack* t = *s;
        if(t->top == (t->b) - 1)
        {
                printf("Stack is empty!!\n");
        }
        t->top -= 1;

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

Stack* createStackByIndex(int* arr, int btm, int top)
{
        sleep(1);
        srand(time(NULL));
        Stack* s = initialStack(arr, btm, top);
        int i;
        for( i = btm ; i <= top ; i++ )
        {
                int tmp = rand() % 100;       
                push(&s , tmp);
        }
        print_stack(s);
        return s;
}

Stack* createStack(int num)
{
        int* arr = (int*)malloc(sizeof(int) * num);
        return createStackByIndex(arr, 0, num-1);
}
/*::#end Stack.l ::*/

int main()
{
        Stack* s = createStack(10);
        pop(&s);
        print_stack(s);
        int* arr = (int*) malloc(sizeof(int) * 10);
        
        Stack* s1 = createStackByIndex(arr, 0, 3);
        Stack* s2 = createStackByIndex(arr, 4, 6);
        Stack* s3 = createStackByIndex(arr, 7, 9);

        return 0;
}

