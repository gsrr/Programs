#include<stdio.h>
#include<stdlib.h>
int number[1000000]; 
main()
{
        int n,m,a,b;
        scanf("%d",&n);
        while(n--)
        {
                scanf("%d",&m);
                int begin=0,max=0; 
                for(a=0 ; a<m ; a++) 
                { 
                        scanf("%d",&number[a]);
                        for( b = begin ; b<a ; b++ )
                        {
                                if( number[b] == number[a] ) 
                                {
                                        begin = b; 
                                }
                        
}
printf("%d : %d : %d\n", b, a, a - begin);
                        if( b == a && max < a - begin ) 
                        {
                                max = a - begin;
                        }
                } 
                printf("%d\n",max); 
        } 
        return 0;
}
