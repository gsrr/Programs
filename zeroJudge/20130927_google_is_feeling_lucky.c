#include <stdio.h>
#include <stdlib.h>




struct page
{
	char name[100];
	int score;
};


void insertionSort(struct page webSite[] , int i)
{
	struct page current = webSite[i];
	//strcpy(current.name , webSite[i].name);
	//current.score = webSite.score;
	int j = i - 1;
	while(j > -1)
	{
		struct page pre  = webSite[j];
		if(current.score <= pre.score)
		{
			break;	
		}
		webSite[i] = webSite[j];
		i--;
		j--;
	}
	webSite[i] = current;
}




int main()
{
	int n;
	struct page webSite[10];
	while(scanf("%d", &n) != EOF)
	{
		for(int j = 0 ; j < n ; j++)
		{
			for(int i = 0 ; i < 10 ; i++)
			{
				scanf("%s %d" , webSite[i].name , &(webSite[i].score));
				insertionSort(webSite , i);
			}
			
			int max = webSite[0].score;
			printf("Case #%d:\n%s\n" , j+1 , webSite[0].name);
			for(int i = 1 ; i < 10 ; i++)
			{
				if(webSite[i].score == max)
				{
					printf("%s\n" , webSite[i].name);
				}
			}
		}
	}


	return 0;
}
