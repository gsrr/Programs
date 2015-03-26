/* #replace space*/
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

char* expandString(char *str, int len)
{
        int cnt = 0;
        int i;
        for( i = 0 ; i < len ; i++ )
        {
                if(str[i] == ' ')
                {
                        cnt++;
                }
        } 
        int ex_len = len + cnt * 2;
        char *str_ex = (char*)malloc(sizeof(char) * ex_len);
        strcpy(str_ex, str);

        i = len - 1;
        for( i ; i < ex_len - 1 ; i++)
        {
                str_ex[i] = ' ';
        }
        str_ex[ex_len - 1] = '\0'; 
        return str_ex;
}


void replaceSpace(char* str, int len)
{
        int cnt = 0;
        int i;
        for(i = 0 ; i < len ; i++)
        {
                if(str[i] == ' ')
                {
                        cnt++;
                }       
        }
        i = 0;
        for( i = len - 1 ; i > -1 ; i--)
        {
                if(str[i] == ' ')
                {
                        cnt--;
                        str[i + 2 * cnt] = '%';
                        str[i + 2 * cnt + 1] = '2';
                        str[i + 2 * cnt + 2] = '0';
                }
                else
                {
                        str[i + 2 * cnt] = str[i];
                }
        }
        i = 0 ;
}

int main()
{
        char str[10];
        generateRandomString(str, 10);
        printf("final:%s:%d\n", str, strlen(str));
        char *str_ex = expandString(str, 10);
        printf("final:%s:%d\n", str_ex, strlen(str_ex));
        replaceSpace(str_ex, strlen(str));
        printf("final:%s:%d\n", str_ex, strlen(str_ex));

        return 0;
}

