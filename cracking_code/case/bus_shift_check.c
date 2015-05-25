
/*
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <stdarg.h>
#include <iostream>
#include <map>

#define OFFSET 20

/*
#define DEBUG //debug
#ifdef DEBUG
        #define D if(1)
#else
        #define D if(0)
#endif
*/


#define debug(...) fprintf(stdout, __VA_ARGS__)
#define debug(...)

struct bus_shift
{
        int* s;
        int* e;
        int* pc;
        int len;
};

typedef struct bus_shift bus_shift;

int lineLen(char* line, const char* delimit)
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


void getTime(char* timestr, int idx, bus_shift* bs, std::map<std::string, int> *powerMap)
{
        int s, e;

        int ret = sscanf(timestr, "%d-%d", &s, &e);
        if(ret == 2)
        {
                bs->s[idx] = s;
                bs->e[idx] = e;
                char key[512] = {0};
                sprintf(key, "%d_%d", s, e);
                bs->pc[idx] = (*powerMap)[key];
                //printf("%d-%d : %d\n",bs->s[idx], bs->e[idx], bs->pc[idx]);
        }
}

void setShiftData(bus_shift* bs, char* line, std::map<std::string, int> *powerMap)
{
        char* pch;
        pch = strtok(line, " ");
        pch = strtok(NULL, " ");
        int cnt = 0;
        while(pch != NULL)
        {
                getTime(pch , cnt++, bs, powerMap);
                pch = strtok(NULL, " ");
        }

}

