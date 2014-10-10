#include <stdio.h>
#include <stdlib.h>


int bigMul(int arr[], int n, int len)
{
	int i;
	int carry;
	for(i = 0 ; i < len ; i++)
	{
		int mult = arr[i] * n + carry;
		carry = mult / 10;
		arr[i] = mult % 10;
	}
	arr[i] = carry;
	return i + 1;
}

void display(int arr[], int len)
{
	for(int i = len - 1 ; i > -1 ; i--)
	{
		printf("%d", arr[i]);
	}
	printf("\n");
}


int main()
{
	int arr[10] = {1, 2, 3, 0, 0, 0 , 0 , 0 , 0, 0};
	int len = bigMul(arr , 5 , 3);
	display(arr, len);
        return 0;
}
