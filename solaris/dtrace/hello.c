#include <stdio.h>
#include <string.h>



char* print_hello_str(char *input)
{
	printf("hello input:%s\n", input);
	return "hello_input";
}

int print_hello()
{
	int cnt = 0;
	printf("Hello : %d\n", strlen("Hello"));
	return 2;
}

int
main(int argc, char **argv) {
	int ret = print_hello();
	printf("ret:%d\n", ret);
	char *char_ret = print_hello_str("I am super man");
	printf("char_ret:%s\n", char_ret);
	sleep(2);
	return (0);
}

