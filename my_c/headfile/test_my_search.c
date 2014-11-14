#include "my_search.h"

int TEST_INTARRAY_INIT = 0;
int TEST_TRVERSE_ARR_BFS = 1;

void test_IntArray_init()
{
	if(TEST_INTARRAY_INIT == 0)
	{	
		return;
	}
	IntArray *arr = IntArray_init(5, 5);	
	displayIntArray(arr);
}

void test_trverse_arr_bfs()
{
	if(TEST_TRVERSE_ARR_BFS == 0)
	{	
		return;
	}
	IntArray *arr = IntArray_init(5, 5);
	int** rec = initMatrix(5,5);
	arr->arr[3][3] = 1;
	displayIntArray(arr);
	printf("\n");
	displayMatrix(rec, 5, 5);
	printf("\n");
	trverse_arr_bfs(arr, rec,0,0);	
	displayMatrix(rec, 5, 5);
}

int main()
{
	test_IntArray_init();
	test_trverse_arr_bfs();
	return 0;
}
