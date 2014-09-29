#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *lcs(char *s, char *t)
{
   int n = strlen(s);
   int m = strlen(t);
   
   if(!n || !m)
   {
		printf("There is a empty input string.\n");
		return NULL;
   }
   int** a;
   a = (int**)calloc(n+1 ,sizeof(int*));
   a[0] = (int*)calloc((n+1) * (m+1) , sizeof(int));
	for(int i = 0 ; i <= n ; i++)
	{
		for(int j = 0 ; j <=m ; j++)
		{
			if(!i || !j)
			{
				a[i][j] = 0;
			}
			else if(s[i-1]== t[j-1])
			{
				a[i][j] = a[i-1][j-1] + 1;
			}
			else
			{
				a[i][j] = a[i][j-1] > a[i-1][j] ? a[i][j-1] : a[i-1][j];
			}
			
		}
		a[i+1] = a[i] + m;
	}
	
	if(!a[n][m])
	{
		printf("There is no common sub-sequence.\n");
		return NULL;
	}
	
	
	char* result;
	int length = a[n][m];
	result = (char*)malloc((length+1) * sizeof(char));
	
	while(n > 0 && m > 0)
	{
		if(s[n-1] == t[m-1] && m != 0)
		{
			result[--length] = s[n-1];
			m--;
			n--;
		}
		else
		{
			a[n][m-1] >= a[n-1][m] ? m-- : n--;
		}

	}
	
	free(a[0]);
	free(a);
	return result;
}

int main()
{
	char str1[10] = "abcde";
	char str2[10] = "bcea";
	printf("%s\n" , lcs(str1, str2));
	return 0;
}