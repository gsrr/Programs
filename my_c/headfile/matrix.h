#include <stdio.h>


void matrixAdd(int fir[][], int sec[][], int row, int col);
void matrixSub(int fir[][], int sec[][], int row, int col);
void matrixMult(int fir[][], int sec[][], int row, int col);

void matrixAdd(int fir[][], int sec[][], int row, int col)
{
        int i;
        for( i = 0 ; i < col ; i++ )
        {
                int j;
                for( j = 0 ; j < row ; j++ )
                {
                        fir[i][j] += sec[i][j];
                }
        }
}

void matrixSub(int fir[][], int sec[][], int row, int col)
{
        int i;
        for( i = 0 ; i < col ; i++ )
        {
                int j;
                for( j = 0 ; j < row ; j++ )
                {
                        fir[i][j] -= sec[i][j];
                }
        }
}
void matrixMult(int fir[][], int sec[][], int ret[][], int row, int col)
{
        int i;
        for( i = 0 ; i < col ; i++ )
        {
                int j;
                int ret = 0;
                for( j = 0 ; j < row ; j++ )
                {
                        ret += fir[i][j] * sec[j][i];
                }
                
        }
}
