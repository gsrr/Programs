
/*
 * transfer float to binary representation
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>


float frand()
{
        return (float)rand() / (float)(RAND_MAX);
}


void convertToBinary(float f)
{
        float tmp = f;
        printf("0.");
        while( tmp != 0 )
        {
                tmp = tmp * 2;
                if( tmp >= 1)
                {
                        printf("1");
                        tmp = tmp - 1;
                }       
                else
                {
                        printf("0");
                }
        }
        printf("\n");
}

int main()
{
        srand((unsigned int)time(NULL));
        float f = frand();
        convertToBinary(0.5);
        convertToBinary(0.3);
        convertToBinary(0.6);
        convertToBinary(f);
        return 0;
}

