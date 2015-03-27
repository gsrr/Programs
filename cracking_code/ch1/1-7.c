/* set matrix to zero */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/* ::#def:int** createMatrix(int row, int col):: */
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
/* ::#end:: */

/* ::#def:void print_matrix(int** matrix, int row, int col):: */
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

/* :: :: */
void insertion_sort(int* arr, int len, int val)
{
        int i;
        for(i = len - 1 ; i > -1 ; i--)
        {
                if(arr[i] < val)
                {
                        arr[i + 1] = arr[i];
                }
                else
                {
                        break;
                }       
        }       
        arr[ i + 1] = val;
}
/* #end */

void setZero(int** matrix, int row, int col)
{
        int* r_ind = (int*)malloc(sizeof(int) * row);
        int* c_ind = (int*)malloc(sizeof(int) * col);
        int r_cnt = 0;
        int c_cnt = 0;
        memset(r_ind, -1, row);
        memset(c_ind, -1, col);
        int i;
        int j;
        for( i = 0 ; i < row ; i++)
        {
                for( j = 0 ; j < col ; j++)
                {
                        if(matrix[i][j] == 0)
                        {
                                insertion_sort(r_ind, r_cnt, i);
                                insertion_sort(c_ind, c_cnt, j);                               
                                r_cnt++;
                                c_cnt++;
                        }
                }
        
        }

        for(i = 0 ; i < r_cnt ; i++)
        {
                int r = r_ind[i];
                for( j = 0 ; j < col ; j++)
                {
                        matrix[r][j] = 0;
                }
        }
        for( j = 0 ; j < c_cnt ; j++)
        {
                int c = c_ind[j];
                for( i = 0 ; i < row ; i++)
                {
                        matrix[i][c] = 0;
                }
        }
}

int main()
{
        int** matrix = createMatrix(5,5);
        print_matrix(matrix,5,5);

        setZero(matrix, 5, 5);
        print_matrix(matrix,5,5);
        return 0;
}

