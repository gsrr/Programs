

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <windows.h>
#include <stdarg.h>
#include <direct.h>

#define OFFSET 20


HANDLE  hConsole; 

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




/* ::#def myprint :: */

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

void countfsChargs(FILE* fw, bus_shift* bss, int num, int base, int b, int comp, int c, int boffset, int coffset)
{
        int i;
        int fc = 0;
        int fct = 0;
        int sc = 0;
        int sct = 0;
        for( i = 0 ; i < num ; i++)
        {
                int pe = bss[i].e[0];
                offsetValue(&pe, i, 0, base, b, comp, c, boffset, coffset);
                int j;
                for( j = 1 ; j < bss[i].len ; j++)
                {
                        int cs = bss[i].s[j];
                        offsetValue(&cs, i, j, base, b, comp, c, boffset, coffset);
                        if(cs - pe >= 60)        
                        {
                                sc++;
                                sct = sct + cs - pe;
                        }
                        else if(cs - pe >= 20)
                        {
                                fc++;
                                fct = fct + cs - pe;
                        }
                        else
                        {
                            ;
                        }
                        pe = bss[i].e[j];
                        offsetValue(&pe, i, j, base, b, comp, c, boffset, coffset);
                }
        }
        myprintf(fw, "Fast Charges: %d , total time:%d minutes\n", fc, fct);
        myprintf(fw, "Slow Charges: %d , total time:%d minutes\n", sc, sct);
}

void showBusSwapShift(bus_shift* bss, int num, int base, int b, int comp, int c, int boffset, int coffset)
{
        char filepath[256] = {0};
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
                                SetConsoleTextAttribute(hConsole, 12);
                                myprintf(fw, "%d-%d ", bss[i].s[j] + boffset, bss[i].e[j] + boffset);
                               SetConsoleTextAttribute(hConsole, 15);
                        }
                        else if(i == comp && j == c)
                        {
                                SetConsoleTextAttribute(hConsole, 12);
                                myprintf(fw, "%d-%d ", bss[i].s[j] + coffset, bss[i].e[j] + coffset);
                                SetConsoleTextAttribute(hConsole, 15);
                        }
                        else
                        {
                                myprintf(fw, "%d-%d ", bss[i].s[j], bss[i].e[j]);
                        }
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
      }
      Sleep(1000);
      printf("\nPress any key to continue...\n");
      //getchar();
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

void browse_bus_shift(bus_shift* bss, int base, int comp, int num)
{
        int totalCnt = 0;
        int sucCnt = 0;
        int failCnt = 0;
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
                               system("cls");			  
                               showBusShift(bss, num);
							    totalCnt++;
                               SetConsoleTextAttribute(hConsole, 14);
                               printf("Swap (%c,%d) & (%c, %d)\n", base + 'a', i + 1, comp + 'a', j+ 1);
                               SetConsoleTextAttribute(hConsole, 15);
                               swapShift(bss, base, i, comp, j);
                               //showBusSwapShift(bss, num, base, i, comp, j, 0, 0);
                               int ret = check_bus_shift(bss, num, base, i, comp, j);
                               ret == 0 ? sucCnt++ : failCnt++;
                               swapShift(bss, base, i, comp, j);
                       }
                }
        }
        printf("\nResult: total = %d , successful = %d , fail = %d\n", totalCnt, sucCnt, failCnt);
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
        mkdir(".\\outputs");
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 15);
        int num = 3;
        bus_shift *bss = readInput("shift.txt", num);       
        int busNum = myrand(3);
        switchBusShift(bss, busNum, num);
        system("pause");
        return 0;
}

