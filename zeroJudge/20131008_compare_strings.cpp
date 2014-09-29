#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void removeSpace(char str1[])
{
	int count = 0;
	int length = strlen(str1);
	for(int i = 0 ; i < length ; i++)
	{
		if(str1[i] != ' ')
		{
			str1[count++] = str1[i];
		}
	}
	str1[count++] = '\0';
}

int main()
{
	int n;
	while(scanf("%d\n" , &n)!=EOF)
	{
		char str1[50] = {0};
		char str2[50] = {0};
		int count = 0;
		while( n-- )
		{
			fgets(str1 , 50 , stdin);
			fgets(str2 , 50 , stdin);
			if( !strcmp(str1 , str2))
			{
				printf("Case %d: Yes\n" , ++count);
			}
			else
			{
				removeSpace(str1);
				removeSpace(str2);
				if( !strcmp(str1 , str2) )
				{
					printf("Case %d: Output Format Error\n" , ++count);
				}
				else
				{
					printf("Case %d: Wrong Answer\n" , ++count);
				}
			}

		}

	}
	return 0;
}
