#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 256

void generateRandomString(char *str, int length)
{
        char engSet[] = "abcdefghijklmnopqrstuvwxyz";
        srand(time(NULL));
        
        int i;
        for( i = 0 ; i < length -1 ; i++)
        {
                int r = rand() % (sizeof(engSet) - 1);
                str[i] = engSet[r];
        }
        str[length - 1] = '\0';
}

int main()
{
        char str[SIZE] = {0};
        generateRandomString(str, SIZE);
        printf("%s\n", str);
        return 0;
}

