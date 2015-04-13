

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

