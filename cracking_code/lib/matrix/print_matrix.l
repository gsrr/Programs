
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
