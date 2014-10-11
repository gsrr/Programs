#include <stdio.h>
#include <string.h>


/* myHead : swapChar : start */
void swapChar(char str[], int i , int j)
{
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
}
/* myHead : swapChar : end */

/* myHead : reverseStr : start */
void reverseStr(char str[])
{
        int len = strlen(str);
        int i;
        for( i = 0 ; i < len/2; i++ )
        {
                swapChar(str, i, len - 1 - i);
        }
}
/* myHead : reverseStr : end */

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


/* myHead : bigDivide : start */
void bigDivide(char num1[] , char num2[] , char quot[])
{
	char *temp = (char*)malloc(sizeof(char) * strlen(num1));
	int len1 = strlen(num1)
	int i;
	for( i = 0 ; i < len1 ;)
	{
		temp[i] = num1[len1-i-1];
		temp[i+1] = '\0';
		reverseStr(temp);
		int cnt = 0;
		while(isBigger(temp , num2))
		{
			bigSub(temp, num2);
			cnt++;
		}
		reverseStr(temp);
		quot[i] = cnt + '0';

                if(strcom(temp. "0") == 0)
                {
                        i = 0;
                }
                else
                {
                        i++;
                }
	}
}

/* myHead : bigDivide : end */

/* myHead : bigSub : start */
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
	for( j = i - 1 ; j > -1 ; j--)
	{
		if(num[j] != '0')
		{
			num[j+1] = '\0';
			break;
		}
	}
}
/* myHead : bigSub : end */

/* myHead:bigMul:start */
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
/* myHead:bigMul:end */
/* myHead:sumArray:start */
int sumArray(int arr[], int len)
{
	int sum = 0;
	for(int i = 0 ; i < len ; i++)
	{
		sum += arr[i];
	}
	return sum;
}
/* myHead:sunArray:end */
