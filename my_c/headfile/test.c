#include <stdio.h>
#include "bigNum.h"


int main()
{
	char num2[11] = "1234567890";
	char num1[21] = "12345678901234567890";
	num1[20] = '\0';
	num2[10] = '\0';
	char quot[30];
	reverseStr(num2);
	reverseStr(num1);
	int r = isBigger(num1,num2);
	if(r == 1)
	{
		bigDivide(num1, num2, quot);
		
	}
	/*
	if(isBigger(num1 , num2))
	{
	}
	else
	{
		printf("here2");
		bigDivide(num2, num1, quot);
		printf("-");
	}
	*/
	printf("%s\n", quot);
	
	return 0;
}
