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
