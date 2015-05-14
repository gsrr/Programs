


/* ::#def myprint :: */

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


/* #end */
