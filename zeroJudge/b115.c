
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void swapChar(char str[], int i , int j);
void reverseStr(char str[]);
int isBigger(char fir[] , char sec[]);
void bigDivide(char num1[] , char num2[] , char quot[]);
void bigSub(char num1[] , char num2[]);
void removeFrontZero(char quot[]);
int bigMul(int arr[], int n, int len);
int bigMul_char(char arr[], int n, int len);
int sumArray(int arr[], int len);

void swapChar(char str[], int i , int j)
{
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
}

void reverseStr(char str[])
{
        int len = strlen(str);
        int i;
        for( i = 0 ; i < len/2; i++ )
        {
                swapChar(str, i, len - 1 - i);
        }
}

int isBigger(char fir[] , char sec[])
{
        int len_fir = strlen(fir);
        int len_sec = strlen(sec);
        if(len_fir < len_sec)
        {
                return 0;
        }
        else if(len_fir > len_sec)
        {
                return 1;
        }
        else
        {
                int i;
                for( i = len_fir - 1 ; i > -1 ; i--)
                {
                        if(fir[i] > sec[i])
                        {
                                return 1;
                        }
                        else if(fir[i] < sec[i])
                        {
                                return 0;
                        }
                }
                return 1;
        }

        
}

void removeFrontZero(char quot[])
{
	int i;
	for(i = 0 ; i < strlen(quot); i++)
	{
		if(quot[i] != '0')
		{
			break;
		}
	}
	int j = 0;
	for( i ; i < strlen(quot); i++,j++)
	{
		quot[j] = quot[i];
	}
	quot[j] = '\0';
	
}


void bigDivide(char num1[] , char num2[] , char quot[])
{
	if(strcmp(num1 , "0") == 0)
	{
		quot[0] = '0';
		quot[1] = '\0';
		return;
	}
	char *temp = (char*)malloc(sizeof(char) * strlen(num1));
	int len1 = strlen(num1);
	int i;
	int j = 0;
	for( i = 0 ; i < len1 ; i++)
	{
		temp[j] = num1[len1-i-1];
		temp[j+1] = '\0';
		reverseStr(temp);
		int cnt = 0;
		while(isBigger(temp , num2))
		{
			bigSub(temp, num2);
			cnt++;
		}
		reverseStr(temp);
		quot[i] = cnt + '0';

                if(strcmp(temp, "0") == 0)
                {
                        j = 0;
                }
                else
                {
                        j++;
                }
	}
	quot[i] = '\0';
	removeFrontZero(quot);
	reverseStr(quot);
	free(temp);
}

void bigSub(char num1[] , char num2[])
{
	int i;
	for(i = 0 ; i < strlen(num1) ; i++)
	{
		if(num1[i] >= num2[i])
		{
			num1[i] = num1[i] - num2[i] + '0';
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
			num1[i] = (num1[i] + 10 - num2[i]) + '0';
		}
	}
	
	int j;
	for( j = i - 1 ; j > 0 ; j--)
	{
		if(num1[j] != '0')
		{
			break;
		}
	}
	num1[j+1] = '\0';
	
}

void bigAdd(char fir[], char sec[])
{
	int lenFir = strlen(fir);
	int lenSec = strlen(sec);
	int i;
	int carry = 0;
	for( i = 0 ; i < lenFir || i < lenSec; i++)
	{
		int tmpFir = ( i < lenFir ) ? fir[i] - '0' : 0;
		int tmpSec = ( i < lenSec ) ? sec[i] - '0' : 0;
		int sum = tmpFir + tmpSec + carry;
		carry = sum / 10;
		fir[i] = (sum % 10) + '0';
	}
	if(carry == 0)
	{
		fir[i] = '\0';
	}
	else
	{
		
		fir[i] = carry + '0';
		fir[i+1] = '\0';
	}
}
void getMultTemp(char arr[], int index)
{
	reverseStr(arr);
	int len = strlen(arr);
	int i;
	for( i = len ; i < len + index ; i++ )
	{
		
		arr[i] = '0';	
	}
	arr[i] = '\0';
	reverseStr(arr);
}
void bigMulChar(char fir[], char sec[], char ret[])
{
	if(strcmp(fir , "0") == 0 || strcmp(sec , "0") == 0)
	{
		ret[0] = '0';
		ret[1] = '\0';
		return;
	}
	int lenSec = strlen(sec);
	int i;
	for( i = 0 ; i < lenSec; i++)
	{
		char *temp = (char*)malloc(sizeof(char) * (strlen(fir) + 1 + i));
		strcpy(temp, fir);
		getMultTemp(temp, i);
		bigMul_char(temp, sec[i] - '0', strlen(temp));
		bigAdd(ret, temp);
		free(temp);
	}
}

int bigMul_char(char arr[], int n, int len)
{
	int i;
	int carry = 0;
	for(i = 0 ; i < len ; i++)
	{
		int mult = (arr[i] - '0') * n + carry;
		carry = mult / 10;
		arr[i] = (mult % 10) + '0';
	}
	if(carry != 0)
	{
		for( i ; carry != 0 ; i++)
		{
			arr[i] = (carry % 10) + '0';
			carry = carry / 10;
		}
	}
	arr[i] = '\0';
}
int bigMul(int arr[], int n, int len)
{
	int i;
	int carry = 0;
	for(i = 0 ; i < len ; i++)
	{
		int mult = arr[i] * n + carry;
		carry = mult / 10;
		arr[i] = mult % 10;
	}
	if(carry != 0)
	{
		int j;
		for( j = i ; carry != 0 ; j++)
		{
			arr[j] = carry % 10;
			carry = carry / 10;
		}
		return j;
	}
	else
	{
		return i;
	}
}
int sumArray(int arr[], int len)
{
	int sum = 0;
	int i;
	for(i = 0 ; i < len ; i++)
	{
		sum += arr[i];
	}
	return sum;
}
int main()
{
	char num1[100];
	char num2[100];
	char op[2];
	while(scanf("%s",num1) != EOF)
	{
		getchar();
		scanf("%s", op);
		scanf("%s", num2);
		reverseStr(num1);
		reverseStr(num2);

		char ret[100] = {0};
			if(op[0] == '*')
			{
				bigMulChar(num1, num2, ret);
			}
			else
			{
				bigDivide(num1, num2, ret);
			}
			reverseStr(ret);
			printf("%s\n", ret);
	}
	return 0;
}
