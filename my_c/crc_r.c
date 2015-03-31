
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char msg[] = "a";
uint POLY = 0xEDB88320;
int main()
{
        uint i,j,l,x;
        l = sizeof(msg)-1;
        x = 0;
        for( i=0; i<l; i++ ) {
                x = x ^ msg[i];
                for( j=0; j<8; j++ ) {
                        uint tmp = x;
                        printf("%x\n", x);
                        x = (x>>1) ^ 0x80000000;
                        //x = x ^ ((~tmp&1)*POLY);
                }
        }
        printf( "crc32(\"%s\")=%08X\n", msg, x );
        return 0;
}


