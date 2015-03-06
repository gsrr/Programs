#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 256

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


removeSpaceAndMove(char *str, int length)
{
        int i;
        int si = -1;
        for( i = 0 ; i < length ; i++)
        {
                if(str[i] == ' ')
                {
                        if(si == -1)
                        {
                                si = i;
                        }
                }
                else
                {
                        if(si != -1)
                        {
                                str[si] = str[i];
                                str[i] = ' ';

                                int j = si + 1;
                                si = -1;
                                for( j ; j < i + 1 ; j++)
                                {
                                        if(str[j] == ' ')
                                        {
                                                si = j; 
                                                break;                      
                                        }
                                }
                        }
                }

        }    

}
removeSpaceAndMove_2(char *str, int length)
{
        int i;
        int si = -1;
        for( i = 0 ; i < length ; i++)
        {
                if(str[i] != ' ')
                {
                        int j = si + 1;
                        for( j ; j < i ; j++)
                        {
                                if(str[j] == ' ')
                                {
                                        break;                      
                                }
                        }
                        si = j;
                               
                        if(si != i)
                        {
                                str[si] = str[i];
                                str[i] = ' ';

                        }
                }

        }    
        str[si + 1] = '\0';

}

void removeDuplicateCharByBuffer(char *str, int length)
{
        int a[26] = {0};
        int i = 0 ; 
        for( i ; i < length ; i++)
        {
                int c = str[i] - 'a';
                if(a[c] == 0)
                {
                        a[c]++;
                }
                else
                {
                        str[i] = ' ';
                }
        }
        removeSpaceAndMove_2(str, length);
}

int bit(int *a, int c)
{
        int b = 1 << c;
        return b & *a;
}

void addBit(int *a, int c)
{
        int b = 1 << c;
        *a = *a | b;
}

void removeDuplicateCharByBuffer_2(char *str, int length)
{
        int a = 0;
        int i = 0 ; 
        for( i ; i < length ; i++)
        {
                int c = str[i] - 'a';
                if(bit(&a,c) == 0)
                {
                        addBit(&a,c);
                }
                else
                {
                        str[i] = ' ';
                }
        }
        removeSpaceAndMove_2(str, length);
}

int main()
{
        char str[SIZE] = {0};
        char engSet[] = "abcdefghijklmnopqrstuvwxyz";
        generateRandomString(engSet, SIZE, str);
        printf("Input String : \n%s\n", str);
        removeDuplicateCharByBuffer(str, SIZE);
        printf("\nOutput String - unique character:\n%s (size:%d)\n", str,strlen(str));
        removeDuplicateCharByBuffer_2(str, SIZE);
        printf("\nOutput String - unique character:\n%s (size:%d)\n", str,strlen(str));
        return 0;
}
