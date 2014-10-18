#include <stdio.h>
#include <stdlib.h>

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

void displayArr(int arr[], int len)
{
        for(int i = 0 ; i < len ; i++)
        {
                printf("%d ", arr[i]);
        }
        printf("\n");
}

int sumArray(int arr[], int len)
{
	int sum = 0;
	for(int i = 0 ; i < len ; i++)
	{
		sum += arr[i];
	}
	return sum;
}

int getInt(int *n)
{
	scanf("%d", n);
	return 1;
}

int printInt(int n)
{
	printf("%d\n", n);
}

int main()
{
	int arr[10000] = {0};
	arr[0] = 1;
	int len = 1;
	int sumArr[1000] = {0};
	sumArr[0] = 1;
	for(int i = 1 ; i <= 1000 ; i++)
	{
		len = bigMul(arr, i, len);
		sumArr[i] = sumArray(arr, len);
	}
	int n = 0;
	while(scanf("%d", &n) != EOF)
	{	
		printInt(sumArr[n]);
	}
}