void setBusShift(bus_shift* bs, char* line, std::map<std::string, int> *powerMap)
{
        int len = lineLen(line, " ");
        bs->len = len - 1; 
        bs->s = (int*)malloc(sizeof(int) * bs->len);        
        bs->e = (int*)malloc(sizeof(int) * bs->len);        
        bs->pc = (int*)malloc(sizeof(int) * bs->len);
        setShiftData(bs, line, powerMap);
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

bus_shift* readInput(const char* path, int num, std::map<std::string,int> *powerMap)
{
        bus_shift* bss = (bus_shift*)malloc(sizeof(bus_shift) * num);
        char buffer[512];
        FILE* fr = fopen(path, "r");
        int i = 0;
        while(fgets(buffer, 512, fr) != NULL)
        {
                trimRight(buffer);
                setBusShift(&bss[i++], buffer, powerMap);
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




/* ::#def myprint :: */
/*
void debug(const char *fmt, ...)
{
        va_list ap;
        va_start(ap, fmt);
        D vfprintf(stderr, fmt, ap);
        va_end(ap);

}
*/

void writeData(FILE *fw, char* msg)
{
        fprintf(fw, "%s", msg);
}


void myprintf(FILE *fw, const char *fmt, ...)
{
        char msg[1024] = {0};
        va_list ap;
        va_start(ap, fmt);
        vsprintf(msg, fmt, ap);
        va_end(ap);
        printf("%s", msg);
        writeData(fw, msg);
        return;
}


/* #end */
void offsetValue(int *pe, int i, int j, int base, int b, int comp, int c, int boffset, int coffset)
{
     if( i == base && j == b)
     {
           *pe += boffset;
     }
     if( i == comp && j == c)
     {
           *pe += coffset;
     }
}


void subPower(bus_shift *bss , int busIdx, int shiftIdx, int *powerBase)
{
        int s = bss[busIdx].s[shiftIdx];
        int e = bss[busIdx].e[shiftIdx];
        *powerBase -= bss[busIdx].pc[shiftIdx];      
}

void countfsChargs(FILE* fw, bus_shift* bss, int num, int base, int b, int comp, int c, int boffset, int coffset)
{
        int powerBase[3] = {100, 100, 100};
        int i;
        int fc = 0;
        int fct = 0;
        int sc = 0;
        int sct = 0;
        for( i = 0 ; i < num ; i++)
        {
                int pe = bss[i].e[0];
                subPower(bss, i, 0, &powerBase[i]);
                offsetValue(&pe, i, 0, base, b, comp, c, boffset, coffset);
                int j;
                for( j = 1 ; j < bss[i].len ; j++)
                {
                        debug("%c, powerBase:%d\n", i + 'a', powerBase[i]);
                        int cs = bss[i].s[j];
                        offsetValue(&cs, i, j, base, b, comp, c, boffset, coffset);
                        if(cs - pe >= 60)        
                        {
                                sc++;
                                sct = sct + cs - pe;
                                powerBase[i] += 100;
                        }
                        else if(cs - pe >= 20)
                        {
                                fc++;
                                fct = fct + cs - pe;
                                powerBase[i] += ((cs - pe) / 10) * 8;
                        }
                        else
                        {

                            ;
                        }
                        pe = bss[i].e[j];
                        subPower(bss, i, j, &powerBase[i]);
                        offsetValue(&pe, i, j, base, b, comp, c, boffset, coffset);
                }
        }
        myprintf(fw, "\nFast Charges: %d , total time:%d minutes\n", fc, fct);
        myprintf(fw, "Slow Charges: %d , total time:%d minutes\n", sc, sct);
        myprintf(fw, "\nPower Remind: a:%d, b:%d, c:%d \n", powerBase[0], powerBase[1], powerBase[2]);
}

void showBusSwapShift(bus_shift* bss, int num, int base, int b, int comp, int c, int boffset, int coffset)
{
        char filepath[256] = {0};
        printf("Bus choosed: %c\n\n", base + 'a');
        printf("%c:offset=%d, %c:offset=%d\n", base+'a', boffset, comp+'a', coffset);
        sprintf(filepath, "%s\\%c%d%c%d", ".\\outputs", base+'a', b, comp+'a', c);
        FILE *fw = fopen(filepath, "a");
        int i;
        for( i = 0 ; i < num ; i++)
        {
                int j;
                myprintf(fw, "%c ", i + 'a');
                for( j = 0 ; j < bss[i].len ; j++)
                {
                        if( i == base && j == b )
                        {
                                printf("\033[41m\033[37m");
                                myprintf(fw, "%d-%d ", bss[i].s[j] + boffset, bss[i].e[j] + boffset);
                                printf("\033[0m");
                        }
                        else if(i == comp && j == c)
                        {
                                printf("\033[41m\033[37m");
                                myprintf(fw, "%d-%d ", bss[i].s[j] + coffset, bss[i].e[j] + coffset);
                                printf("\033[0m");
                        }
                        else
                        {
                                myprintf(fw, "%d-%d ", bss[i].s[j], bss[i].e[j]);
                        }
                        debug("cost:%d ", bss[i].pc[j]);
                }
                myprintf(fw, "\n");
        }
        countfsChargs(fw, bss, num, base, b, comp, c, boffset, coffset);
        fclose(fw);
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
      int offset[3] = {0 , -1*OFFSET, OFFSET};
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


int check_bus_shift(bus_shift* bss, int num, int base, int bIdx, int comp, int cIdx)
{
        int ret = 0;
      int b_offset = getOffset(bss, num, base, bIdx);
      int c_offset = getOffset(bss, num, comp, cIdx);
      printf("\n");
      if(b_offset == -1 || c_offset == -1)
      {
              printf("Error\n");
                ret = 1;       
      }
      else
      {
              showBusSwapShift(bss, num, base, bIdx, comp, cIdx, b_offset, c_offset);
              printf("\nPress any key to continue...\n");
              getchar();
      }
      //sleep(1);
      return ret;
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

int browse_bus_shift(bus_shift* bss, int base, int comp, int num)
{
        int ret = -1;
        int totalCnt = 0;
        int sucCnt = 0;
        int failCnt = 0;
        int i = myrand(bss[base].len);
        int j;
        for( j = 0 ; j < bss[comp].len ; j++)
        {
                int b_s = bss[base].s[i];
                int c_s = bss[comp].s[j];
                if(abs(b_s - c_s) <= 60)
                {
                        system("clear");
                        showBusShift(bss, num);
                        totalCnt++;
                        printf("Swap (%c,%d) & (%c, %d)\n", base + 'a', i + 1, comp + 'a', j+ 1);
                        swapShift(bss, base, i, comp, j);
                        //showBusSwapShift(bss, num, base, i, comp, j, 0, 0);
                        ret = check_bus_shift(bss, num, base, i, comp, j);
                        if(ret == 0)
                        {
                                sucCnt++;
                                break;
                        } 
                        else
                        {
                                failCnt++;
                        }
                        swapShift(bss, base, i, comp, j);
                }
        }
        //printf("\nResult: total = %d , successful = %d , fail = %d\n", totalCnt, sucCnt, failCnt);
        return ret;
}

void swapArr(int* arr, int i, int j)
{
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
}
        

void shuffleArray(int* arr, int len)
{
        int i;
        for( i = len - 1 ; i > -1 ; i--)
        {
                int r = myrand(len);
                swapArr(arr, i, r);
        }
}

void switchBusShift(bus_shift* bss, int busNum, int len)
{
        int* arr = (int*)malloc(sizeof(int) * len);
        int i;
        for( i = 0 ; i < len ; i++)
        {
                arr[i] = i;
        }

        shuffleArray(arr, len);
        for( i = 0 ; i < len ; i++)
        {
                if( i != busNum)
                {
                        int ret = browse_bus_shift(bss, busNum, i, len);               
                        if( ret == 0)
                        {
                                break;
                        }
                }
        }
        free(arr);
}


struct mapArgs
{
        std::map<std::string, int> *mp;
};

typedef struct mapArgs mapArgs;

void readMap(char* line, void* args)
{
       mapArgs *mp = (mapArgs*)args;
       std::map<std::string, int> *powerMap = mp-> mp;
       int a, b, c, d;
       sscanf(line, "%d %d %d %d", &a, &b, &c, &d);
       char key[512] = {0};
       sprintf(key, "%d_%d", b, c);
       (*powerMap)[key] = d;
}

void readFile(const char* filepath, void *args, void (*func)(char* line, void* args))
{
        FILE *fr = fopen(filepath, "r");
        char buffer[512];
        while(fgets(buffer, 512, fr) != NULL)
        {
                func(buffer, args);
        }
}

void readSchedule(const char* filepath, std::map<std::string,int> *powerMap)
{
        mapArgs *mp = (mapArgs*)malloc(sizeof(mapArgs));
        mp->mp = powerMap;
        readFile(filepath, mp, readMap);     
}

void showMapContent(std::map<std::string, int> *powerMap)
{
        for(std::map<std::string, int>::iterator it=(*powerMap).begin(); it != (*powerMap).end(); it++)
        {
                std::cout << it->first << " => " << it->second << '\n';
        }
}

int main()
{
        system("rm ./outputs/*");
        srand(time(NULL));
        int num = 3;
        std::map<std::string , int> powerMap;
        readSchedule("schedule.txt", &powerMap);
        bus_shift *bss = readInput("shift.txt", num , &powerMap);       
        while(1)
        {
                int busNum = myrand(3);
                switchBusShift(bss, busNum, num);
        }
        return 0;
}

