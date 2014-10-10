


/* bigMul:start */
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
/* bigMul:end */
