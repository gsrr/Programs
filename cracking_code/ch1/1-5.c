/*compress*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* ::#def:void generateRandomString(char *str, int len):: */
void generateRandomString(char *str, int len)
{
/*char charSet[] = "abcdefghijklmnopqrstuvwxyz";*/ 
        char charSet[] = "abcde";
        int setSize = sizeof(charSet) - 1;
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


void compressString(char *str)
{
        int i;
        int len = strlen(str);
        int cnt = 0;
        int pos = 0;
        for( i = 0 ; i < len ;)
        {
                char c = str[i];
                cnt++;
                int j;
                for( j = i + 1 ; j < len ; j++)
                {
                        if(c == str[j])
                        {
                                cnt++;
                        }
                        else
                        {
                                break;
                        }
                }

                int digits = floor(log10(cnt)) + 1;
                char *tmp = (char*)malloc(sizeof(char) * (digits + 1));
                sprintf(tmp , "%d", cnt);
                int len_tmp = strlen(tmp);
                if( cnt > 1)
                {
                        int k;
                        for(k = 0 ; k < len_tmp ; k++)
                        {
                                str[pos++] = tmp[k];
                        }
                }
                str[pos] = c;
                pos++;
                i += cnt;
                cnt = 0;
        }       
        str[pos] = '\0';
}

int main()
{
        char str[40] = {0};
        generateRandomString(str, 40);
        print_str(str);
        compressString(str);
        print_str(str);
        return 0;
}

