#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

typedef long long int64;
const int INF = 0x3f3f3f3f; 
const int MAXN = 1000010;


int findSameNumber(int arr[], int i, int start)
{
        for(int j = i - 1 ; j > start - 1 ; j--)
        {
                if(arr[i] == arr[j])
                {
                        return 1;
                }
        }
        return 0;
}

int main()
{
        int nCase, m, n;
        int arr[MAXN];
        scanf("%d", &nCase);

        while(nCase--)
        {
                scanf("%d", &n);
                
                for(int i=0; i<n; i++)
                        scanf("%d", &arr[i]);

                int start = 0;
                int maxx = 0;
                arr[n] = arr[n-1];
                for(int i = 0; i <= n; i++)
                {
                        int ret = findSameNumber(arr, i, start);
                        if(ret)
                        {
                                maxx = max(i - start, maxx);
                                start = i;
                        }
                }
                printf("%d\n", maxx);
        }
        return 0; 
}
