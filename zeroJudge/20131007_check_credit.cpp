#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int n;
	int numArray[] = {0 , 1 , 2 , 3 , 4 , 5, 6 , 7, 8, 9, 1 , 2 ,3 , 4 , 5, 6, 7, 8, 9};
	while(scanf("%d\n" , &n) != EOF)
	{
		while( n-- )
		{
			char str[50] = {0};
			fgets(str , 50 , stdin);
			int length = strlen(str);
			int sum = 0;
			int count = 1;
			for( int i = 0 ; i < length ; i++ )
			{
				if(str[i] == ' ' || str[i]=='\n')
				{
					count = 1;
				}
				else
				{
					if(count % 2 == 0)
					{
						sum = sum + numArray[(str[i] - '0')];	
					}
					else
					{
						int num = (str[i] - '0') * 2;
						sum = sum + numArray[num];
					}
					count++;
				}
			}
			if(sum % 10 == 0)
			{
				printf("Valid\n");
			}
			else
			{
				printf("Invalid\n");
			}
		}
	}
	return 0;
}
