
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

#define TSIZE 1024
#define PATH_MAX 4096

static void gen_data(char *buf)
{
	unsigned int *pd = NULL;
	int i = 0;

	for (i = 0; i < TSIZE; i += 4) {
		pd = (unsigned int *)(buf + i);
		*pd = i;//random();
	}
}

static void dump_data(char *buf, const char *head_str)
{
	unsigned int *pd = NULL;
	int i = 0;

	printf("%s:", head_str);

	for (i = 0; i < TSIZE; i += 4) {
		pd = (unsigned int *)(buf + i);
		if (i % 64 == 0)
			printf("\n0x%04x ", i);
		printf("%08x ", *pd);
	}

	printf("\n");
}

char wpath[PATH_MAX], rpath[PATH_MAX];
char wbuf72[TSIZE];
char rbuf720[TSIZE];
char rbuf721[TSIZE];
char wbuf74[TSIZE];
char rbuf74[TSIZE];

static ssize_t
do_write(const char *path, char *buf, int len, off_t offset)
{
	ssize_t wsize = 0;
	int wfd = -1;

	wfd = openat(AT_FDCWD, path, O_WRONLY|O_DIRECT|O_CREAT, 00700);
	if (wfd < 0) {
		printf("open %s\n", path);
		return 0;
	}

	wsize = pwrite(wfd, buf, len, offset);
	close(wfd);

	return wsize;
}

static ssize_t
do_read(const char *path, char *buf, int len, off_t offset)
{
	ssize_t rsize = 0;
	int rfd = -1;

	rfd = openat(AT_FDCWD, path, O_RDONLY|O_DIRECT|O_CREAT, 00700);
	if (rfd < 0) {
		printf("open %s\n", path);
		return 0;
	}

	rsize = pread(rfd, buf, len, offset);
	close(rfd);

	return rsize;
}

int main(int argc, char **argv)
{
	off_t off200 = 0x200, off400 = 0x400;
	ssize_t wsize = 0, rsize = 0;
	int round = 0, i = 0;

	if (argc < 3) {
		printf("Usage: %s wdir rdir\n", argv[0]);
		return -1;
	}

	sprintf(wpath, "%s/dcfile", argv[1]);
	sprintf(rpath, "%s/dcfile", argv[2]);

	unlinkat(AT_FDCWD, wpath, 0);
	unlinkat(AT_FDCWD, rpath, 0);

	while(++round) {
		gen_data(wbuf72);
		gen_data(wbuf74);

		wsize = do_write(wpath, wbuf72, TSIZE, off200);
		if (wsize != TSIZE) {
			printf("write data to 0x%lx got %d", off200, wsize);
			break;
		}

		rsize = do_read(rpath, rbuf720, TSIZE, off200);
		if (rsize != TSIZE) {
			printf("read data from 0x%lx got %d", off200, rsize);
			break;
		}

		wsize = do_write(wpath, wbuf74, TSIZE, off400);
		if (wsize != TSIZE) {
			printf("write data to 0x%lx got %d", off400, wsize);
			break;
		}

		rsize = do_read(rpath, rbuf721, TSIZE, off200);
		if (rsize != TSIZE) {
			printf("read data from 0x%lx got %d", off200, rsize);
			break;
		}

		rsize = do_read(rpath, rbuf74, TSIZE, off400);
		if (rsize != TSIZE) {
			printf("read data from 0x%lx got %d", off400, rsize);
			break;
		}

		if (memcmp(rbuf720, wbuf72, TSIZE)) {
			printf("data0 at 0x%lx is not equal\n", off200);
			dump_data(wbuf72, "Writed");
			dump_data(rbuf720, "Read720");
			break;
		}

                memcpy(wbuf72 + 512, wbuf74, 512);
		if (memcmp(rbuf721, wbuf72, TSIZE)) {
			printf("data1 at 0x%lx is not equal\n", off200);
			dump_data(wbuf72, "Writed");
			dump_data(rbuf721, "Read721");
			break;
		}

		if (memcmp(rbuf74, wbuf74, TSIZE)) {
			printf("data at 0x%lx is not equal\n", off400);
			dump_data(wbuf74, "Writed");
			dump_data(rbuf74, "Read74");
			break;
		}

		off200 += 0x400;
		off400 += 0x400;
	}

	printf(", at round %d.\n", round);
	return 0;
}
