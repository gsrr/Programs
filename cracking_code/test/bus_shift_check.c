
/*
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>


struct bus_shift
{
        int* start;
        int* end;
        int len;
};

typedef struct bus_shift bus_shift;


bus_shift* readInput(char* data)
{
        bus_shift* bs = (bus_shift*)malloc(sizeof(bus_shift) * 3);
               
        return bs;
}


void showBusShift(bus_shift* bss, int len)
{
        int i;
        for( i = 0 ; i < len ; i++)
        {

        }
}


int checkIndivBus(bus_shift bs)
{

}

void check_bus_shift(bus_shift* bss, int len)
{
        int i;
        for( i = 0 ; i < len ; i++ )
        {
                if(checkIndivBus(bss[i]) == 1)
                {
                        printf("Error\n");
                        return;
                }
        }
        showBusShift(bs, len);
}


int main()
{
        bus_shift *bss = readInput("shift.txt");       
        check_bus_shift(bss, 3);
        return 0;
}

