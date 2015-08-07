
/*
 * How many possible paths to go from (0,0) to (x,y)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>


/* ::#def:int** createMatrix(int row, int col):: */
int** createMatrix(int row, int col, int value)
{
       srand(time(NULL));
       int i;
       int j;
       int** matrix = (int**)malloc(sizeof(int*) * row);
       for( i = 0 ; i < row ; i++)
       {
               matrix[i] = (int*)malloc(sizeof(int) * col);
               for( j = 0 ; j < col ; j++)
               {
                       if(value == -1)
                       {
                                matrix[i][j] = rand() % 10;
                       }
                       else
                       {
                                matrix[i][j] = 0;
                       }
               }
       }
        return matrix;
}

void print_matrix(int** matrix, int row, int col)
{
        int i;
        int j;
        for( i = 0 ; i < row ; i++)
        {
                for( j = 0 ; j < col ; j++)
                {
                        printf("%d ", matrix[i][j]);
                }
                printf("\n");
        }
        printf("\n");
}
/* ::#end:: */

void initMatrix(int*** matrix, int r, int c)
{
        int** tmp = *matrix;
        print_matrix(tmp, r, c);
        int i;
        for( i = 0 ; i < r ; i++)
        {
                tmp[i][0] = 1;
        }
        for( i = 0 ; i < c ; i++)
        {
                tmp[0][i] = 1;
        }
}

void calSteps(int*** matrix, int x, int y)
{
        int** tmp = *matrix;
        int i;
        for( i = 1 ; i < x ; i++)
        {
                int j;
                for( j = 1; j < y ; j++)
                {
                        tmp[i][j] = tmp[i-1][j] + tmp[i][j-1];
                }
        }       
}

int main()
{
        int x,y;
        printf("Input a number (row):");
        scanf("%d", &x);
        printf("Input a number (col):");
        scanf("%d", &y);
        int** matrix = createMatrix(x, y, 0);
        initMatrix(&matrix, x, y);
        print_matrix(matrix, x, y);
        calSteps(&matrix, x, y);
        print_matrix(matrix, x, y);
        return 0;
}

