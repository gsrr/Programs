


/* ::#def time :: */

void currtime()
{
        time_t t;
        struct tm *timeinfo;
        time(&t);
        timeinfo = localtime(&t);
        printf("%s\n",asctime(timeinfo));
}
/* #end */
