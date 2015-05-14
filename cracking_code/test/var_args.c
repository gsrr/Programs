
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

void writeData(char* filepath, char* msg)
{
        if(filepath == NULL)
        {
                return;
        }
        FILE *fw = fopen(filepath, "a");
        fprintf(fw, "%s", msg);
        fclose(fw);
}


void myprintf(char* filepath, const char *fmt, ...)
{
        char msg[1024] = {0};
        va_list ap;
        va_start(ap, fmt);
        vsprintf(msg, fmt, ap);
        va_end(ap);
        printf("%s", msg);
        writeData(filepath, msg);
        return;
}

int main()
{
        char *str = "Hello World";
        int test = 100;
        myprintf(NULL, "%s This is a test:%d\n", str, test);
        myprintf("test.txt", "%s This is a test:%d\n", str, test);
        return 0;
}

