#include <stdio.h>
#include <stdlib.h>



void add(int* arr , int num , int len)
{
	for(int i = 0 ; i < len ; i++)
	{
		arr[i] = (arr[i] + num) % 65536;
	}
}

int query(int* arr , int num , int len)
{
	int count = 0 ;
	for(int i = 0 ; i < len ; i++)
	{
		int temp = arr[i];
		for(int j = 0 ; j  < num; j++)
		{
			temp = temp / 2;
		}
		if(temp %2 ==1)
		{
			count++;
		}
	}
	return count;
}

int main()
{
	int n, m;
	while(scanf("%d %d" , &n , &m) != EOF)
	{
		int* arr = (int*)malloc(n * sizeof(int));
		for(int i = 0 ; i < n ; i++)
		{
			scanf("%d" , arr + i);
		}
		char cmd;
		int num;
		for(int i = 0 ; i < m ; i++)
		{
			getchar();
			scanf("%c %d", &cmd , &num);
			if(cmd == 'Q')
			{
				printf("%d\n" , query(arr , num , n));
			}
			else
			{
				add(arr , num , n);
			}
		}
		free(arr);
	}
	return 0;
}
