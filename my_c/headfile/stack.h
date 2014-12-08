#include <stdio.h>


typedef struct stack{
        int *elem;
        int size;
        int top;
}Stack;


Stack create(Stack s, int num){
        s->elem = (int*)malloc(sizeof(int) * num) ;
        s->size = num;
        s->top = -1;
}

void push(Stack s, int elem){
        if( s->top == s->size)
        {
                printf("full\n");
                return;
        }
        s->top += 1;
        s->elem[s->top] = elem;
}

int pop(Stack s)
{
        if(s->top == -1)
        {
                printf("empty\n");
                return;
        }
        int ret = s->elem[s->top];
        s->top -= 1;
        return ret;
}
