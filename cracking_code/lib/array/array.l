


/* ::#def array :: */
int* createArr(int num)
{
        int* tmp = (int*)malloc(sizeof(int)* num);
        int i;
        for( i = 0 ; i < num ; i++)
        {
                tmp[i] = i+1;
        } 
        return tmp;
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
