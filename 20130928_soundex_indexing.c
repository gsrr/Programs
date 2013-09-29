#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int letter[27] = {0 , 1 , 2 , 3 , 0 , 1 , 2 , 0 , 0 , 2 , 2 , 4 , 5 ,5 ,0 , 1 , 2 , 6 , 2 , 3 , 0 , 1 , 0 , 2 , 0 , 2};

int main()
{
	char name[21];
	printf("%9c%s%*c%s\n", ' ', "NAME", 25 - strlen("NAME"), ' ', "SOUNDEX CODE");
	while(scanf("%s" , name) != EOF)
	{
		int length = strlen(name);
		char output[5];
		output[0] = name[0];
		output[4] = '\0';
		int j = 1;
		int pre_code = letter[name[0] -65];
		for(int i = 1 ; i < length &&  j < 4 ; i++)
		{
			if(letter[name[i] - 65] != 0 && (pre_code != letter[name[i] - 65]))
			{
				output[j] = letter[name[i] - 65] + 48;
				j++;
			}
			pre_code = letter[name[i] -65];

		}

		for(j ; j < 4 ; j++)
		{
			output[j] = '0';
		}
		printf("%9c%s%*c%s\n", ' ', name, 25 - strlen(name), ' ', output);
	}
	printf("%19c%s\n", ' ', "END OF OUTPUT");
	return 0;
}
