#include <stdio.h>


void hanoi(int n, char A, char B, char C) 
{
        if(n <= 0)
        {
                return;
        }      
        else if(n == 1)
        {
                printf("Move ring %d from %c to %c\n",n,A,C) ;
        } 
        else 
        {
                hanoi(n-1,A, C , B) ;
                printf("Move ring %d from %c to %c\n",n,A,C) ;
                hanoi(n-3,B, C, A);
                if(n -2 > 0)
                {
                        printf("Move ring %d from %c to %c\n",n-2 , B , C) ;
                }
        }
}

void hanoi_even(int n, char A, char B, char C) ;
void hanoi_odd(int n, char A, char B, char C) 
{

        if(n==1)
        { 
                printf("Move ring 1 from A to B\n") ;
        }
        else if(n==2)
        { 
                printf("Move ring 1 from A to B\n") ;
                printf("Move ring 2 from A to C\n") ;
        }
        else if(n == 3)
        {
                printf("Move ring 1 from A to B\n") ;
                printf("Move ring 2 from A to C\n") ;
                printf("Move ring 1 from B to C\n") ;
                printf("Move ring 3 from A to B\n") ;
                printf("Move ring 1 from C to B\n") ;
        }
        else 
        {
                hanoi(n , A, C, B);
                hanoi_even(n-3,A, B, C);
        }
}

void hanoi_even(int n, char A, char B, char C) 
{

        if(n==1)
        { 
                printf("Move ring 1 from A to B\n") ;
        }
        else if(n==2)
        { 
                printf("Move ring 1 from A to B\n") ;
                printf("Move ring 2 from A to C\n") ;
        }
        else if(n == 3)
        {
                printf("Move ring 1 from A to B\n") ;
                printf("Move ring 2 from A to C\n") ;
                printf("Move ring 1 from B to C\n") ;
                printf("Move ring 3 from A to B\n") ;
                printf("Move ring 1 from C to B\n") ;
        }
        else 
        {
                hanoi(n , A, B, C);
                hanoi_odd(n-3,A, C, B) ;
        }
}

int n; 
int main()
{
        while(scanf("%d",&n)==1) 
        {
                hanoi_even(n,'A','B','C');                    
                printf("\n") ;
        } 
        return 0;
}
