#include<stdio.h>

int house[6][6] = {0};
int path[10] = {0}, pathsize = 0;
void backtracking( int point )
{
        path[pathsize++] = point;
        int i;
        if( pathsize == 9 )
        {
                for( i = 0 ; i < pathsize ; i++ )
                        printf( "%d", path[i] );
                printf( "\n" );
                pathsize--;
                return;
        }

        for( i = 1 ; i <= 5 ; i++ )
        {
                if( house[point][i] )
                {
                        house[point][i] = house[i][point] = 0;
                        backtracking( i );
                        house[point][i] = house[i][point] = 1;
                }
        }
        pathsize--;
}

int main()
{
        house[1][2] = house[2][1] = 1;
        house[1][3] = house[3][1] = 1;
        house[1][5] = house[5][1] = 1;
        house[2][3] = house[3][2] = 1;
        house[2][5] = house[5][2] = 1;
        house[3][4] = house[4][3] = 1;
        house[3][5] = house[5][3] = 1;
        house[4][5] = house[5][4] = 1;
        backtracking( 1 );
        return 0;
}
