#include<stdio.h>
#include<stdlib.h>
#define Mod 500000

#include <map>
using namespace std;



void InsHash(int n, map<int , int> &HASH) {
        if(HASH.find(n) == HASH.end())
                HASH[n] = 1;
        else
                HASH[n] = HASH[n] + 1;

}

int Find(int v, map<int, int> &HASH) {
        map<int, int>::iterator curr = HASH.find(v);
        if (curr != HASH.end()) {
                return curr->second;
        }
        return 0;
}

void putRightValueInfoHash(int A[], int n, map<int, int> &HASH)
{
        for(int a = 0; a < n; a++)
                for(int b = 0; b < n; b++)
                        for(int c = 0; c < n; c++) {
                                InsHash(A[a]*A[b]+A[c], HASH);
                        }
}


long long compareLeftValueWithHash(int A[], int n, map<int, int> &HASH)
{
        long long Ans = 0;
        for(int a = 0; a < n; a++) {
                if(A[a] != 0)
                        for(int b = 0; b < n; b++)
                                for(int c = 0; c < n; c++) {
                                        Ans += Find(A[a]*(A[b]+A[c]), HASH);
                                }
        }

        return Ans;

}

int main() {
        int n, A[100];
        while(scanf("%d", &n) == 1) {
                map<int , int> HASH;
                for(int a = 0; a < n; a++)
                        scanf("%d", &A[a]);

                putRightValueInfoHash(A, n, HASH);
                printf("%lld\n\n", compareLeftValueWithHash(A, n , HASH));
        }
        return 0;
}
