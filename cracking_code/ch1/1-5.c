/*compress*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ::#def:void generateRandomString(char *str, int len):: */
void generateRandomString(char *str, int len)
{
        char charSet[] = "abcdefghijklminopqrstuvwxyz "; 
        int setSize = sizeof(charSet);
        srand(time(NULL));
        int i;
        for( i = 0 ; i < len -1 ; i++)
        {
                int r = rand() % setSize;
                str[i] = charSet[r];
        }
        str[len - 1] = '\0';
}
/* ::#def print_str(char *str)::*/
void print_str(char *str)
{
        printf("%s\n", str);       
}

int main()
{
        char str[20] = {0};
        generateRandomString(str, 20);
        print_str(str);
        return 0;
}

