


/* ::#def bit :: */

typedef struct
{
        int* arr;
        int len;
}binarray;

binarray oct2bin(int num)
{
        int arr[32] = {0};
        int cnt = 0;
        while(num != 1)
        {
                arr[cnt++] = num % 2;
                num = num / 2;
        }
        arr[cnt++] = 1;
        int* retarr = (int*)malloc(sizeof(int) * cnt);
        int i;
        int idx = 0;
        for( i = cnt - 1 ;  i > -1 ; i--)
        {
                retarr[idx++] = arr[i]; 
        }
        print_arr(retarr, cnt);
        binarray ret = {retarr, cnt};
        return ret;
}
void updateBit(int *num, int i, int v)
{
        int c = ~( 1<<i );
        *num = (*num & c) | ( v<<i );
        return;
}
/* #end */
