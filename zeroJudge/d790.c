#include <stdio.h>
#include <string.h>



int getNextZeroPosition(char str[])
{
        int n = strlen(str);
        for (int k = n - 1 ; k > 0 ; k--)
        {
                if(str[k-1] < str[k])
                {
                        return k;
                }
        }
        return 0;
}

void swapWithZero(char str[], int next)
{
        int v;
        v = str[next];
        str[next] = str[next-1];
        str[next-1] = v;
}

int cleanAllBehindPos(char str[], int next)
{
        int times = 0;
        int n = strlen(str);
        for(int k = n-1 ; k>next-1 ; k--)
        {
                if(str[k] == '1') times++;
                str[k] = '0';
        }
        return times;
}
void reSetOneFromright(char str[], int times)
{
        int n = strlen(str);
        for(int k=n-1 ; times != 0 ; k--, times--)
        {
                str[k] = '1';
        }
}


void setInitialString(char str[], int n, int h)
{
        for(int j=0 ; j < n ; j++)
        {
                if(j < n-h)
                {
                        str[j] = '0';
                }
                else
                {
                        str[j] = '1';
                }
        }
        str[n] = '\0';

}
int main()
{
        int t;
        scanf("%d",&t);

        int i;
        for(i=0;i<t;i++)
        {
                int n,h;
                scanf("%d %d",&n,&h);
                char str[20];
                setInitialString(str, n, h);
                while(1)
                {
                        printf("%s\n",str);
                        int next = getNextZeroPosition(str);
                        if(next == 0) 
                        {
                                printf("\n"); 
                                break;
                        }
                        else
                        {
                                swapWithZero(str, next);
                                int nums = cleanAllBehindPos(str, next); 
                                reSetOneFromright(str, nums);
                        }
                }
        }

        return 0;
}
