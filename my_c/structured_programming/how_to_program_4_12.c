#include <stdio.h>


//Browse odd number and sum these odd numbers from 1 to 15
int sumOddNumber()
{
        int i = 0;
        int sum = 0;
        for(i = 1 ; i <= 15 ; i+=2)
        {
                sum = sum + i;
        }
        return sum;
}
// Calculate odd number from 1 to 15
int main()
{
        printf("%d\n" , sumOddNumber());
        return 0;
}

