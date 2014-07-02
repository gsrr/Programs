#include <stdio.h>
#include <string.h>

int isNightMultiple(int tmp_sum)
{
        if(tmp_sum % 9 != 0)
        {
                return 0;
        }

        if(tmp_sum >= 10)
        {
                char s[1001] = {0};
                sprintf(s, "%d", tmp_sum);
                int sum = 0;
                for(int i = 0; s[i]; i++)
                        sum += s[i]-'0';
                return isNightMultiple(sum) + 1;
        }
        else 
        {
                return 1;
        }

}


int main() {
        char s[1001];
        while(scanf("%s", s) == 1) {
                if(strcmp(s, "0") == 0)
                        break;
                int i, sum = 0;
                for(i = 0; s[i]; i++)
                        sum += s[i]-'0';
                printf("%s is ", s);
                int degree = isNightMultiple(sum);
                if(degree != 0)
                {
                        printf("a multiple of 9 and has 9-degree %d.\n", degree);
                }
                else
                {
                        puts("not a multiple of 9.");
                }
        }
        return 0;
}
