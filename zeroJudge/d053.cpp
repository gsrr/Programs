#include <iostream>
#include <stdio.h>
using namespace std;


int sudoku[9][9];
int queue[81][2];
int end_point,n;
bool get_answer;

int check(int x,int y,int num)
{
        for(int i = 0; i < n * n; i++)
        {
                if(sudoku[i][y] == num && i != x) return 0;
                if(sudoku[x][i] == num && i != y) return 0;
        }
        int xx = x/n, yy = y/n;
        xx*= n, yy *= n;
        for(int i=0;i<n;i++)
        {
                for(int j=0;j<n;j++)
                {
                        if(sudoku[xx + i][yy + j] == num && (xx+i) != x && (yy+j) != y) return 0;
                }
        }

        return 1;
}

bool find_answer(int now, int end_point)
{
        return now == end_point;
}


void DFS(int now){
        if(get_answer)
                return ;
        if(find_answer(now, end_point))
        {
                get_answer=true;
                for(int i=0;i<n*n;i++){
                        int first = 0;
                        for(int j=0;j<n*n;j++)
                        {
                                if(first)
                                {   
                                        cout << " ";
                                }
                                else    
                                {
                                        first = 1;
                                }
                                cout << sudoku[i][j];
                        }
                        cout << endl;
                }
                return ;
        }
        

        int x = queue[now][0];
        int y = queue[now][1];

        if(sudoku[x][y] == 0)
        {
                for(int i=1;i<=n*n;i++)
                {
                        if( check ( queue[now][0], queue[now][1], i ) == 1)
                        {
                                sudoku[queue[now][0]][queue[now][1]] = i;
                                DFS(now + 1);
                                sudoku[queue[now][0]][queue[now][1]] = 0;
                        }
                }
        }
        else
        {
                DFS(now + 1);
        }
}

int main()
{
        int first = 0;
        while(cin >> n){
                end_point = 0;
                get_answer=false;
                for(int i=0; i < n * n; i++)
                {
                        for(int j=0;j < n * n; j++)
                        {
                                cin >> sudoku[i][j];
                                queue[end_point][0] = i;
                                queue[end_point][1] = j;
                                end_point++;
                        }
                }

                if(first)
                {   
                        cout << endl;
                }
                else    
                {
                        first = 1;
                }
                
                DFS(0);
                if(!get_answer)
                {
                        cout << "NO SOLUTION" << endl;
                }
        }
        return 0;
}
