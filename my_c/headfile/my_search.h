#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <string.h>
using namespace std;

struct intArray{
	int** arr;
	int m;
	int n;

};

typedef struct intArray IntArray;


void displayIntArray(IntArray* arr)
{
	int m = arr->m;
	int n = arr->n;
	int i,j;
	for(i = 0 ; i < m ; i++)
	{
		for(j = 0 ; j < n ; j++)
		{
			printf("%d ", arr->arr[i][j]);
		}
		printf("\n");
	}
}

IntArray* IntArray_init(int m, int n)
{
	IntArray* arr = (IntArray*)malloc(sizeof(IntArray));
	arr->arr = (int**)malloc(sizeof(int*) * m);
	int i;
	for( i = 0 ; i < m ; i++)
	{
		arr->arr[i] = (int*)malloc(sizeof(int)*n);
		memset(arr->arr[i], 0, n);
	}
	arr->m = m;
	arr->n = n;
	return arr;
}

// /*

void displayMatrix(int** rec, int m , int n)
{
	int i,j;
	for( i = 0 ; i < m ; i++)
	{
		for( j = 0 ; j < n ; j++)
		{
			printf("%d ",rec[i][j]);
		}
		printf("\n");
	}
}

int** initMatrix(int m, int n)
{
	int** rec = (int**)malloc(sizeof(int*) * m);
	int i;
	for(i = 0 ; i < m ; i++)
	{
		rec[i] = (int*)malloc(sizeof(int) * n);
		memset(rec[i], 0, n);
	}
	return rec;
}

struct element{
	int value;
	int r;
	int c;
};

typedef struct element Element;

Element getElemInit(int key, int i, int j)
{
	Element e;
	e.value = key;
	e.r = i;
	e.c = j;
	return e;
}
void trverse_arr_bfs(IntArray* array, int** rec, int i, int j)
{
	queue<Element> qu;
	int m = array->m;
	int n = array->n;
	int key = array->arr[i][j];
	Element e = getElemInit(key, i, j);
	qu.push(e);
	while(qu.empty() != true)
	{
		Element tmp = qu.front();
		qu.pop();
		int r = tmp.r;
		int c = tmp.c;
		if(tmp.value == key && rec[r][c] == 0)
		{
			rec[r][c] = 1;
			if(r+1 < m)
			{
				int value = array->arr[r+1][c];
				Element e = getElemInit(value, r+1, c);
				qu.push(e);
			}
			if(c+1 < n)
			{
				int value = array->arr[r][c+1];
				Element e = getElemInit(value, r, c+1);
				qu.push(e);
			}
		}
	}
}
// */

