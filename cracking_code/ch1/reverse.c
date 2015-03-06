
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void reverseChar(char *str)
{
        int i;
        int j = strlen(str) - 1;
        for( i = 0 ; i < strlen(str)/2 ; i++)
        {
                char temp = str[i];
                str[i] = str[j];
                str[j] = temp;
                j--;
        }
        
}


void strcat_my(char *str, char *pch)
{
        strcat(str, pch);
        strcat(str, " ");
}

void reverseWord(char *str)
{
        reverseChar(str);
        char *pch;
        pch = strtok(str, " ,.");
        str[0] = '\0';
        while(pch != NULL)
        {
                reverseChar(pch);
                strcat_my(str, pch);
                pch = strtok(NULL, " ,.");
        }
}


void reverseChar_my(int s, char *str)
{
        int i;
        int end = s + (strlen(str) - s) / 2;
        int j = strlen(str) - 1;
        for( i = s ; i < end ; i++)
        {
                char temp = str[i];
                str[i] = str[j];
                str[j] = temp;
                j--;
        }

}

void reverseWord_loop(char *str)
{
        reverseChar(str);
        int i;
        int s = 0;
        for( i = 0 ; i < strlen(str) + 1 ; i++)
        {
                if( str[i] == ' ' )
                {
                        str[i] = '\0';
                        reverseChar_my(s , str);
                        s = i + 1;
                        str[i] = ' ';
                }
        
        /* for last word */}
        reverseChar_my(s , str);

}

int main()
{
        char backup[512] = {0};
        char message[] = "This is a message.";
        printf("Original message:%s\n", message);

        strcpy(backup, message);
        reverseChar(backup);
        printf("Reverse Character:%s\n", backup);

        strcpy(backup, message);
        reverseWord(backup);
        printf("Reverse Word:%s\n", backup);

        strcpy(backup, message);
        reverseWord_loop(backup);
        printf("Reverse Word:%s\n", backup);
        return 0;
}

