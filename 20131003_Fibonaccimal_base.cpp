#include <stdio.h>
#include <stdlib.h>



void getFibNumber(int fib[] , int length)
{
	fib[0] = 0;
	fib[1] = 1;
	for(int i = 2 ; i < length ; i++)
	{
		fib[i] = fib[i-1] + fib[i-2];
	}
}

int main()
{
	int fib[46];
	getFibNumber(fib , 46);
	int n;

	while(scanf("%d" , &n) != EOF)
	{
		int m;
		for(int i= 0 ; i < n ; i++)
		{
			scanf("%d" , &m);
			printf("%d = " , m);
			int count = 45;
			while(m < fib[count])
			{
				count--;
			}

			while((m != 0 && m != 1) || count > 2)
			{
				if(m >= fib[count])
				{
					printf("1");
					m = m - fib[count];
				}
				else 
				{
					printf("0");
				}
				count--;
			}
			printf("%d (fib)\n" , m == 0 ? 0 : 1);
		}

	}
	return 0;
}
