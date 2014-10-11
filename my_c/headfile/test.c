#include <stdio.h>
#include "bigNum.h"


void displayArr(char arr[], int len)
{
	int i;
        for(i = 0 ; i < len ; i++)
        {
                printf("%c ", arr[i]);
        }
        printf("\n");
}
int main()
{
	char num1[50] = "12346587987654321";
	char num2[20] = "98765432123456789";
	num1[17] = '\0';
	num2[17] = '\0';
	char ret[100] = {0};
	reverseStr(num1);
	reverseStr(num2);
	bigMulChar(num1, num2, ret);
	displayArr(ret, strlen(ret));
	
	return 0;
}
