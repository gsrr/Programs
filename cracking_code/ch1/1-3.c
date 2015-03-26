/*#permutation*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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


int checkPerm_buffer(char* str1, char* str2)
{
        int len1 = strlen(str1);
        int len2 = strlen(str2);
        if(len1 != len2)
        {
                return -1;
        }

        int buffer[128] = {0};
        int i;
        for( i = 0 ; i < len1 ; i++ )
        {
                buffer[str1[i]]++;       
        }     
        for( i = 0 ; i < len2 ; i++)
        {
                buffer[str2[i]]--;
                if(buffer[str2[i]] == -1)
                {
                        return -1;
                }
        }
        
        return 0;
}

/*int as_compare (const void * a, const void * b)*/
int as_compare (const void * a, const void * b)
{
  return ( *(char*)a - *(char*)b );
}

int checkPerm_sort(char* str1, char* str2)
{
        int len1 = strlen(str1);
        int len2 = strlen(str2);
        qsort(str1, len1, sizeof(char), as_compare);       
        qsort(str2, len2, sizeof(char), as_compare);    
        printf("%s\n%s\n", str1,str2);
        return strcmp(str1, str2);   
}

int main()
{
        char charSet[] = "abcdefghijklmnopqrstuvwxyz";
        char str1[10] = {0};
        char str2[10] = {0};
        generateRandomString(charSet , 10 , str1);
        generateRandomString(charSet , 10 , str2);
        
        printf("%s\n%s\n", str1, str2);  
        printf("checkPerm_buffer : %d\n", checkPerm_buffer(str1, str2)); 
        printf("checkPerm_sort : %d\n", checkPerm_sort(str1, str2)); 
        return 0;
}

