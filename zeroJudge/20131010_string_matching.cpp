#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int string_match(char* str1 , char* str2)
{
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	
	int count = 0;
	for(int i = 0 ; i < len1 ; i++)
	{
		int j;
		for(j = 0 ; j < len2 ; j++)
		{
			if(str1[i+j] != str2[j])
			{
				break;
			}
		}

		if(j == len2)
		{
			count++;
		}
	}
	return count;
}

int main(int argc , char* argv[])
{
	char* str1 = argv[1];
	char* str2 = argv[2];
	printf("%d\n" , string_match(str1 , str2));
	return 0;
}
