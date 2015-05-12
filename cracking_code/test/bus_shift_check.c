
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
        int* s;
        int* e;
        int len;
};

typedef struct bus_shift bus_shift;

int lineLen(char* line, char* delimit)
{
        int cnt = 0;
        char* pch;
        char tmp[512];
        sprintf(tmp, "%s", line);
        pch = strtok(tmp, delimit);
        while(pch != NULL)
        {
                cnt++;
                pch = strtok(NULL, " ");
        }
        return cnt;
}


void getTime(char* timestr, int idx, bus_shift* bs)
{
        int s, e;

        int ret = sscanf(timestr, "%d-%d", &s, &e);
        if(ret == 2)
        {
                bs->s[idx] = s;
                bs->e[idx] = e;
        }
}

void setShiftData(bus_shift* bs, char* line)
{
        char* pch;
        pch = strtok(line, " ");
        pch = strtok(NULL, " ");
        int cnt = 0;
        while(pch != NULL)
        {
                getTime(pch , cnt++, bs);
                pch = strtok(NULL, " ");
        }

}

void setBusShift(bus_shift* bs, char* line)
{
        int len = lineLen(line, " ");
        bs->len = len - 1; 
        bs->s = (int*)malloc(sizeof(int) * bs->len);        
        bs->e = (int*)malloc(sizeof(int) * bs->len);        
        setShiftData(bs, line);
}

void trimRight(char* buffer)
{
        int len = strlen(buffer);
        int i;
        for( i = len - 1 ; i > -1 ; i--)
        {
                if(buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != '\n')
                {
                        break;
                }
        } 
        buffer[i + 1] = '\0';
}

bus_shift* readInput(char* path, int num)
{
        bus_shift* bss = (bus_shift*)malloc(sizeof(bus_shift) * num);
        char buffer[512];
        FILE* fr = fopen(path, "r");
        int i = 0;
        while(fgets(buffer, 512, fr) != NULL)
        {
                trimRight(buffer);
                setBusShift(&bss[i++], buffer);
        }   

                                    
        return bss;
}

void showBusShift(bus_shift* bss, int num)
{
        int i;
        for( i = 0 ; i < num ; i++)
        {
                int j;
                for( j = 0 ; j < bss[i].len ; j++)
                {
                        printf("%d-%d ", bss[i].s[j], bss[i].e[j]);
                }
                printf("\n");
        }
}


/*
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
*/

int main()
{
        int num = 3;
        bus_shift *bss = readInput("shift.txt", num);       
        showBusShift(bss, num);
        //check_bus_shift(bss, 3);
        return 0;
}

