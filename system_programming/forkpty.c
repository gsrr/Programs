#include<stdio.h>
#include <pty.h>
#include <string.h>
#include <unistd.h>


void print_message(int fd)
{
	char buffer[100] = {0};
	read(fd, buffer, 100);
	printf("Message from child:%s\n", buffer);
	sleep(1);
}

int main()
{
	int fd = -1;
	int pid = forkpty(&fd, NULL, NULL, NULL);
	if(pid == 0)
	{
		printf("Child process:%d\n", pid);
		fflush(stdout);
		execlp("python", "execute python program", "../python/pyecho.py", NULL);
	}
	else
	{
		printf("Parent process:%d:%d\n", pid,fd);
		print_message(fd);
		print_message(fd);
		write(fd, "message one\n", strlen("message one\n"));
		print_message(fd);
		print_message(fd);
	}
	return 0;
}
