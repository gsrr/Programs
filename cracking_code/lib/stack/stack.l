


/* ::#def Stack :: */
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

Stack* createStack(int num)
{
        srand(time(NULL));
        int* arr = (int*)malloc(sizeof(int) * num);
        Stack* s = initialStack(arr, 0, num-1);
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
