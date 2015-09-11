#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>
#include <pthread.h>
#include <dirent.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <string.h>


#define NUM 2
#define LIMIT 5000
int f_cnt1 = 0;
int f_cnt2 = 0;
char *files[NUM];
int fd1 = -1;
int fd2 = -1;

int isDirectoryEmpty(const char *dirname) 
{
	int n = 0;
	struct dirent *d;
	DIR *dir = opendir(dirname);
	if (dir == NULL) 
		return 1;
	while ((d = readdir(dir)) != NULL) {
		if(++n > 2)
			break;
	}
	closedir(dir);
	if (n <= 2) 
		return 1;
	else
		return 0;
}

int execute(
	const char *fpath, 
	const struct stat *statb, 
	int type,
	struct FTW *state)
{
	if(type == FTW_F || type == FTW_SL ||(type = FTW_D && isDirectoryEmpty(fpath) == 1))
	{
		if(fd1 < 0 )
		{
			fd1 = open( files[0], O_CREAT|O_TRUNC|O_RDWR ,S_IRUSR | S_IWUSR | S_IRGRP);
			f_cnt1 = 0;
		}
		if(fd1 > 0)
		{
			if( f_cnt1 < LIMIT ) {
				char path[255] = {0};
				sprintf(path, "\"%s\"\n", fpath);
				write(fd1, path, strlen(path));
				f_cnt1++;
				printf("write file1\n");
				return 0;
			}
			else
			{
				// exec thread1
			}
		}
		if(fd2 < 0 )
		{
			fd2 = open( files[1], O_CREAT|O_TRUNC|O_RDWR ,S_IRUSR | S_IWUSR | S_IRGRP);
			f_cnt2 = 0;
		}
		if(fd2 > 0)
		{
			if( f_cnt2 < LIMIT ) {
				char path[255] = {0};
				sprintf(path, "\"%s\"\n", fpath);
				write(fd2, path, strlen(path));
				f_cnt2++;
				printf("write file2\n");
			}
			else
			{
				//exec thread2
			}
		}
	}
	return 0;
}


int main(int argc, char **argv)
{
	int i;
	for( i = 0 ; i < NUM ; i++)
	{
		files[i] = (char*)malloc(sizeof(char) * 255);
		sprintf(files[i], "%s_%d", argv[1], i);
		printf("%s\n",files[i]);
	}
	nftw( ".", execute, 100, FTW_PHYS);
	//wait thread to complete
	return 0;
}
