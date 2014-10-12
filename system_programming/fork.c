#include <stdio.h>

int main()
{
        int a;
        int b;
        int childPid = fork();
        if(childPid == 0)
        {
                a = 1;
                b = 2;
                printf("This is child!!\n");
        }
        else if(childPid > 0)
        {
                int status;
                wait(&status);
                a = 2;
                b = 3;
                printf("This is parent , capture the child result:%d\n" , status/256);                       
        } 
        else
        {
                printf("fork error...\n");
        }
        printf("pid:%d , sum of (a,b):%d\n" , childPid , a+b);
        return a+b;
}
