#include <stdio.h>


void matrixAdd(Matrix fir, Matrix sec);
void matrixSub(Matrix fir, Matrix sec);
void matrixMult(Matrix *fir, Matrix *sec, Matrix *ret)


typedef struct matrix{
	int **elem;
	int row;
	int col;
}Matrix;

void matrixAdd(Matrix *fir, Matrix *sec)
{
        int i;
        for( i = 0 ; i < fir->row ; i++ )
        {
                int j;
                for( j = 0 ; j < fir->col ; j++ )
                {
                        fir[i][j] += sec[i][j];
                }
        }
}

void matrixSub(Matrix *fir, Matrix *sec)
{
        int i;
        for( i = 0 ; i < fir->row ; i++ )
        {
                int j;
                for( j = 0 ; j < fir->col ; j++ )
                {
                        fir[i][j] -= sec[i][j];
                }
        }
}
void matrixMult(Matrix *fir, Matrix *sec, Matrix *ret)
{
        int i;
        for( i = 0 ; i < ret->row ; i++ )
        {
                int j;
                for( j = 0 ; j < ret->col ; j++ )
                {
                        ret->elem[i][j] = 0;
			int n;
			for( n = 0 ; n < fir->col ; n++)
			{
				ret->elem[i][j] += fir[i][n] * sec[n][j];
			}
                }
                
        }
}

void matrixInverse(Matrix *fix, Matrix *ret
{
        
}
