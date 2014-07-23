
#include<stdio.h>
#include<stdlib.h>

int used[10]={0},board[10][2];
int map[8][8];

int check(int x,int y)
{
        int a;
        for(a=1;a<x;a++)
                if(abs(board[a][0] - x) == abs(board[a][1] - y))
                        return 0;
        return 1;
}

int max;


int print_permutation()
{
        int sum = 0;
        int a;
        for(a = 1 ; a <= 8 ; a++)
        {
                sum = sum + map[board[a][0] - 1][board[a][1] - 1];
        }
        return sum;

}


int isValid(int index, int a)
{
        if(used[a] == 0 && check(index,a) == 1)
        {
                return 1;
        }
        return 0;
}

void DFS(int index)/*index->x used->y*/
{
        if(index == 9)
        {
                int tmp_max = print_permutation();
                if(tmp_max > max)
                {
                        max = tmp_max;
                }
                return;
        }

        int a;
        for(a = 1; a <= 8 ; a++) /*a->y*/
        {
                if(isValid(index, a))
                {
                        board[index][0] = index;
                        board[index][1] = a;
                        used[a] = 1;
                        DFS (index+1);
                        used[a] = 0;
                }
        }
}

int main()
{
        int t;
        int x , y;
        scanf("%d",&t);
        while(t--)
        {
                int a,b;
                for(a = 0 ; a < 8 ; a++)
                {
                        for (b = 0 ; b < 8 ; b++)
                        {
                                scanf("%d", &map[a][b]);
                        }
                }
                max = 0;
                DFS(1);
                printf("%d\n",max);
        }
        return 0;
}
