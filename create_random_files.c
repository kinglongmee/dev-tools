
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char *strSrc="123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

void gen_random_filename(char *filename)
{
	int cnt = 0, i = 0, n = 0;

	cnt = rand() % 255;
	if (cnt < 5)
		cnt = 5;

	for (i=0; i < cnt; i++) {
		n = rand() % 61;
		filename[i] = strSrc[n];
	}
	filename[i] = 0;
}

int main(int argc, char **argv)
{
	char filename[256];
	char *dirpath = argv[1];
	int ret = 0, i = 0, cnt = 0;

	if (argc < 3) {
		printf("Usage: %s dirpath fcount\n", argv[0]);
		return -1;
	}

	cnt = atoi(argv[2]);

	ret = mkdir(dirpath, 0777);
	if (ret && errno != EEXIST) {
		printf("mkdir %s failed: %m\n", dirpath);
		return -1;
	}

	ret = chdir(dirpath);
	if (ret) {
		printf("chdir %s failed: %m\n", dirpath);
		return -1;
	}

	srand(time(NULL));
	for (i=1; i<=cnt; i++) {
		gen_random_filename(filename);
		ret = creat(filename, 0777);
		if (ret < 0)
			printf("creat %s failed: %m\n", filename);
		else
			close(ret);
	}

	return 0;
}
