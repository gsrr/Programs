#include<stdio.h>
#include<stdlib.h>

int used[10]={0},board[10][2];/*xy[][0]->x xy[][1]->y*/
int check(int x,int y)
{
        int a;
        for(a=1;a<x;a++)
                if(abs(board[a][0] - x) == abs(board[a][1] - y))
                        return 0;
        return 1;
}

int time = 0 , max;


void print_permutation()
{
        time++;
        printf(" %d      ",time);
        int a;
        for(a = 1 ; a <= 8 ; a++)
                printf("%d ",board[a][1]);
        printf("\n");

}


int isValid(int index, int a)
{
        if(used[a] == 0 && check(index,a) == 1)
        {
                return 1;
        }
        return 0;
}

void DFS(int index, int x, int y)/*index->x used->y*/
{
        if(index == 9)
        {
                if(board[x][1] == y)
                {
                        print_permutation();
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
                        DFS (index+1, x, y);
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
                scanf("%d %d",&y,&x);
                printf("SOLN       COLUMN\n\n");
                printf(" #      1 2 3 4 5 6 7 8\n");
                time = 0;
                DFS(1, x, y);
        }
        return 0;
}
