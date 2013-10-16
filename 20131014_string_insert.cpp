#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int findPos(char str[])
{
	int max = str[0];
	int length = strlen(str);
	int pos = 0;
	for(int i = 1 ; i < length ; i++)
	{
		if(str[i] > max)
		{
			max = str[i];
			pos = i;	
		}
	}
	return pos;
}


void insertString(char str[] , char substr[] , int pos)
{
	int length = strlen(substr);
	int len1 = strlen(str);
	for(int i = len1 ; i > pos ; i--)
	{
		str[i + length] = str[i];
	}
	for(int i = 0 ; i < length ; i++)
	{
		str[++pos] = substr[i];
	}
}

int main()
{
	char str[20];
	char substr[10];
	while(scanf("%s %s" , str ,substr)!=EOF)
	{
		int max_pos = findPos(str);
		insertString(str , substr , max_pos);
		printf("%s\n" , str);
	}
	return 0;
}
