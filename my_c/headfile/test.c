#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void reverse(char num[])
{
	int length = strlen(num);
	for(int i = 0 ; i < length/2 ; i++)
	{
		char temp = num[i];
		num[i] = num[length-1-i];
		num[length-1-i] = temp;
	}
}

int addition(char num1[] , char num2[] , char num3[])
{
	int length = 0;
	int quot = 0;
	for(int i = 0 ; i < strlen(num1) ; i++)
	{
		int sum = (num1[i] - 48) + quot + (num2[i] - 48);
		num3[length++] = sum % 10;
		quot = sum / 10;
	}
	if(quot != 0)
	{
		num3[length++] = quot;
	}
	num3[length] = '\0';
	return length;
}

int subtraction(char num1[] , char num2[] , char num3[])
{
	int length = 0;
	int diff = strlen(num1) - strlen(num2);
	for(int i = 0 ; i < strlen(num1) && i < strlen(num2) ; i++)
	{
		if(num1[i] >= num2[i])
		{
			num3[length++] = num1[i] - num2[i] + '0';
		}
		else
		{
			int j;
			for(j = i+1 ; j < strlen(num1) ; j++)
			{
				if(num1[j] > '0')
				{
					num1[j] = num1[j]-1;
					break;
				}
				else
				{
					num1[j] = 9 + '0';
				}
			}
			num3[length++] = (num1[i] + 10 - num2[i]) + '0';
		}
	}

	for(length ; length < strlen(num1) ; length++)
	{
		num3[length] = num1[length];
	}
	num3[length] = '\0';
	return length;
}

int multip(char num1[] , char num2[] , char num3[])
{
	int length = 0;
	int num3_length = 0;
	char temp[500] = {48};
	for(int i = 0 ; i < 500 ; i++)
	{
		num3[i] = num3[i] + 48;
	}
	for(int i = 0 ; i < strlen(num1) ; i++)
	{
		for(int j = 0 ; j < 500 ; j++)
		{
			temp[j] = 48;
		}
		int length = i;
		int quo = 0;
		for(int j=0 ; j < strlen(num2) ; j++)
		{
			int multi_sum = (num1[i]-48)*(num2[j]-48) + quo;
			temp[length++] = multi_sum % 10 + 48;
			quo = multi_sum / 10;
		}
		if(quo != 0 )
		{
			temp[length++] = quo + 48;
		}

		temp[length] = '\0';
		for(int i = 0 ; i < num3_length ; i++)
		{
			num3[i] = num3[i] + 48;
		}
		num3[num3_length] = 48;
		num3_length = addition(temp , num3 , num3);
	}
	return num3_length ;
}


int compareSmall(char num1[] , char num2[])
{
	if(strlen(num2) > strlen(num1))
	{
		return 0;
	}
	else if(strlen(num2) == strlen(num1))
	{
		if(num2[strlen(num2) - 1] > num1[strlen(num1) - 1])
		{
			return 0;
		}
	}
	return 1;
}

int divide(char num1[] , char num2[] , char num3[])
{
	int length = 0;
	char temp[500];
	for(int i = 0 ; i < 500 ; i++)
	{
		temp[i] = num1[i];
		num3[i] = 48;
	}
	while(compareSmall(temp , num2) == 1)
	{
		int temp_length = subtraction(temp , num2 , temp);
		num3[0] = num3[0] + 1;
		int i = 0 ;
		while(num3[i] > '9')
		{
			num3[i] = '0';
			num3[i+1] = num3[i+1] + 1;
			i++;
		}
		if(length <= i)
		{
			length = i+1;
		}
		printf("%s " , temp);
	}
	num3[length] = '\0';
	return length;
}

void divide_small(char num1[] , char num2[] , char num3[])
{
	reverse(num2);
	int number = atoi(num2);
	int count = 0;
	int temp = 0;
	int flag = 0;
	for(int i = strlen(num1)-1 ; i > -1 ; i--)
	{
		temp = temp*10 + (num1[i] - '0');
		if(temp >= number)
		{	
			flag = 1;
			num3[count++] = (temp / number) + '0';
			temp = temp % number;
		}
		else if(flag == 1)
		{
			num3[count++] = '0';
		}
	}
	num3[count] = '\0';
}


int main()
{
	char num1[500];
	char num2[500];
	char op;
	int count = 0;

	while((scanf("%s %c %s" , num1 , &op , num2))!=EOF)
	{
		int length = 0;
		char num3[500] = {0};

		count++;
		if(count == 9)
		{
			printf("%c %s\n" , op , num2);
		}

		reverse(num1);
		reverse(num2);
		switch(op)
		{
			case '+':
				length = addition(num1 , num2 , num3);
				for(int i = length -1 ; i > -1 ; i--)
				{
					printf("%d" , num3[i]);
				}
				break;
			case '-':
				if(compareSmall(num1 , num2) == 1)
				{
					length = subtraction(num1 , num2 , num3);
				}
				else
				{
					length = subtraction(num2 , num1 , num3);
					printf("-");
				}
				reverse(num3);
				printf("%s" , num3);
				break;
			case '*':
				length = multip(num1 , num2 , num3);
				for(int i = length -1 ; i > -1 ; i--)
				{
					printf("%d" , num3[i]);
				}
				break;
			case '/':
				if(strlen(num2) > 5)
				{
					length = divide(num1 , num2 , num3);
				}
				else if (strlen(num1) < strlen(num2))
				{
					printf("0");
					break;
				}
				else
				{
					divide_small(num1 , num2 , num3);
				}

				printf("%s" , num3);
				break;
		}

		putchar('\n');


	}

	return 0;
}

