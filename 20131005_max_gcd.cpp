#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gcd(int a , int b)
{
	int t;
	while( b != 0)
	{
		t = a;
		a = b;
		b = t % b;
	}
	return a;
	
}

int compare(const void* a , const void* b)
{
	return -1*(*(int*)a - *(int*)b);
}


int* split(char* line , char del , int* length)
{
	int str_len = strlen(line);
	int* numArray = (int*)malloc(101 * sizeof(int));
	int num = 0;
	for(int i = 0 ; i <= str_len ; i++)
	{
		if(line[i] >= '0' && line[i] <= '9')
		{
			num = num * 10 + (line[i] - '0');
		}
		else
		{
			if(num != 0)
			{
				numArray[*length] = num;
				*length = *length + 1;
			}
			num = 0;
		}
	}
	qsort(numArray , *length , sizeof(int) , compare);
	return numArray;
}




int main()
{
	int n;
	while(scanf("%d\n" , &n) != EOF)
	{
		while(n--)
		{
			char str[5000] = {0};
			int length = 0;
			fgets(str, sizeof(str), stdin);
			int* numArray = split(str , ' ' , &length);
			
			int max_gcd = 0;
			for(int i = 0 ; i < length ; i++)
			{
				if(max_gcd >= numArray[i])
				{
					break;
				}
				for(int j = i+1 ; j < length ; j++)
				{
					if(max_gcd >= numArray[j])
					{
						break;
					}
					else
					{
						int temp = gcd(numArray[i] , numArray[j]);
						max_gcd = max_gcd > temp ? max_gcd : temp;
					}
				}
			}
			printf("%d\n" , max_gcd );

			free(numArray);
		}
	}
	
	return 0;
}
