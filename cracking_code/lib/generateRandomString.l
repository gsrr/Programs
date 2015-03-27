/* ::#def:void generateRandomString(char *str, int len):: */
void generateRandomString(char *str, int len)
{
        char charSet[] = "abcdefghijklmnopqrstuvwxyz "; 
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
/* #end */
