#include<stdio.h>   
#include<stdlib.h>   
#include<string.h>   
#include<math.h>   
int math[1001][2601];                  
main()   
{   

        int a,b,n;                             
        math[0][0]=1;math[1][0]=1;          
        for(a=2;a<1001;a++)   
        {   
                for(b=0;b<2600;b++)   
                {                               
                        math[a][b]=math[a][b]+math[a-1][b]*a;   
                        if (math[a][b]>=10)   
                        {   
                                math[a][b+1]=math[a][b+1]+math[a][b]/10;   
                                math[a][b]=math[a][b]%10;   
                        }   
                }   
        }    
        while(scanf("%d",&n)==1)   
        {   
                printf("%d!\n",n);    
                for(a=2599;a>=0;a--)   
                {   
                        if(math[n][a]!=0)   
                        {   
                                for(b=a;b>=0;b--)   
                                        printf("%d",math[n][b]);   
                                break;   
                        }    
                }   
                printf("\n");   
        }   
        return 0;   
}
