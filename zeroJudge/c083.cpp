#include<stdio.h>
#include<stdlib.h>


void initial(int index[], int n)
{
        for(int i=0; i<n; i++)
                index[i] = i+1;
}


int getVictim(int index[] , int n, int k, int pos)
{
        int count = 0;
        while(count < k)//數k個人 
        {
                pos = pos % n;
                if(index[pos])//數人 
                {
                        count++;
                        if(count == k)
                                break;
                }
                pos++;
        }
        return pos;
}


int getAlternate(int index[], int n, int k, int pos)
{
        return getVictim(index, n , k , pos);
}

int main()
{
        int index[100];
        int n,k;

        while(scanf("%d %d",&n,&k) != EOF)
        {
                if (n == 0 && k ==0)
                        break;
                
                initial(index, n);

                
                if(n == 1)
                {
                        printf("%d\n",n);
                }
                else
                {
                        int r = n;
                        int roulette = -1;
                        while(r > 1) 
                        {
                                roulette = getVictim(index, n, k, roulette + 1);
                                index[roulette] = 0; 

                                int temp = getAlternate(index, n , k , roulette + 1);

                                index[roulette] = index[temp];//補位 
                                index[temp] = 0;//空位 
                                r--;
                        }
                        int ans = 1 + (1-index[roulette]) + n;
                        if(ans>n)
                                ans -= n;
                        printf("%d\n",ans);
                }


        }
}
