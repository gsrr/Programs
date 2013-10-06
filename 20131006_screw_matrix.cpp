#include <stdio.h>
#include <stdlib.h>




int rightScrew(int** matrix , int size)
{
	int count = 2;
	int r = 0;
	int c = 0;
	matrix[r][c] = 1;
	while(count <= size * size)
	{
		c = c + 1;
		for(c ; c < size && matrix[r][c] == 0; c++)
		{
			matrix[r][c] = count++;
		}
		c = c - 1;
		r = r + 1;
		for(r ; r < size && matrix[r][c] == 0; r++)
		{
			matrix[r][c] = count++;
		}
		r = r - 1;
		c = c - 1;
		for(c ; c > -1 && matrix[r][c] == 0 ; c--)
		{
			matrix[r][c] = count++;
		}
		c = c + 1;
		r = r - 1;
		for(r ; r > -1  && matrix[r][c] == 0; r--)
		{
			matrix[r][c] = count++;
		}
		r = r + 1;
	}
}



int leftScrew(int** matrix , int size)
{
	int count = 2;
	int r = 0;
	int c = 0;
	matrix[r][c] = 1;
	while(count <= size * size)
	{
		r = r + 1;
		for(r ; r < size && matrix[r][c] == 0; r++)
		{
			matrix[r][c] = count++;
		}
		r = r - 1;
		c = c + 1;
		for(c ; c < size && matrix[r][c] == 0; c++)
		{
			matrix[r][c] = count++;
		}
		c = c - 1;
		r = r - 1;
		for(r ; r > -1 && matrix[r][c] == 0 ; r--)
		{
			matrix[r][c] = count++;
		}
		r = r + 1;
		c = c - 1;
		for(c ; c > -1  && matrix[r][c] == 0; c--)
		{
			matrix[r][c] = count++;
		}
		c = c + 1;
	}
}


int main()
{
	int n;
	while(scanf("%d\n" , &n) != EOF)
	{
		int a , b;
		while(n--)
		{
			scanf("%d %d\n" , &a , &b);
			int** matrix =(int**) malloc( a * sizeof(int*));
			matrix[0] = (int*) calloc(a*a , sizeof(int));
			for(int i = 1 ; i < a ; i++)
			{
				matrix[i] = matrix[i-1] + a;
			}
			if(b == 1)
			{
				rightScrew(matrix , a);
			}
			else
			{
				leftScrew(matrix , a);
			}

			for(int i = 0 ; i < a ; i++)
			{
				for(int j = 0 ; j < a  ; j++)
				{
					printf("%5d" , matrix[i][j]);
				}
				printf("\n");
			}
		}

		
	}
	return 0;
}
