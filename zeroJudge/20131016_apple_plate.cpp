#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;


int f(int m , int n)
{
	cout << m << ":" << n << endl;
	if(m == 0 || n == 1)
	{
		return 1;
	}
	else if(m < n)
	{
		return f(m , m);
	}
	else
	{
		return f(m-n , n) + f(m , n-1);
	}
}


int main()
{
	int t = 0;
	while(scanf("%d" , &t) != EOF)
	{
		int m , n;
		while(t--)
		{
			scanf("%d %d" , &m , &n);
			printf("%d\n" , f(m , n));
		}
	}
	return 0;
}
