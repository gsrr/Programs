/*Rotate matrix*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int** createMatrix(int row, int col)
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
                        matrix[i][j] = rand() % 10;
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

void transposeElement(int** matrix, int i, int j)
{
       int temp = matrix[i][j];
        matrix[i][j] = matrix[j][i];
       matrix[j][i] = temp; 
}

void transMatrix(int** matrix, int row, int col)
{
        int i;
        int j;
        for( i = 0 ; i < row ; i++)
        {
                for( j = 0 ; j < i && j < col ; j++)
                {
                        transposeElement(matrix, i, j);       
                }
        }
}

void swapColumn(int** matrix, int row, int col)
{
        int i;
        int j;
        for( j = 0 ; j < col/2 ; j++)
        {
                int end = (col - 1) - j;
                for( i = 0 ; i < row ; i++)
                {
                        int temp = matrix[i][j];
                        matrix[i][j] = matrix[i][end];
                        matrix[i][end] = temp;       
                }
        }
}

int main()
{
        int** matrix = createMatrix(5, 5);
        printf("%d\n", matrix[0][1]);
        print_matrix(matrix, 5, 5);
        transMatrix(matrix, 5, 5);
        print_matrix(matrix, 5, 5);
        swapColumn(matrix, 5, 5);
        print_matrix(matrix, 5, 5);
        return 0;
}

