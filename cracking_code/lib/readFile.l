


/* ::#def readFile :: */

void readFile(const char* filepath, void *args, void (*func)(char* line, void* args))
{
        FILE *fr = fopen(filepath, "r");
        char buffer[512];
        while(fgets(buffer, 512, fr) != NULL)
        {
                func(buffer, args);
        }
}
/* #end */
