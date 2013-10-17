#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */ 
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <sys/wait.h>   /* Wait for Process Termination */
#include <stdlib.h>     /* General Utilities */



int main()
{
	int retval;
	int status;

	pid_t childPid = fork();

	if(childPid >= 0)
	{
		if(childPid == 0)
		{
			printf("This is child\n");
			sleep(1);
			printf("Enter exit value: ");
			scanf("%d" , &retval);
			exit(retval);
		}
		else
		{
			printf("Parent: I am the parent process\n");
			printf("Parent: I am waiting for my child to exit\n");
			wait(&status);
			printf("Parent: Child's exit code is:%d\n" , status/256);
			exit(0);
		}
	}
	else
	{
		perror("fork error\n");
		exit(0);
	}

}
