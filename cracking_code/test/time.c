


#include <stdio.h>
#include <time.h>


int main()
{
	time_t timer;
	char buffer[32];
	struct tm* tm_info;

	time(&timer);
	tm_info = localtime(&timer);

	strftime(buffer, 32, "%Y:%m:%d %H:%M:%S", tm_info);
	printf("[%s]\n", buffer);
	return 0;
}
