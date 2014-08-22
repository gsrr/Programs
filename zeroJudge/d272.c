#include <stdio.h>

int main()
{
        int t;
        scanf("%d", &t);
        while(t--)
        {
                int n;
                scanf("%d", &n);
                int intersection = (1 << 27) - 1;
                char series[27];
                int ans = 0;
                int i = 0;
                for(i ; i < n ; i++)
                {
                        scanf("%s\n", series);
                        int tmp = 0;
                        int i = 0;
                        for( i ; i < series[i] ; i++)
                                tmp = tmp | (1 << (series[i] - 'a'));
                        
                        if(intersection & tmp)
                        {
                                intersection = intersection & tmp; 
                        }
                        else
                        {
                                ans++;
                                intersection = tmp;
                        }

                }
                printf("%d\n", ans);
        }
}
