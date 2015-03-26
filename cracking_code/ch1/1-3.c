/*#permutation*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ::#def:void generateRandomString(char *charSet, int length, char *str):: */
void generateRandomString(char *charSet, int length, char *str)
{
        srand(time(NULL));
        int i;
        for( i = 0 ; i < length -1 ; i++)
        {
                int r = rand() % (sizeof(charSet) - 1);
                str[i] = charSet[r];
        }
        str[length - 1] = '\0';
}

int main()
{
        char charSet[] = "abcdefghijklmnopqrstuvwxyz";
        char str[10] = {0};
        generateRandomString(charSet , 10 , str);
        printf("%s\n", str);   
        return 0;
}

