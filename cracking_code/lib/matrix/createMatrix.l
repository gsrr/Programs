
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
