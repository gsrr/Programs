#include<stdio.h>
#include<stdlib.h>

int used[10]={0},xy[10][2];/*xy[][0]->x xy[][1]->y*/
int check(int x,int y)
{
        int a;
        for(a=1;a<x;a++)
                if(abs(xy[a][0]-x)==abs(xy[a][1]-y))
                        return 0;
        return 1;
}

int time=0,max;
int xx,yy;

void DFS(int now)/*now->x used->y*/
{
        int a,b,c;
        if(now==9)
        {
                if(xy[xx][1]==yy)
                {
                        time++;
                        printf(" %d      ",time);
                        for(a=1;a<=8;a++)
                                printf("%d ",xy[a][1]);
                        printf("\n");
                }
                return;
        }
        for(a=1;a<=8;a++) /*a->y*/
        {
                if(used[a]==0&&check(now,a)==1)
                {
                        xy[now][0]=now;
                        xy[now][1]=a;
                        used[a]=1;
                        DFS (now+1);
                        used[a]=0;
                }
        }
}

int main()
{
        int t;
        scanf("%d",&t);
        while(t--)
        {
                int a,b,c;
                scanf("%d %d",&yy,&xx);
                printf("SOLN       COLUMN\n\n");
                printf(" #      1 2 3 4 5 6 7 8\n");
                time=0;
                DFS(1);
        }
        return 0;
        /*  system("pause");*/
}
