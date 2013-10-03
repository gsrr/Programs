#include <stdio.h>
#include <stdlib.h>


int main()
{
	int n , m;
	int count =0;
	//int a[101][101];
	while(scanf("%d %d" , &n , &m) != EOF)
	{
		if(n == 0 && m == 0)
		{
			break;
		}
		count++;
		
		int* s = (int*)malloc(n * sizeof(int));
		int* t = (int*)malloc(m * sizeof(int));
		for(int i = 0 ; i < n ; i++)
		{
			scanf("%d" , &s[i]);
		}
		for(int j = 0 ; j < m ; j++)
		{
			scanf("%d" , &t[j]);
			
		}
		
		int** a;
		a = (int**)calloc(n+1 ,sizeof(int*));
		a[0] = (int*)calloc((n+1) * (m+1) , sizeof(int));
		
		

		for(int i = 0 ; i <= n ; i++)
		{
			for(int j = 0 ; j <= m ; j++)
			{
				if(!i || !j)
				{
					a[i][j] = 0;
				}
				else if(s[i-1] == t[j-1])
				{
					a[i][j] = a[i-1][j-1] + 1;
				}
				else
				{
					a[i][j] = (a[i-1][j] >= a[i][j-1]) ? a[i-1][j] : a[i][j-1];
				}
				//printf("%d:%d:%d " , s[i-1] , t[j-1] , a[i][j]);
			}
			
			if(i != n)
			{
				a[i+1] = a[i] + (m+1);
			}
			//printf("\n");
		}
		
		printf("Twin Towers #%d\nNumber of Tiles : %d\n\n" , count , a[n][m]);
		free(a[0]);
		free(a);
		free(s);
		free(t);
	}
	return 0;
}
