
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
                printf("%c ", i + 'a');
                for( j = 0 ; j < bss[i].len ; j++)
                {
                        printf("%d-%d ", bss[i].s[j], bss[i].e[j]);
                }
                printf("\n");
        }
        printf("\n");
}

void showBusSwapShift(bus_shift* bss, int num, int base, int b, int comp, int c, int boffset, int coffset)
{
        int i;
        for( i = 0 ; i < num ; i++)
        {
                int j;
                printf("%c ", i + 'a');
                for( j = 0 ; j < bss[i].len ; j++)
                {
                        if( i == base && j == b )
                        {
                                printf("\033[41m\033[37m");
                                printf("%d-%d ", bss[i].s[j] + boffset, bss[i].e[j] + boffset);
                                printf("\033[0m");
                        }
                        else if(i == comp && j == c)
                        {
                                printf("\033[41m\033[37m");
                                printf("%d-%d ", bss[i].s[j] + coffset, bss[i].e[j] + coffset);
                                printf("\033[0m");
                        }
                        else
                        {
                                printf("%d-%d ", bss[i].s[j], bss[i].e[j]);
                        }
                }
                printf("\n");
        }
}


/* ::#def myrand :: */
typedef struct{
        int base;
        int cust;
}f_args;

int myrand_base(int base)
{
        srand(time(NULL));
        return rand() % base;
}

int var_f(f_args in)
{
        int base = in.cust ? in.cust : in.base;
        return myrand_base(base);
}

/*
* varadic macros
*/
#define myrand(...) var_f((f_args){.base=1000,__VA_ARGS__});




/* #end */


int getOffset(bus_shift* bss, int num, int busIdx, int timeIdx)
{
      int offset[3] = {0 , -20, 20};
      int i;
      for( i = 0 ; i < num ; i++)
      {
              if( i == busIdx )
              {
                  int len = bss[busIdx].len;
                  int j;
                  for( j = 0 ; j < 3 ; j++)
                  {
                          int s = bss[busIdx].s[timeIdx] + offset[j];
                          int e = bss[busIdx].e[timeIdx] + offset[j];
                          int post_s;
                          int post_e;
                          if(timeIdx != 0)
                          {
                                  int pre_s = bss[busIdx].s[timeIdx-1];
                                  int pre_e = bss[busIdx].e[timeIdx-1];
                                  if(pre_s > s || pre_e > s)
                                  {
                                          continue;
                                  }
                          }
                          if(timeIdx != len -1)
                          {
                                  int post_s = bss[busIdx].s[timeIdx+1];
                                  int post_e = bss[busIdx].e[timeIdx+1];
                                  if(s > post_s || e > post_s)
                                  {
                                          continue;
                                  }
                          }
                          break;
                  }
                  if(j == 3)
                  {
                          return -1;
                  }
                  else
                  {
                          return offset[j];
                  }

              }
      }
}


void check_bus_shift(bus_shift* bss, int num, int base, int bIdx, int comp, int cIdx)
{
      int b_offset = getOffset(bss, num, base, bIdx);
      int c_offset = getOffset(bss, num, comp, cIdx);
      printf("\n");
      if(b_offset == -1 || c_offset == -1)
      {
              printf("Error\n");
      }
      else
      {
              printf("%c:offset=%d, %c:offset=%d\n", base+'a', b_offset, comp+'a', c_offset);
              showBusSwapShift(bss, num, base, bIdx, comp, cIdx, b_offset, c_offset);
      }
      sleep(1);
}


void swapShift(bus_shift* bss, int base, int i, int comp, int j)
{
        int* b_s = bss[base].s;
        int* b_e = bss[base].e;
        int* c_s = bss[comp].s;
        int* c_e = bss[comp].e;

        int tmp_s = b_s[i];
        b_s[i] = c_s[j];
        c_s[j] = tmp_s;

        int tmp_e = b_e[i];
        b_e[i] = c_e[j];
        c_e[j] = tmp_e;
}

void browse_bus_shift(bus_shift* bss, int base, int comp, int num)
{
        int i;
        for( i = 0 ; i < bss[base].len ; i++ )
        {
                int j;
                for( j = 0 ; j < bss[comp].len ; j++)
                {
                       int b_s = bss[base].s[i];
                       int c_s = bss[comp].s[j];
                       if(abs(b_s - c_s) <= 60)
                       {
                               system("clear");
                               showBusShift(bss, num);
                               printf("Swap (%c,%d) & (%c, %d)\n", base + 'a', i + 1, comp + 'a', j+ 1);
                               swapShift(bss, base, i, comp, j);
                               showBusSwapShift(bss, num, base, i, comp, j, 0, 0);
                               check_bus_shift(bss, num, base, i, comp, j);
                               swapShift(bss, base, i, comp, j);
                       }
                }
        }
}


void switchBusShift(bus_shift* bss, int busNum, int len)
{
        int i;
        for( i = 0 ; i < len ; i++ )
        {
                if( i != busNum)
                {
                        browse_bus_shift(bss, busNum, i, len);               
                }
        }
}

int main()
{
        int num = 3;
        bus_shift *bss = readInput("shift.txt", num);       
        int busNum = myrand(3);
        switchBusShift(bss, busNum, num);
        return 0;
}

