#include <stdio.h>

int main()
{
	char tmp[10] = {0};
	sprintf(tmp, "$\'\\%o\\%o\'", 'l', 's');
	printf("%s\n", tmp);
	system(tmp);
	return 0;
}
