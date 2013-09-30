#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void reverse(char binary[])
{
	int length = strlen(binary) - 1;
	for(int i = 0 ; i < length/2 + 1 ; i++)
	{
		char temp = binary[i];
		binary[i] = binary[length - i];
		binary[length - i] = temp;
	}
}

int main()
{
	int n;
	while(scanf("%d" , &n) != EOF && n != 0)
	{
		char binary[32] = {0};
		int index = 0;
		int count = 0;
		while(n != 0)
		{
			binary[index++] = n % 2 + 48;
			count = count + n%2;
			n = n / 2;
		}
		binary[index] = '\0';
		reverse(binary);
		printf("The parity of %s is %d (mod 2).\n" , binary , count);

	}
	return 0;
}
